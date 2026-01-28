#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"

Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

	if (sensores.nivel != 4){
		if (!hayPlan){

			
					c_state.jugador.f = sensores.posF;
					c_state.jugador.c = sensores.posC;
					c_state.jugador.brujula = sensores.sentido;
					c_state.colaborador.f = sensores.CLBposF;
					c_state.colaborador.c = sensores.CLBposC;
					c_state.colaborador.brujula = sensores.CLBsentido;
					goal.f = sensores.destinoF;
					goal.c = sensores.destinoC;

			switch (sensores.nivel){
				case 0: 
					
					plan = AnchuraSoloJugador_V3(c_state , goal ,mapaResultado);

				break;
				case 1: 
					cout << "calculamos un nuevo plan\n";
					plan = AnchuraLvl1(c_state,goal,mapaResultado);
					VisualizarPlan(c_state,plan);

					cout << "se esta implementando el nivel 1";
				break;

				case 2: //llamada del metodo para el nivel 2
					cout << "se esta implementando el nivel 2";
				break;

				case 3: //llamada del metodo para el nivel 3
					cout << "se esta implementando el nivel 3";
				break;
				}

				VisualizarPlan(c_state,plan);
				hayPlan = true;
		}

		if (hayPlan && plan.size() > 0){
			accion = plan.front();
			plan.pop_front();
		}

		if(plan.size() == 0){
			cout << "se completo el plan" << endl;
			hayPlan = false;
		}
	}
	else
	{
		//incluir llamada think para el lvl.4
	}
		

	return accion;
}

bool ComportamientoJugador::AnchuraSoloJugador(const state &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	state current_state = inicio;
	list<state> frontier;
	list<state> explored;
	frontier.push_back(current_state);

	bool SolutionFound = (current_state.jugador.f == final.f && current_state.jugador.c == final.c);

	while(!frontier.empty() && !SolutionFound){
		// cout << "atascado";
		
		frontier.pop_front();
		explored.push_back(current_state);

		//generar hijo actWalk
		state child_walk = apply(actWALK,current_state,mapa);
		if (child_walk.jugador.f == final.f && child_walk.jugador.c == final.c){
			current_state = child_walk;
			SolutionFound = true;	
		}
		else if (!Find(child_walk,frontier) and !Find(child_walk,explored))
		{
			frontier.push_back(child_walk);
		}

		if (!SolutionFound){
		//generar hijo actRUN
			state child_run = apply(actRUN,current_state,mapa);
			if (child_run.jugador.f == final.f && child_run.jugador.c == final.c){
				current_state = child_run;
				SolutionFound = true;	
			}
			else if (!Find(child_run,frontier) and !Find(child_run,explored))
			{
				frontier.push_back(child_run);
			}
		}

		if (!SolutionFound){
			//generar hijo actTUNR_L
			state child_turnl = apply(actTURN_L,current_state,mapa);
			if (!Find(child_turnl,frontier) and !Find(child_turnl,explored)){
				frontier.push_back(child_turnl);
			}

			//generar hijo actTUNR_SR
			state child_turnsr = apply(actTURN_SR,current_state,mapa);
			if (!Find(child_turnsr,frontier) and !Find(child_turnsr,explored)){
				frontier.push_back(child_turnsr);
			}
		}

		if (!SolutionFound && !frontier.empty()){
			current_state = frontier.front();
		}
		

	}

	return SolutionFound;
}

bool ComportamientoJugador::CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char> > &mapa){
	return (mapa[x.f][x.c] != 'P' && mapa[x.f][x.c] != 'M');
}

