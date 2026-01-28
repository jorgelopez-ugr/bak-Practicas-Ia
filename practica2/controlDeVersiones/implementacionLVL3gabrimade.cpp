#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>

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
			c_state.ultimaOrdenColaborador = act_CLB_STOP;

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

				case 2: 
					cout << "calculamos nuevo plan\n";
					plan = DijkstraLvl2(c_state,goal,mapaResultado);
					VisualizarPlan(c_state,plan);
					cout << "se esta implementando el nivel 2";
				break;

				case 3:
					// plan = AnchuraN3(c_state,goal,mapaResultado);
					plan = AnchuraLvl3(c_state,goal,mapaResultado);
					VisualizarPlan(c_state,plan);
					cout << "se esta implementando el nivel 3";
				break;
				}

				// VisualizarPlan(c_state,plan);
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
     
	return next;

}

state ComportamientoJugador::apply(const Action &a, const state &st, const vector<vector<unsigned char> > &mapa){
	
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

				if (CasillaTransitable(sig_ubicacion2,mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
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

			if (colaboradorEnRangoVision(st_result) || esLlamadaRecursiva){
				sig_ubicacion = NextCasilla(st.colaborador);
				st_result.ultimaOrdenColaborador = act_CLB_WALK;

				if (CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
					st_result.colaborador = sig_ubicacion;
				}

				esLlamadaRecursiva = false;
			}

			break;

		case act_CLB_TURN_SR:

			if (colaboradorEnRangoVision(st_result) || esLlamadaRecursiva){
				st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
				st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;
				esLlamadaRecursiva = false;
			}

			break;

		case act_CLB_STOP:

			if (colaboradorEnRangoVision(st_result) || esLlamadaRecursiva){
				st_result.ultimaOrdenColaborador = act_CLB_STOP;
				esLlamadaRecursiva = false;
			}

			break;
    }

	if (a != act_CLB_STOP && a != act_CLB_TURN_SR && a != act_CLB_WALK){
		esLlamadaRecursiva = true;
		st_result = apply(st_result.ultimaOrdenColaborador,st_result,mapa);
	}

	// if (a != act_CLB_STOP && a != act_CLB_TURN_SR && a != act_CLB_WALK){
	// 	// st_result = apply(st_result.ultimaOrdenColaborador,st_result,mapa);

	// 	switch (st_result.ultimaOrdenColaborador)
    //     {
    //     case act_CLB_WALK:
    //         sig_ubicacion = NextCasilla(st_result.colaborador);
    //         if (CasillaTransitable(sig_ubicacion, mapa) and
    //              not(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c))
    //         {
    //             st_result.colaborador = sig_ubicacion;
    //         }

    //         break;

    //     case act_CLB_TURN_SR:
    //         st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula + 1) % 8);
    //         break;

    //     case act_CLB_STOP:
    //         break;
    //     }
	// }

    return st_result;
}

state ComportamientoJugador::apply2(const Action &a, const state &st, const vector<vector<unsigned char> > &mapa){
	
    state st_result = st;
    ubicacion sig_ubicacion,sig_ubicacion2;
    
    switch(a)
	{
		case act_CLB_WALK:
			sig_ubicacion = NextCasilla(st.colaborador);
			st_result.ultimaOrdenColaborador = act_CLB_WALK;

			if (CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
				st_result.colaborador = sig_ubicacion;
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

list <Action> ComportamientoJugador::AnchuraSoloJugador_V3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){

	node current_node;
	list<node> frontier; //frontera
	set<node> explored; //explorados
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
    set<node> explorados; // explorados
    list<node> frontera; // frontera
    list<Action> planN;
    list<Action> todas_acciones = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR, act_CLB_STOP};
	bool haySolucion = false;

	frontera.push_back(current_node);

    while (!(current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c) && !frontera.empty() && !haySolucion){

		current_node = frontera.front();
		frontera.pop_front();

		if (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c){
			haySolucion = true;
			continue;
		}

		while(!frontera.empty() && !(explorados.find(current_node) == explorados.end())){
			current_node = frontera.front();
			frontera.pop_front();
		}
		
		explorados.insert(current_node);

		clbEnVision = colaboradorEnRangoVision(current_node.st);

        for (auto accion : todas_acciones){
			node child_node = current_node;

			if (!clbEnVision && (accion == act_CLB_STOP || accion == act_CLB_TURN_SR || accion == act_CLB_WALK)){
				child_node.st = apply2(current_node.st.ultimaOrdenColaborador, current_node.st, mapa);
				child_node.secuencia.push_back(current_node.st.ultimaOrdenColaborador);
			}
			else {
				child_node.st = apply(accion, current_node.st, mapa);
				child_node.secuencia.push_back(accion);
			}

			if (explorados.find(child_node) == explorados.end()){
				frontera.push_back(child_node);
				// explorados.insert(child_node);
			}
		}
  	}


    planN = current_node.secuencia;
	//cout << "6.5" << endl;
    PintaPlan(planN);
	//cout << "7" << endl;
    return planN;

}

list <Action> ComportamientoJugador::DijkstraLvl2(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){

	node2 current_node;
	current_node.nodoBasico.st = inicio;
	current_node.coste_total_secuencia = 0;
	
	current_node.tieneBikini = false;
	current_node.tieneZapatillas = false;

	if(mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c] == 'K'){
		current_node.tieneBikini = true;
		current_node.tieneZapatillas = false;
	}
	else if (mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c] == 'D')
	{
		current_node.tieneBikini = false;
		current_node.tieneZapatillas = true;
	}

	priority_queue<node2,vector<node2>,ordenarCola> frontera;
	set<node2> explorados;
	
	list<Action> planLVL2;
	list<Action> todas_acciones = {actWALK, actRUN, actTURN_L, actTURN_SR, actIDLE};

	frontera.push(current_node);
	bool encontrado = false;

    while (!frontera.empty() && !encontrado)
	{
		current_node = frontera.top();
		frontera.pop();
		
		while(!frontera.empty() && explorados.find(current_node) != explorados.end()){
			current_node = frontera.top();
			frontera.pop();
		}

		if (current_node.nodoBasico.st.jugador.f == final.f && current_node.nodoBasico.st.jugador.c == final.c){
			encontrado = true;
			continue;
		}

		explorados.insert(current_node);

		for (auto accion : todas_acciones){
			node2 child_node = current_node;
			child_node.nodoBasico.st = apply(accion,current_node.nodoBasico.st,mapa);

			if (mapa[child_node.nodoBasico.st.jugador.f][child_node.nodoBasico.st.jugador.c] == 'K'){
				child_node.tieneBikini = true;
				child_node.tieneZapatillas = false;
			}
			else if (mapa[child_node.nodoBasico.st.jugador.f][child_node.nodoBasico.st.jugador.c] == 'D')
			{
				child_node.tieneBikini = false;
				child_node.tieneZapatillas = true;
			}

			// child_node.coste_total_secuencia += calculaCosteDelPaso(accion,mapa[child_node.st.jugador.f][child_node.st.jugador.c],child_node);
			child_node.coste_total_secuencia += calculaCosteDelPaso(accion,mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c],child_node);

			child_node.nodoBasico.secuencia.push_back(accion);
			
			frontera.push(child_node);
		}
	}

	planLVL2 = current_node.nodoBasico.secuencia;
	PintaPlan(planLVL2);
	return planLVL2;
}