ubicacion ComportamientoJugador::NextCasilla(const ubicacion &pos){
	/* Devuelve la ubicación siguiente según el avance del agente*/
    ubicacion next = pos;
    switch (pos.brujula)
    {
        case norte:
            next.f = pos.f - 1;
            break;
        case noreste:
            next.f = pos.f - 1;
            next.c = pos.c + 1;
            break;
        case este:
            next.c = pos.c + 1;
            break;
        case sureste:
            next.f = pos.f + 1;
            next.c = pos.c + 1;
            break; 
        case sur: 
            next.f = pos.f + 1; 
            break; 
         case suroeste: 
            next.f = pos.f + 1; 
            next.c = pos.c - 1; 
            break; 
         case oeste: 
            next.c = pos.c - 1; 
            break;  
         case noroeste:  
            next.f = pos.f - 1 ;  
            next.c = pos.c - 1 ;  
            break;   
	}   
     
	return   next;

}
// Devuelve el estado que se genera si el agente puede avanzar.
// Si no puede avanzar, devuelve como estado la misma entrada
state ComportamientoJugador::apply(const Action &a, const state &st, const vector<vector<unsigned char> > mapa){
	
    state st_result = st;
    ubicacion sig_ubicacion,sig_ubicacion2;
    
    switch(a)
	{
        case actWALK: //si prox casilla es transitable y no está ocupada por el colaborador
			sig_ubicacion = NextCasilla(st.jugador);

			if (CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
				st_result.jugador = sig_ubicacion;
			}

			break;

        case actRUN: //si prox 2 casillas son transitable y no está ocupada por el colaborador
			
			sig_ubicacion = NextCasilla(st.jugador);

			if (CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
				sig_ubicacion2 = NextCasilla(sig_ubicacion);

				if (CasillaTransitable(sig_ubicacion2,mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
						st_result.jugador = sig_ubicacion2;
				}
			}

			break;

        case actTURN_L:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+6)%8);

			break;

        case actTURN_SR:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+1)%8);

			break;

		case act_CLB_WALK:
			sig_ubicacion = NextCasilla(st.colaborador);
			
			if (CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
				st_result.colaborador = sig_ubicacion;
				st_result.ultimaOrdenColaborador = act_CLB_WALK;
			}

			break;

		case act_CLB_TURN_SR:
			st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
			st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;

			break;

		case act_CLB_STOP:
			st_result.ultimaOrdenColaborador = act_CLB_STOP;
			break;
    }

    return st_result;
}

bool ComportamientoJugador::Find(const state &item, const list<state> &lista){
	auto it = lista.begin();

	while (it != lista.end() && !((*it) == item)){
		it++;
	}

	return (!(it == lista.end()));
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

void ComportamientoJugador::AnulaMatriz(vector<vector<unsigned char> > &mapaResultado){
	for (int i = 0 ; i < mapaResultado.size() ; i++){
		for (int j = 0 ; j < mapaResultado[0].size() ; j++){
			mapaResultado[i][j] = 0;
		}
	}
}

void ComportamientoJugador::VisualizarPlan(const state &st, const list<Action> &plan){
	AnulaMatriz(mapaConPlan);
	state cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
    	if ((*it != act_CLB_WALK) && (*it != act_CLB_TURN_SR) && (*it != act_CLB_STOP))
    	{
     	   	switch (cst.ultimaOrdenColaborador)
     	   	{
				case act_CLB_WALK:
					cst.colaborador = NextCasilla(cst.colaborador);
					mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
					break;
				case act_CLB_TURN_SR:
					cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
					break;
        	}
    	}

		switch (*it)
		{
		case actRUN:
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 3;
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;

			break;

		case actWALK:
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;

			break;

		case actTURN_SR:
			cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 1) % 8);
			break;

		case actTURN_L:
			cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
			break;

		case act_CLB_WALK:
			cst.colaborador = NextCasilla(cst.colaborador);
			cst.ultimaOrdenColaborador = act_CLB_WALK;
			mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
			break;

		case act_CLB_TURN_SR:
			cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula+1) % 8);
			cst.ultimaOrdenColaborador = act_CLB_TURN_SR;

			break;

		case act_CLB_STOP:
			cst.ultimaOrdenColaborador = act_CLB_STOP;
			break; 
		}

		it++;

	}
}