list <Action> ComportamientoJugador::AnchuraLvl3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){
	
	node3 current_node;
    current_node.nodoBasico.st = inicio;
	current_node.coste_total_secuencia = 0;

	if (mapa[current_node.nodoBasico.st.colaborador.f][current_node.nodoBasico.st.colaborador.c] == 'K'){
		current_node.tieneBikini_colab = true;
		current_node.tieneZapatillas_colab = false;
	}
	else if (mapa[current_node.nodoBasico.st.colaborador.f][current_node.nodoBasico.st.colaborador.c] == 'D'){
		current_node.tieneBikini_colab = false;
		current_node.tieneZapatillas_colab = true;
	}

	if (mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c] == 'K'){
		current_node.tieneBikini_jugador = true;
		current_node.tieneZapatillas_jugador = false;
	}
	else if (mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c] == 'D'){
		current_node.tieneBikini_jugador = false;
		current_node.tieneZapatillas_jugador = true;
	}

    set<node3> explorados; // explorados
	priority_queue<node3,vector<node3>,ordenarCola3> frontera;
    list<Action> planN;
    list<Action> todas_acciones = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR, act_CLB_STOP};
	bool haySolucion = false;
	bool fueraDeVista = false;

	frontera.push(current_node);

    while (!frontera.empty() && !haySolucion){

		current_node = frontera.top();
		frontera.pop();

		while(!frontera.empty() && explorados.find(current_node) != explorados.end()){
			current_node = frontera.top();
			frontera.pop();
		}

		if (current_node.nodoBasico.st.colaborador.f == final.f && current_node.nodoBasico.st.colaborador.c == final.c){
			haySolucion = true;
			break;
		}
		
		explorados.insert(current_node);

		clbEnVision = colaboradorEnRangoVision(current_node.nodoBasico.st);

        for (auto accion : todas_acciones){
			node3 child_node = current_node;

			if (accion == act_CLB_STOP || accion == act_CLB_WALK || accion == act_CLB_TURN_SR){
				//accion para el colaborador
				if (clbEnVision){

					child_node.coste_total_secuencia += calculaCosteDelPaso(accion,mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c],child_node);

					child_node.nodoBasico.st = apply(accion,current_node.nodoBasico.st,mapa);
					child_node.nodoBasico.secuencia.push_back(accion);

					child_node.coste_heuristico = costeHeuristico(child_node.nodoBasico.st,final) + child_node.coste_total_secuencia;

					if (mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c] == 'K'){
						child_node.tieneBikini_colab = true;
						child_node.tieneZapatillas_colab = false;
					}
					else if (mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c] == 'D'){
						child_node.tieneBikini_colab = false;
						child_node.tieneZapatillas_colab = true;
					}
				}
				else
				{
					//colaborador no a la vista
					child_node.coste_total_secuencia += calculaCosteDelPaso(accion,mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c],child_node);

					child_node.nodoBasico.st = apply2(current_node.nodoBasico.st.ultimaOrdenColaborador,current_node.nodoBasico.st,mapa);
					child_node.nodoBasico.secuencia.push_back(current_node.nodoBasico.st.ultimaOrdenColaborador);

					child_node.coste_heuristico = costeHeuristico(child_node.nodoBasico.st,final) + child_node.coste_total_secuencia;


					// cout << "ha entrado aqui";


					if (mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c] == 'K'){
						child_node.tieneBikini_colab = true;
						child_node.tieneZapatillas_colab = false;
					}
					else if (mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c] == 'D'){
						child_node.tieneBikini_colab = false;
						child_node.tieneZapatillas_colab = true;
					}

					accion = current_node.nodoBasico.st.ultimaOrdenColaborador;
					// fueraDeVista = true;
				}
			}
			else
			{
				//acciones para el jugador
				child_node.coste_total_secuencia += calculaCosteDelPaso(accion,mapa[child_node.nodoBasico.st.colaborador.f][child_node.nodoBasico.st.colaborador.c],child_node);

				child_node.nodoBasico.st = apply(accion,current_node.nodoBasico.st,mapa);
				child_node.nodoBasico.secuencia.push_back(accion);

				child_node.coste_heuristico = costeHeuristico(child_node.nodoBasico.st,final) + child_node.coste_total_secuencia;

				if (mapa[child_node.nodoBasico.st.jugador.f][child_node.nodoBasico.st.jugador.c] == 'K'){
					child_node.tieneBikini_jugador = true;
					child_node.tieneZapatillas_jugador = false;
				}
				else if (mapa[child_node.nodoBasico.st.jugador.f][child_node.nodoBasico.st.jugador.c] == 'D'){
					child_node.tieneBikini_jugador = false;
					child_node.tieneZapatillas_jugador = true;
				}
			}

			if (explorados.find(child_node) == explorados.end()){
				
				// if (fueraDeVista){
				// 	child_node.coste_total_secuencia = current_node.coste_total_secuencia + costeHeuristico(current_node.nodoBasico.st,final) + calculaCosteDelPaso(current_node.nodoBasico.st.ultimaOrdenColaborador,mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c],child_node);
				// 	fueraDeVista = false;
				// }
				// else{
					// child_node.coste_total_secuencia = current_node.coste_total_secuencia + costeHeuristico(current_node.nodoBasico.st,final) + calculaCosteDelPaso(accion,mapa[current_node.nodoBasico.st.jugador.f][current_node.nodoBasico.st.jugador.c],child_node);
				// }

				// child_node.coste_total_secuencia = current_node.coste_total_secuencia + costeHeuristico(current_node.nodoBasico.st,final);


				// cout << "el coste es: " << child_node.coste	_total_secuencia;

				// if (child_node.coste_total_secuencia < current_node.coste_total_secuencia){
					frontera.push(child_node);
				// }	
			}	
		}
  	}

	if (haySolucion){
		cout << "salio porque encontro solucion";
	}
	else
	{
		cout << "salio por frontera empty";
	}

    planN = current_node.nodoBasico.secuencia;
    PintaPlan(planN);
    return planN;

	// // node current_node;
	// node3 current_node;
	// // node2 current_node;
    // current_node.nodoBasico.st = inicio;
	// // current_node.st = inicio;

    // // set<node> explorados; // explorados
    // // list<node> frontera; // frontera

	// set<node3> explorados;
	// list<node3> frontera;

	// // set<node2> explorados;
	// // list<node2> frontera;

    // list<Action> planN;
    // list<Action> todas_acciones = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR};
	// bool haySolucion = false;

	// frontera.push_back(current_node);

    // while (!(current_node.nodoBasico.st.colaborador.f == final.f && current_node.nodoBasico.st.colaborador.c == final.c) && !frontera.empty() && !haySolucion){
	// // while (!(current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c) && !frontera.empty() && !haySolucion){


	// 	current_node = frontera.front();
	// 	frontera.pop_front();

	// 	if (current_node.nodoBasico.st.colaborador.f == final.f && current_node.nodoBasico.st.colaborador.c == final.c){
	// 	// if (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c){

	// 		haySolucion = true;
	// 		continue;
	// 	}

	// 	while(!frontera.empty() && !(explorados.find(current_node) == explorados.end())){
	// 		current_node = frontera.front();
	// 		frontera.pop_front();
	// 	}
		
	// 	explorados.insert(current_node);

	// 	clbEnVision = colaboradorEnRangoVision(current_node.nodoBasico.st);
	// 	// clbEnVision = colaboradorEnRangoVision(current_node.st);

    //     for (auto accion : todas_acciones){
	// 		// node child_node = current_node;
	// 		node3 child_node = current_node;
	// 		// node2 child_node = current_node;


	// 		if (!clbEnVision && (accion == act_CLB_STOP || accion == act_CLB_TURN_SR || accion == act_CLB_WALK)){
	// 			child_node.nodoBasico.st = apply2(current_node.nodoBasico.st.ultimaOrdenColaborador, current_node.nodoBasico.st, mapa);
	// 			child_node.nodoBasico.secuencia.push_back(current_node.nodoBasico.st.ultimaOrdenColaborador);
			
	// 			// child_node.st = apply2(current_node.st.ultimaOrdenColaborador, current_node.st, mapa);
	// 			// child_node.secuencia.push_back(current_node.st.ultimaOrdenColaborador);

	// 		}
	// 		else {
	// 			child_node.nodoBasico.st = apply(accion, current_node.nodoBasico.st, mapa);
	// 			child_node.nodoBasico.secuencia.push_back(accion);

	// 			// child_node.st = apply(accion, current_node.st, mapa);
	// 			// child_node.secuencia.push_back(accion);

	// 		}

	// 		if (explorados.find(child_node) == explorados.end()){
	// 			frontera.push_back(child_node);
	// 			// explorados.insert(child_node);
	// 		}
	// 	}
  	// }


    // planN = current_node.nodoBasico.secuencia;
    // // planN = current_node.secuencia;

	// //cout << "6.5" << endl;
    // PintaPlan(planN);
	// //cout << "7" << endl;
    // return planN;

}

int ComportamientoJugador::calculaCosteDelPaso(Action accion,char casilla,const node2 &nodo){

	bool bikini = nodo.tieneBikini;
	bool zapas = nodo.tieneZapatillas;

	if (accion == actWALK){
		if (casilla == 'A' && !bikini){
			return 100;
		}
		else if (casilla == 'A' && bikini){
			return 10;
		}
		else if (casilla == 'B' && !zapas){
			return 50;
		}
		else if (casilla == 'B' && zapas){
			return 15;
		}
		else if (casilla == 'T'){
			return 2;
		}
		else
		{
			return 1;
		}
	} else if (accion == actRUN){
		if (casilla == 'A' && !bikini){
			return 150;
		}
		else if (casilla == 'A' && bikini){
			return 15;
		}
		else if (casilla == 'B' && !zapas){
			return 75;
		}
		else if (casilla == 'B' && zapas){
			return 25;
		}
		else if (casilla == 'T'){
			return 3;
		}
		else
		{
			return 1;
		}
	} else if (accion == actTURN_L){
		if (casilla == 'A' && !bikini){
			return 30;
		}
		else if (casilla == 'A' && bikini){
			return 5;
		}
		else if (casilla == 'B' && !zapas){
			return 7;
		}
		else if (casilla == 'B' && zapas){
			return 1;
		}
		else if (casilla == 'T'){
			return 2;
		}
		else
		{
			return 1;
		}
	} else if (accion == actTURN_SR){
		if (casilla == 'A' && !bikini){
			return 10;
		}
		else if (casilla == 'A' && bikini){
			return 2;
		}
		else if (casilla == 'B' && !zapas){
			return 5;
		}
		else if (casilla == 'B' && zapas){
			return 1;
		}
		else if (casilla == 'T'){
			return 1;
		}
		else
		{
			return 1;
		}
	}

	// cout << "no entro en ninguno" << endl << endl << endl;
	// return 0;
}