void ComportamientoJugador::PintaPlan(const list<Action> &plan){

	auto it = plan.begin();
	while (it != plan.end()) {

		if (*it == actWALK) {
			cout << "W ";
		}
		else if (*it == actRUN) {
			cout << "R ";
		}
		else if (*it == actTURN_SR) {
			cout << "r ";
		}
		else if (*it == actTURN_L) {
			cout << "L ";
		}
		else if (*it == act_CLB_WALK) {
			cout << "cW ";
		}
		else if (*it == act_CLB_TURN_SR) {
			cout << "cr ";
		}
		else if (*it == act_CLB_STOP) {
			cout << "cS ";
		}
		else if (*it == actIDLE){
			cout << 'I ';
		} 
		else{
			cout<< "-_"; 
		} 
		it++;
	}

	cout << "(" << plan.size() << " acciones)\n";
}

bool ComportamientoJugador::Find(const state &item, const list<node> &lista){
	auto it = lista.begin();
	while (it != lista.end() && !(it->st == item)){
		it++;
	}

	return (!(it == lista.end()));
}

list <Action> ComportamientoJugador::AnchuraSoloJugador_V2(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){

	node current_node;
	list<node> frontier;
	list<node> explored;
	list<Action> plan;

	current_node.st = inicio;

	bool SolutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
	frontier.push_back(current_node);

	while (!frontier.empty() && !SolutionFound){
		frontier.pop_front();
		explored.push_back(current_node);

		//generar hijo actWalk
		node child_walk = current_node;
		child_walk.st = apply(actWALK,current_node.st,mapa);
		child_walk.secuencia.push_back(actWALK);

		if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c){
			current_node = child_walk;
			SolutionFound = true;
		}
		else if (!Find(child_walk.st, frontier) && !Find(child_walk.st,explored)){
			frontier.push_back(child_walk);
		}

		if (!SolutionFound){
			//generar hijo actRun
			node child_run = current_node;
			child_run.st = apply(actRUN,current_node.st,mapa);
			child_run.secuencia.push_back(actRUN);

			if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c){
				current_node = child_run;
				SolutionFound = true;
			}
			else if (!Find(child_run.st , frontier) && !Find(child_run.st , explored)){
				frontier.push_back(child_run);
			}
		}
		
		if (!SolutionFound){
			//generar hijo de actTurn_L
			node child_turnl = current_node;
			child_turnl.st = apply(actTURN_L,current_node.st,mapa);
			child_turnl.secuencia.push_back(actTURN_L);

			if (!Find(child_turnl.st, frontier) && !Find(child_turnl.st, explored)){
				frontier.push_back(child_turnl);
			}
			//generar hijo de actTurn_SR
			node child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR,current_node.st,mapa);
			child_turnsr.secuencia.push_back(actTURN_SR);

			if (!Find(child_turnsr.st , frontier) && !Find(child_turnsr.st , explored)){
				frontier.push_back(child_turnsr);
			}
		}

		if (!SolutionFound && !frontier.empty()){
			current_node = frontier.front();
		}
	}

	if (SolutionFound){
		plan = current_node.secuencia;
		cout << "Encontrado un plan: ";
		PintaPlan(current_node.secuencia);
	}

	return plan;
}
list <Action> ComportamientoJugador::AnchuraSoloJugador_V3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){

	node current_node;
	list<node> frontier; //cerrados
	set<node> explored; //abiertos
	list<Action> plan; //es lo que se va a devolver, el plan de las acciones a llevar a cabo
	current_node.st = inicio; //es decir, en el nodo actual, en que posiciones se encuentran los agentes
	bool SolutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c); //nos encontramos sobre la casilla de solucion?
	frontier.push_back(current_node); //a la frontera le añade el nodos actual, no tengo claro que es la frontera
	/*
		*LA FRONTERA*

		- Lista de nodos pendientes de explorar, no acabo de entender porque mete el current en frontier
	
		SOLUCION: porque lo primero que se hace al entrar es frontera.pop entonces para que es no de fallo tiene que 
		llevar algo metido ya de antes y se pone este que luego se elimina en lo primero y ya esta

		*EXPLORADOS*

		- Lista de nodos que ya se han visitado y por tanto no hay que volver a visitar. Cada vez que se tacha
		uno de la frontera hay que añadirlo a los explorados.

		*ACLARACIONES*

		- Por cada accion posible a realizar desde un nodo se genera un nodo hijo y a este se le evaluan a su
		vez todas las posibilidades y se le generan todos los hijos que se le tengan que generar y es asi como
		finalmente se encuentra una solución, es como encadenar nodos.

		- si frontier queda vacio es porque no hay solucion posible
	*/
	while(!frontier.empty() and !SolutionFound){ //mientras haya nodos que explorar y no se haya llegado a la solucion
		
		//fase inicial de actualizacion de estado
		frontier.pop_front(); 
		explored.insert(current_node);

		//Generar hijo actWALK
		node child_walk = current_node; //se genera y luego se comprueba si tiene lo que hay que tener para pushearlo al frontier o no
		child_walk.st = apply(actWALK, current_node.st, mapa); //comprueba si puede avanzar
		child_walk.secuencia.push_back(actWALK);
		if(child_walk.st.jugador.f == final.f and child_walk.st.jugador.c == final.c){ // ¿hemos llegado?
			current_node = child_walk;
			SolutionFound = true;
		}
		else if(explored.find(child_walk) == explored.end()){ //si no ha sido ya explorado lo añadimos a la frontera 
			frontier.push_back(child_walk);
		}
		//esto es asi porque se espera volver a el a comprobar.

		if(!SolutionFound){ //en cada una de estas etas generando un nodo hijo que luego se va a explorar siguiendo el mismo paradigma
			//Generar hijo actRUN
			node child_run = current_node;
			child_run.st = apply(actRUN, current_node.st, mapa);
			child_run.secuencia.push_back(actRUN);
			if(child_run.st.jugador.f == final.f and child_run.st.jugador.c == final.c){
				current_node = child_run;
				SolutionFound = true;
			}
			else if(explored.find(child_run) == explored.end()){
				frontier.push_back(child_run);
			}
		}

		//si te das cuenta todos los nodos van arrastrando la secuencia que hay que
		//llevar a cabo para poder llegar hasta la salida desde la posicion en la que esten
		
		if (!SolutionFound){ //en cada una de estas etas generando un nodo hijo que luego se va a explorar siguiendo el mismo paradigma
			//generar hijo de actTurn_L
			node child_turnl = current_node;
			child_turnl.st = apply(actTURN_L,current_node.st,mapa);
			child_turnl.secuencia.push_back(actTURN_L);

			if (explored.find(child_turnl) == explored.end()){
				frontier.push_back(child_turnl);
			}
			//generar hijo de actTurn_SR
			node child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR,current_node.st,mapa);
			child_turnsr.secuencia.push_back(actTURN_SR);

			if (explored.find(child_turnsr) == explored.end()){
				frontier.push_back(child_turnsr);
			}
		}

		if (!SolutionFound && !frontier.empty()){ 
			current_node = frontier.front();

			while(!frontier.empty() && explored.find(current_node) != explored.end()){
				frontier.pop_front();

				if (!frontier.empty()){
					current_node = frontier.front();
				}

			}
		}
	}

	if (SolutionFound){
		plan = current_node.secuencia;
	}
	// 	cout << "Encontrado un plan: ";
	// 	PintaPlan(current_node.secuencia);
	// }

	return plan;
}
//WORK IN PROGRESS
list <Action> ComportamientoJugador::AnchuraLvl1(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){

	node current_node;
    current_node.st = inicio;
    set<node> abiertos;
    list<node> cerrados;
    list<Action> plan;
    Action ultima = actIDLE;
    list<Action> todas_acciones = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR};
    // abiertos.insert(current_node);
    cerrados.push_back(current_node);
	current_node = cerrados.front();


    while (!(current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c) && !cerrados.empty()){
		// current_node = cerrados.front();
		abiertos.insert(current_node);

		// bool veColaborador = colaboradorEnRangoVision(current_node.st.jugador,current_node.st.colaborador);
		bool veColaborador = colaboradorEnRangoVision(current_node.st);

        for (auto accion : todas_acciones){
			if (!veColaborador){
				if (accion != act_CLB_STOP && accion != act_CLB_WALK && accion != act_CLB_TURN_SR){
					node child_node;
					child_node.st = apply(accion, current_node.st, mapa);
					child_node.secuencia = current_node.secuencia;
					child_node.secuencia.push_back(accion);

					if (abiertos.find(child_node) == abiertos.end()){
						cerrados.push_back(child_node);
						// abiertos.insert(child_node);
					}
				}
			}
			else
			{
				if (accion == act_CLB_STOP || accion == act_CLB_WALK || accion == act_CLB_TURN_SR){
					node child_node;
					child_node.st = apply(accion, current_node.st, mapa);
					child_node.secuencia = current_node.secuencia;
					child_node.secuencia.push_back(accion);

					if (abiertos.find(child_node) == abiertos.end()){
						cerrados.push_back(child_node);
						// abiertos.insert(child_node);
					}
				}
			}
        }

		while(!cerrados.empty() && !(abiertos.find(current_node) == abiertos.end())){
			cerrados.pop_front();

			if (!cerrados.empty()){
				current_node = cerrados.front();
			}

		}
  	}

	current_node.secuencia.pop_back();

    plan = current_node.secuencia;
    PintaPlan(plan);
    return plan;

}

//work in progress
bool ComportamientoJugador::llegaRepitiendo(const list<Action> &secuencia){
	return false;
}


bool ComportamientoJugador::colaboradorEnRangoVision(const state &estado){

	bool confirmacion = false;

	switch(estado.jugador.brujula){
		case norte:
			if (
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 0== estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) || 
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||  
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) || 
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c)
			){
				confirmacion = true;
			}
			else
			{
				confirmacion = false;
			}
			
			break;

		case sur:

			if (
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) || 
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||  
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) || 
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c)
			){
				confirmacion = true;
			}
			else
			{
				confirmacion = false;
			}
			
			break;
		case este:
			if (
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||  
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c)
			){
				confirmacion = true;
			}
			else
			{
				confirmacion = false;
			}
			
			break;


		case oeste:

			if (
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
			(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
			(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
			(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
			(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||  
			(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
			(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c)
			){
				confirmacion = true;
			}
			else
			{
				confirmacion = false;
			}
			
			break;

			case noreste:

				if (
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) || 
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||  
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c)
				){
					confirmacion = true;
				}
				else
				{
					confirmacion = false;
				}


			break;
		case noroeste:

			if (
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) || 
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
				(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
				(estado.jugador.f - 2 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||  
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
				(estado.jugador.f - 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c)
				){
					confirmacion = true;
				}
				else
				{
					confirmacion = false;
				}
				
				break;

			
		case sureste:

			if (
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) || 
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) || 
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 3 == estado.colaborador.c) ||
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 2 == estado.colaborador.c) ||  
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 1 == estado.colaborador.c) || 
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c)
				){
					confirmacion = true;
				}
				else
				{
					confirmacion = false;
				}
				
				break;
		case suroeste:
			
			if (
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) ||
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c + 0 == estado.colaborador.c) ||
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) || 
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 2 == estado.colaborador.c) || 
				(estado.jugador.f + 3 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||
				(estado.jugador.f + 2 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) ||  
				(estado.jugador.f + 1 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c) || 
				(estado.jugador.f + 0 == estado.colaborador.f && estado.jugador.c - 3 == estado.colaborador.c)
				){
					
					confirmacion = true;
				}
				else
				{
					confirmacion = false;
				}
				
				break;
	}

	return confirmacion;
}