int ComportamientoJugador::calculaCosteDelPaso(Action accion,char casilla,const node3 &nodo){

	if (accion == act_CLB_WALK || accion == actWALK){
		if (accion == actWALK){	
			if (casilla == 'A' && !nodo.tieneBikini_jugador){
				return 100;
			}
			else if (casilla == 'A' && nodo.tieneBikini_jugador){
				return 10;
			}
			else if (casilla == 'B' && !nodo.tieneZapatillas_jugador){
				return 50;
			}
			else if (casilla == 'B' && nodo.tieneZapatillas_jugador){
				return 15;
			}
			else if (casilla == 'T'){
				return 2;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if (casilla == 'A' && !nodo.tieneBikini_colab){
				return 100;
			}
			else if (casilla == 'A' && nodo.tieneBikini_colab){
				return 10;
			}
			else if (casilla == 'B' && !nodo.tieneZapatillas_colab){
				return 50;
			}
			else if (casilla == 'B' && nodo.tieneZapatillas_colab){
				return 15;
			}
			else if (casilla == 'T'){
				return 2;
			}
			else
			{
				return 1;
			}
		}
		
	}
	else if (accion == actRUN){
		if (casilla == 'A' && !nodo.tieneBikini_jugador){
			return 150;
		}
		else if (casilla == 'A' && nodo.tieneBikini_jugador){
			return 15;
		}
		else if (casilla == 'B' && !nodo.tieneZapatillas_jugador){
			return 75;
		}
		else if (casilla == 'B' && nodo.tieneZapatillas_jugador){
			return 25;
		}
		else if (casilla == 'T'){
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else if (accion == actTURN_L){
		if (casilla == 'A' && !nodo.tieneBikini_jugador){
			return 30;
		}
		else if (casilla == 'A' && nodo.tieneBikini_jugador){
			return 5;
		}
		else if (casilla == 'B' && !nodo.tieneZapatillas_jugador){
			return 7;
		}
		else if (casilla == 'B' && nodo.tieneZapatillas_jugador){
			return 1;
		}
		else if (casilla == 'T'){
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else if (accion == act_CLB_TURN_SR || accion == actTURN_SR){
		if (accion == act_CLB_TURN_SR){
			if (casilla == 'A' && !nodo.tieneBikini_colab){
				return 10;
			}
			else if (casilla == 'A' && nodo.tieneBikini_colab){
				return 2;
			}
			else if (casilla == 'B' && !nodo.tieneZapatillas_colab){
				return 5;
			}
			else if (casilla == 'B' && nodo.tieneZapatillas_colab){
				return 1;
			}
			else if (casilla == 'T'){
				return 1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if (casilla == 'A' && !nodo.tieneBikini_jugador){
				return 10;
			}
			else if (casilla == 'A' && nodo.tieneBikini_jugador){
				return 2;
			}
			else if (casilla == 'B' && !nodo.tieneZapatillas_jugador){
				return 5;
			}
			else if (casilla == 'B' && nodo.tieneZapatillas_jugador){
				return 1;
			}
			else if (casilla == 'T'){
				return 1;
			}
			else
			{
				return 1;
			}
		}
		
	}
}

int ComportamientoJugador::costeHeuristico(const state &st, ubicacion posi){
	//calculamos para ese estado la suma del valor absoluto de la diferencia de filas y columnas
	//del jugador con el colaborador y el colaborador con la solucion.

	// int vAbsColSol = abs(st.colaborador.f - posi.f) + abs(st.colaborador.c - posi.c);

	// return vAbsColSol;

	// int df = abs(st.jugador.f - goal.f);
    // int dc = abs(st.jugador.c - goal.c);
    // return max(df, dc);

	int df = st.colaborador.f - posi.f;
    int dc = st.colaborador.c - posi.c;
    return sqrt(pow(df,2) + pow(dc,2));
}

bool ComportamientoJugador::colaboradorEnRangoVision(const state &estado){

	bool confirmacion = false;

	switch(estado.jugador.brujula){
		case norte:
			if (
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c - 1 == estado.colaborador.c) ||
			(estado.jugador.f - 1 == estado.colaborador.f && estado.jugador.c + 0== estado.colaborador.c)  ||
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