void ComportamientoJugador::generaVectores(pair<int, int> &del_1_al_3, pair<int, int> &del_3_al_2, pair<int, int> &del_3_al_4, Orientacion ori)
{
	pair<int, int> arriba = make_pair(-1, 0);
	pair<int, int> abajo = make_pair(1, 0);
	pair<int, int> izquierda = make_pair(0, -1);
	pair<int, int> derecha = make_pair(0, 1);
	pair<int, int> arriba_derecha = make_pair(-1, 1);
	pair<int, int> arriba_izquierda = make_pair(-1, -1);
	pair<int, int> abajo_derecha = make_pair(1, 1);
	pair<int, int> abajo_izquierda = make_pair(1, -1);

	switch (ori)
	{
	case norte:
		del_1_al_3 = arriba;
		del_3_al_2 = izquierda;
		del_3_al_4 = derecha;
		break;
	case sur:
		del_1_al_3 = abajo;
		del_3_al_2 = derecha;
		del_3_al_4 = izquierda;
		break;
	case este:
		del_1_al_3 = derecha;
		del_3_al_2 = arriba;
		del_3_al_4 = abajo;
		break;
	case oeste:
		del_1_al_3 = izquierda;
		del_3_al_2 = abajo;
		del_3_al_4 = arriba;
		break;
	case noreste:
		del_1_al_3 = arriba_derecha;
		del_3_al_2 = izquierda;
		del_3_al_4 = abajo;
		break;
	case noroeste:
		del_1_al_3 = arriba_izquierda;
		del_3_al_2 = abajo;
		del_3_al_4 = derecha;
		break;
	case sureste:
		del_1_al_3 = abajo_derecha;
		del_3_al_2 = arriba;
		del_3_al_4 = izquierda;
		break;
	case suroeste:
		del_1_al_3 = abajo_izquierda;
		del_3_al_2 = derecha;
		del_3_al_4 = arriba;
		break;
	}
}

bool ComportamientoJugador::colaboradorEnRangoVision(const ubicacion &j, const ubicacion &s)
{
	set<pair<int, int>> vision;
	pair<int, int> del_1_al_3, del_3_al_2, del_3_al_4;
	generaVectores(del_1_al_3, del_3_al_2, del_3_al_4, j.brujula);

	for (int nivel = 0; nivel < 4; nivel++)
	{
		pair<int, int> casilla_central = make_pair(j.f + del_1_al_3.first * nivel, j.c + nivel * del_1_al_3.second);

		vision.insert(casilla_central);

		for (int lateral = 1; lateral <= nivel; lateral++)
		{
			pair<int, int> casilla_lateral;
			casilla_lateral.first = casilla_central.first + (del_3_al_2.first * lateral);
			casilla_lateral.second = casilla_central.second + (del_3_al_2.second * lateral);
			vision.insert(casilla_lateral);

			casilla_lateral.first = casilla_central.first + (del_3_al_4.first * lateral);
			casilla_lateral.second = casilla_central.second + (del_3_al_4.second * lateral);
			vision.insert(casilla_lateral);
		}
	}

	return (vision.find(make_pair(s.f, s.c)) != vision.end());
}

/*
	Estructura básica

	list <Action> ComportamientoJugador::AnchuraLvl1(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){
    
	node nodo_general;
	list<node> frontera;
	set<node> explorados;

	//nodo general ahora mismo es el instante inicial
	nodo_general.st = inicio;

	frontera.push_back(nodo_general);
	explorados.insert(nodo_general);

    vector<Action> acciones_posibles = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR};

	while (!(nodo_general.st.colaborador == final) && !frontera.empty())
	{
		nodo_general = frontera.front();
		frontera.pop_front();

		for (int i = 0 ; i < acciones_posibles.size() ;i++){ //vamos a generar todos los hijos posibles
			node nodo_hijo = nodo_general;
			nodo_hijo.st = apply(acciones_posibles[i],nodo_general.st,mapa);
			nodo_hijo.secuencia.push_back(acciones_posibles[i]);

			if (explorados.find(nodo_hijo) == explorados.end()){
				frontera.push_back(nodo_hijo);
			}
		}
	}
	
	return nodo_general.secuencia;
	}

*/
