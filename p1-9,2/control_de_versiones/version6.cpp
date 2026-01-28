#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){
	matriz[st.fil][st.col] = terreno[0]; // 0 es la posicion actual;

	for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < ncol ; j++){
          matriz[i][j] = 'P';
          matriz[nfil - i-1][j] = 'P';
          matriz[j][i] = 'P';
          matriz[j][ncol-i-1] = 'P';
        }
	}

	switch(st.brujula){
		case norte:
			matriz[st.fil - 1][st.col - 1] = terreno[1];
			matriz[st.fil - 1][st.col]     = terreno[2];
			matriz[st.fil - 1][st.col + 1] = terreno[3];
			matriz[st.fil - 2][st.col - 2] = terreno[4];
			matriz[st.fil - 2][st.col - 1] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil - 2][st.col] = terreno[6];
			matriz[st.fil - 2][st.col + 1] = terreno[7];
			matriz[st.fil - 2][st.col + 2] = terreno[8];
			matriz[st.fil - 3][st.col - 3] = terreno[9];
			matriz[st.fil - 3][st.col - 2] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil - 3][st.col - 1] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil - 3][st.col]     = terreno[12];
			if (terreno[13] != '?') matriz[st.fil - 3][st.col + 1] = terreno[13]; 
			matriz[st.fil - 3][st.col + 2] = terreno[14];
			matriz[st.fil - 3][st.col + 3] = terreno[15];
			break;

		case sur:
			matriz[st.fil + 1][st.col + 1] = terreno[1];
			matriz[st.fil + 1][st.col]     = terreno[2];
			matriz[st.fil + 1][st.col - 1] = terreno[3];
			matriz[st.fil + 2][st.col + 2] = terreno[4];
			matriz[st.fil + 2][st.col + 1] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil + 2][st.col] = terreno[6];
			matriz[st.fil + 2][st.col - 1] = terreno[7];
			matriz[st.fil + 2][st.col - 2] = terreno[8];
			matriz[st.fil + 3][st.col + 3] = terreno[9];
			matriz[st.fil + 3][st.col + 2] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil + 3][st.col + 1] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil + 3][st.col] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil + 3][st.col - 1] = terreno[13];
			matriz[st.fil + 3][st.col - 2] = terreno[14];
			matriz[st.fil + 3][st.col - 3] = terreno[15];
			break;
		case este:
			matriz[st.fil - 1][st.col + 1] = terreno[1];
			matriz[st.fil][st.col + 1] = terreno[2];
			matriz[st.fil + 1][st.col + 1] = terreno[3];
			matriz[st.fil - 2][st.col + 2] = terreno[4];
			matriz[st.fil - 1][st.col + 2] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil][st.col + 2] = terreno[6];
			matriz[st.fil + 1][st.col + 2] = terreno[7];
			matriz[st.fil + 2][st.col + 2] = terreno[8];
			matriz[st.fil - 3][st.col + 3] = terreno[9];
			matriz[st.fil - 2][st.col + 3] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil - 1][st.col + 3] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil][st.col + 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil + 1][st.col + 3] = terreno[13];
			matriz[st.fil + 2][st.col + 3] = terreno[14];
			matriz[st.fil + 3][st.col + 3] = terreno[15];
			break;
		case oeste:
			matriz[st.fil + 1][st.col - 1] = terreno[1];
			matriz[st.fil][st.col -1 ] = terreno[2];
			matriz[st.fil - 1][st.col - 1] = terreno[3];
			matriz[st.fil + 2][st.col - 2] = terreno[4];
			matriz[st.fil + 1][st.col - 2] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil][st.col - 2] = terreno[6];
			matriz[st.fil - 1][st.col - 2] = terreno[7];
			matriz[st.fil - 2][st.col - 2] = terreno[8];
			matriz[st.fil + 3][st.col - 3] = terreno[9];
			matriz[st.fil + 2][st.col - 3] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil + 1][st.col - 3] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil][st.col - 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil - 1][st.col - 3] = terreno[13];	
			matriz[st.fil - 2][st.col - 3] = terreno[14];
			matriz[st.fil - 3][st.col - 3] = terreno[15];
			break;
		case noreste:
			matriz[st.fil - 1][st.col] = terreno[1];
			matriz[st.fil - 1][st.col + 1] = terreno[2];
			matriz[st.fil][st.col + 1] = terreno[3];
			matriz[st.fil - 2][st.col] = terreno[4];
			matriz[st.fil - 2][st.col + 1] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil - 2][st.col + 2] =	terreno[6];
			matriz[st.fil - 1][st.col + 2] = terreno[7];
			matriz[st.fil][st.col + 2] = terreno[8];
			matriz[st.fil - 3][st.col] = terreno[9];
			matriz[st.fil - 3][st.col + 1] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil - 3][st.col + 2] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil - 3][st.col + 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil - 2][st.col + 3] = terreno[13];	
			matriz[st.fil - 1][st.col + 3] = terreno[14];
			matriz[st.fil][st.col + 3] = terreno[15];
			break;
		case noroeste:
			matriz[st.fil][st.col - 1] = terreno[1];
			matriz[st.fil - 1][st.col - 1] = terreno[2];
			matriz[st.fil - 1][st.col] = terreno[3];
			matriz[st.fil][st.col - 2] = terreno[4];
			matriz[st.fil - 1][st.col - 2] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil - 2][st.col - 2] =	terreno[6];
			matriz[st.fil - 2][st.col - 1] = terreno[7];
			matriz[st.fil - 2][st.col] = terreno[8];
			matriz[st.fil][st.col - 3] = terreno[9];
			matriz[st.fil - 1][st.col - 3] =	terreno[10];
			if (terreno[11] != '?') matriz[st.fil - 2][st.col - 3] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil - 3][st.col - 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil - 3][st.col - 2] = terreno[13];  
			matriz[st.fil - 3][st.col - 1] = terreno[14];
			matriz[st.fil - 3][st.col] = terreno[15];
			break;
		case sureste:
			matriz[st.fil][st.col + 1] = terreno[1];
			matriz[st.fil + 1][st.col + 1] = terreno[2];
			matriz[st.fil + 1][st.col] = terreno[3];
			matriz[st.fil][st.col + 2] = terreno[4];
			matriz[st.fil + 1][st.col + 2] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil + 2][st.col + 2] =	terreno[6];	
			matriz[st.fil + 2][st.col + 1] = terreno[7];
			matriz[st.fil + 2][st.col] = terreno[8];
			matriz[st.fil][st.col + 3] = terreno[9];
			matriz[st.fil + 1][st.col + 3] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil + 2][st.col + 3] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil + 3][st.col + 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil + 3][st.col + 2] = terreno[13];	
			matriz[st.fil + 3][st.col + 1] = terreno[14];
			matriz[st.fil + 3][st.col] = terreno[15];
			break;
		case suroeste:
			matriz[st.fil + 1][st.col] = terreno[1];
			matriz[st.fil + 1][st.col - 1] = terreno[2];
			matriz[st.fil][st.col - 1] = terreno[3];
			matriz[st.fil + 2][st.col] = terreno[4];
			matriz[st.fil + 2][st.col - 1] = terreno[5];
			if (terreno[6] != '?') matriz[st.fil + 2][st.col - 2] =	terreno[6];
			matriz[st.fil + 1][st.col - 2] = terreno[7];
			matriz[st.fil][st.col - 2] = terreno[8];
			matriz[st.fil + 3][st.col] = terreno[9];
			matriz[st.fil + 3][st.col - 1] = terreno[10];
			if (terreno[11] != '?') matriz[st.fil + 3][st.col - 2] = terreno[11];
			if (terreno[12] != '?') matriz[st.fil + 3][st.col - 3] = terreno[12];
			if (terreno[13] != '?') matriz[st.fil + 2][st.col - 3] = terreno[13];
			matriz[st.fil + 1][st.col - 3] = terreno[14];
			matriz[st.fil][st.col - 3] = terreno[15];
			break;
	}
}

Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;
	int a;

	showInfoParameters(sensores);

	if (sensores.reset){
		last_action = actIDLE;
		girar_derecha = false;

		bien_situado = false;

		tiene_zapatillas = false;
		tiene_bikini = false;

		pudo_continuar = true;

		ciclos_recargando = 0;
		contador = 0;

		current_state.fil = 99;
		current_state.col = 99;
		current_state.brujula = norte;

		aux_state.fil = nfilAux/2;
		aux_state.col = ncolAux/2;
		current_state.brujula = norte;

		for (int i = 0 ; i < nfilAux ; i++){
        	for (int j = 0 ; j < ncolAux ; j++){
          		matriz_aux[i][j] = '?';
        	}
     	}
	}

	//pendiente de revisar para ajustarlo a la nueva forma
	switch (last_action)
	{
		case actWALK:
			switch (current_state.brujula){
				case norte: current_state.fil--; break;
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--; break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}

			break;
		case actRUN:
			break;
		case actTURN_SR:
			a = current_state.brujula;
			a = (a+1)%8;
			current_state.brujula = static_cast<Orientacion>(a);

			break;

		case actTURN_L:
			a = current_state.brujula;
			a = (a+6)%8;
			current_state.brujula = static_cast<Orientacion>(a);

			break;

		case actIDLE:
			break;
	}

	//bloque de actualizacion de la posicion auxiliar.
	if (sensores.nivel != 3 && sensores.nivel != 1 && !bien_situado){
		int b;		
			switch (last_action){
				case actWALK:
					switch (aux_state.brujula){
						case norte:	aux_state.fil--; break;
						case noreste: aux_state.fil--; aux_state.fil++;	break;
						case este: aux_state.fil++; break;
						case sureste: aux_state.fil++; aux_state.fil++;	break;
						case sur: aux_state.fil++;	break;
						case suroeste: aux_state.fil++; aux_state.fil--; break;
						case oeste: aux_state.fil--; break;
						case noroeste: aux_state.fil--; aux_state.fil--; break;
					}

				break;
			
				case actTURN_SR:
					b = aux_state.brujula;
					b = (b + 1) % 8;
					aux_state.brujula = static_cast<Orientacion>(b);
				break;

				case actTURN_L:
					b = aux_state.brujula;
					b = (a + 6) % 8; 
					aux_state.brujula = static_cast<Orientacion>(b);
				break;
			}
	}

	
	//gestion de cuando se encuentra un G y no conocia su posicion en los niveles 1 y 2
	// if (sensores.terreno[0] == 'G' && !bien_situado && sensores.nivel != 0 && sensores.nivel != 3){
	// 	int dif_fil = aux_state.fil - current_state.fil; 
	// 	int dif_col = aux_state.col - current_state.col;
	
	// 	int resta = ((current_state.brujula - aux_state.brujula) + 8) % 8;
	// 	Orientacion inicial = static_cast<Orientacion>(resta);

	// 	for (int i = 0; i < nfilAux; i++) {
	// 		for (int j = 0; j < ncolAux; j++) {
	// 			if (matriz_aux[i][j] != '?') {
	// 				mapaResultado[i - dif_fil][j - dif_col] = matriz_aux[i][j];
	// 			}
	// 		}
	// 	}

	// 	bien_situado = true;
	// 	current_state.fil = sensores.posF;
	// 	current_state.col = sensores.posC;
	// 	current_state.brujula = sensores.sentido;
		
	// }

	if (sensores.nivel == 0){
		bien_situado = true;
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;

		PonerTerrenoEnMatriz(sensores.terreno,current_state,mapaResultado);
	}
	else
	{
		if (sensores.terreno[0] == 'G' && !bien_situado){
			bien_situado = true;
			current_state.fil = sensores.posF;
			current_state.col = sensores.posC;
			current_state.brujula = sensores.sentido;
		}

		if (bien_situado){
			PonerTerrenoEnMatriz(sensores.terreno,current_state,mapaResultado);
		}
	}
	

	// if (bien_situado){
	// 	PonerTerrenoEnMatriz(sensores.terreno,current_state,mapaResultado);
	// }
	// else
	// {
	// 	pintaMatrizAuxiliar(aux_state,sensores);
	// }
	

	accion = dirigeEnCono(current_state,sensores);
	
	if (accion == actWALK && !_canStepOn(sensores)){
		accion = actIDLE;
	}
	
	if (accion == actIDLE){
		cout << "no esta dirigiendose" << endl;

		contador++;
		int const ciclos_reactivacion = 50;

		if (contador == ciclos_reactivacion){
			pudo_continuar = true;
			contador = 0;
		}

		if (accion == actIDLE){
			int random = rand() % 100;

			if (random < 90){
				if (_canStepOn(sensores)){
					accion = actWALK;
				}
				else if (rand() % 2 == 0)
				{	//que compruebe lo que tiene a la derecha y sino que vaya hacia la izquierda
					accion = actTURN_SR;
				}
				else
				{
					accion = actTURN_L;
				}
			}
			else if (random < 95)
			{
				accion = actTURN_SR;
			}
			else
			{
				accion = actTURN_L;
			}
		}
	}

	if (sensores.terreno[0] == 'K'){
		tiene_bikini = true;
	}
	else if (sensores.terreno[0] == 'D'){
		tiene_zapatillas = true;
	}
	else if (sensores.terreno[0] == 'X' && sensores.bateria < 3500 && ciclos > 1500){
		while (ciclos_recargando < 100)
		{
			ciclos_recargando++;

			last_action = actIDLE;
			return actIDLE;
		}
		
		ciclos_recargando = 0;
	}

	if (accion == actWALK){
		veces_misma_posicion = 0;
	}
	else
	{
		veces_misma_posicion++;
	}
	

	last_action = accion;
	ciclos--;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

void ComportamientoJugador::showInfoParameters(Sensores sensores){
	// Mostrar el valor de los sensores
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC;
	switch (sensores.sentido)
	{
		case norte:	  cout << " Norte\n";	break;
		case noreste: cout << " Noreste\n";	break;
		case este:    cout << " Este\n";	break;
		case sureste: cout << " Sureste\n";	break;
		case sur:     cout << " Sur\n";	break;
		case suroeste:cout << " Suroeste\n";	break;
		case oeste:   cout << " Oeste\n";	break;
		case noroeste:cout << " Noroeste\n";	break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];

	cout << "  Agentes: ";
	for (int i=0; i<sensores.agentes.size(); i++)
		cout << sensores.agentes[i];

	cout << "\nColision: " << sensores.colision;
	cout << "  Reset: " << sensores.reset;
	cout << "  Vida: " << sensores.vida << endl<< endl;
}

Action ComportamientoJugador::dirigeEnCono(const state &st,Sensores sensores){
	Action accion = actIDLE;

	switch (st.brujula)
	{
	case norte:
		
		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9 ){
					accion = _vaANoroeste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{

					accion = _vaANoreste(st);
				}
				else
				{
					accion = _vaANorte(st);
				}
			}
		}

		break;
	case noreste:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9){
					accion = _vaANorte(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{
					accion = _vaAEste(st);
				}
				else
				{
					accion = _vaANoreste(st);
				}
			}

		}

		break;
	case este:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9 ){
					accion = _vaANoreste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{

					accion = _vaASureste(st);
				}
				else
				{
					accion = _vaAEste(st);
				}
			}
		}

		break;
	case sureste:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9){
					accion = _vaAEste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{
					accion = _vaASur(st);
				}
				else
				{
					accion = _vaASureste(st);
				}
			}

		}

		break;
	case sur:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9 ){
					accion = _vaASureste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{

					accion = _vaASuroeste(st);
				}
				else
				{
					accion = _vaASur(st);
				}
			}
		}

		break;
	case suroeste:
		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9){
					accion = _vaASur(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{
					accion = _vaAOeste(st);
				}
				else
				{
					accion = _vaASuroeste(st);
				}
			}

		}

		break;
	case oeste:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado)
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9 ){
					accion = _vaASuroeste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{

					accion = _vaANoroeste(st);
				}
				else
				{
					accion = _vaAOeste(st);
				}
			}
		}
		break;
	case noroeste:

		for (int i = 0 ; i < sensores.terreno.size() ; i++){
			if ((sensores.terreno[i] == 'G' && !bien_situado) 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)
				|| (sensores.terreno[i] == 'X' && sensores.bateria < 3500 && ciclos > 2000)){	
				if (i == 1 || i == 4 || i == 9){
					accion = _vaAOeste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{
					accion = _vaANorte(st);
				}
				else
				{
					accion = _vaANoroeste(st);
				}
			}

		}
		break;
	}

	return accion;
}

//funciones que acortan el movimiento.
Action ComportamientoJugador::_vaANorte(const state &st){
Action solucion;
int oneTurn = (norte+7)%8;

if (st.brujula == norte){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;

}
Action ComportamientoJugador::_vaASur(const state &st){
Action solucion;
int oneTurn = (sur+7)%8;

if (st.brujula == sur){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaAEste(const state &st){
Action solucion;
int oneTurn = (este+7)%8;

if (st.brujula == este){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaAOeste(const state &st){
Action solucion;
int oneTurn = (oeste+7)%8;

if (st.brujula == oeste){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaANoreste(const state &st){
Action solucion;
int oneTurn = (noreste+7)%8;

if (st.brujula == noreste){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaANoroeste(const state &st){
Action solucion;
int oneTurn = (noroeste+7)%8;

if (st.brujula == noroeste){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaASureste(const state &st){
Action solucion;
int oneTurn = (sureste+7)%8;

if (st.brujula == sureste){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
Action ComportamientoJugador::_vaASuroeste(const state &st){
Action solucion;
int oneTurn = (suroeste+7)%8;

if (st.brujula == suroeste){
	solucion = actWALK;

	// st.fil--;
} 
else
{
	if (st.brujula == oneTurn){
	solucion = actTURN_SR;
	}
	else
	{
	solucion = actTURN_L;
	}
	
}


return solucion;
}
//en principio el metodo canStepOn pierde su sentido al usarse el mapa de calor
bool ComportamientoJugador::_canStepOn(Sensores sensores){

	int limite_bateria;

	if (sensores.nivel == 0){
		limite_bateria = 4800;
	}
	else if (sensores.nivel ==3 )
	{
		limite_bateria = 2750;
	}
	else
	{
		limite_bateria = 2500;
	}

	if (sensores.terreno[2] != 'M' && sensores.terreno[2] != 'P' && veces_misma_posicion > 10){
		return true;
	}

	if (((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'G')
		|| (sensores.terreno[2] == 'A' && (tiene_bikini || sensores.bateria < limite_bateria)) 
		|| (sensores.terreno[2] == 'B' && (tiene_zapatillas || sensores.bateria < limite_bateria))
		|| sensores.terreno[2] == 'K' || sensores.terreno[2] == 'D' || sensores.terreno[2] == 'X')
		&& sensores.agentes[2] == '_'){
      		
		return true;
	}
	else
	{  
		return false;
	} 
}

void ComportamientoJugador::pintaMatrizAuxiliar(const state &st, Sensores sensores){

	switch (st.brujula)
	{
	case 0:
		matriz_aux[st.fil-1][st.col-1] = sensores.terreno[1];
		matriz_aux[st.fil-1][st.col]   = sensores.terreno[2];
		matriz_aux[st.fil-1][st.col+1] = sensores.terreno[3];
		matriz_aux[st.fil-2][st.col-2] = sensores.terreno[4];
		matriz_aux[st.fil-2][st.col-1] = sensores.terreno[5];
		matriz_aux[st.fil-2][st.col]   = sensores.terreno[6];
		matriz_aux[st.fil-2][st.col+1] = sensores.terreno[7];
		matriz_aux[st.fil-2][st.col+2] = sensores.terreno[8];
		matriz_aux[st.fil-3][st.col-3] = sensores.terreno[9];
		matriz_aux[st.fil-3][st.col-2] = sensores.terreno[10];
		matriz_aux[st.fil-3][st.col-1] = sensores.terreno[11];
		matriz_aux[st.fil-3][st.col]   = sensores.terreno[12];
		matriz_aux[st.fil-3][st.col+1] = sensores.terreno[13];
		matriz_aux[st.fil-3][st.col+2] = sensores.terreno[14];
		matriz_aux[st.fil-3][st.col+3] = sensores.terreno[15];
		break;
	case 1:
		matriz_aux[st.fil-1][st.col]   = sensores.terreno[1];
		matriz_aux[st.fil-1][st.col+1] = sensores.terreno[2];
		matriz_aux[st.fil][st.col+1]   = sensores.terreno[3];
		matriz_aux[st.fil-2][st.col]   = sensores.terreno[4];
		matriz_aux[st.fil-2][st.col+1] = sensores.terreno[5];
		matriz_aux[st.fil-2][st.col+2] = sensores.terreno[6];
		matriz_aux[st.fil-1][st.col+2] = sensores.terreno[7];
		matriz_aux[st.fil][st.col+2]   = sensores.terreno[8];
		matriz_aux[st.fil-3][st.col]   = sensores.terreno[9];
		matriz_aux[st.fil-3][st.col+1] = sensores.terreno[10];
		matriz_aux[st.fil-3][st.col+2] = sensores.terreno[11];
		matriz_aux[st.fil-3][st.col+3] = sensores.terreno[12];
		matriz_aux[st.fil-2][st.col+3] = sensores.terreno[13];
		matriz_aux[st.fil-1][st.col+3] = sensores.terreno[14];
		matriz_aux[st.fil][st.col+3]   = sensores.terreno[15];
		break;
	case 2:
		matriz_aux[st.fil-1][st.col+1] = sensores.terreno[1];
		matriz_aux[st.fil][st.col+1]   = sensores.terreno[2];
		matriz_aux[st.fil+1][st.col+1] = sensores.terreno[3];
		matriz_aux[st.fil-2][st.col+2] = sensores.terreno[4];
		matriz_aux[st.fil-1][st.col+2] = sensores.terreno[5];
		matriz_aux[st.fil][st.col+2]   = sensores.terreno[6];
		matriz_aux[st.fil+1][st.col+2] = sensores.terreno[7];
		matriz_aux[st.fil+2][st.col+2] = sensores.terreno[8];
		matriz_aux[st.fil-3][st.col+3] = sensores.terreno[9];
		matriz_aux[st.fil-2][st.col+3] = sensores.terreno[10];
		matriz_aux[st.fil-1][st.col+3] = sensores.terreno[11];
		matriz_aux[st.fil][st.col+3]   = sensores.terreno[12];
		matriz_aux[st.fil+1][st.col+3] = sensores.terreno[13];
		matriz_aux[st.fil+2][st.col+3] = sensores.terreno[14];
		matriz_aux[st.fil+3][st.col+3] = sensores.terreno[15];
		break;
	case 3:
		matriz_aux[st.fil+1][st.col]   = sensores.terreno[3];
		matriz_aux[st.fil+1][st.col+1] = sensores.terreno[2];
		matriz_aux[st.fil][st.col+1]   = sensores.terreno[1];
		matriz_aux[st.fil+2][st.col]   = sensores.terreno[8];
		matriz_aux[st.fil+2][st.col+1] = sensores.terreno[7];
		matriz_aux[st.fil+2][st.col+2] = sensores.terreno[6];
		matriz_aux[st.fil+1][st.col+2] = sensores.terreno[5];
		matriz_aux[st.fil][st.col+2]   = sensores.terreno[4];
		matriz_aux[st.fil+3][st.col]   = sensores.terreno[15];
		matriz_aux[st.fil+3][st.col+1] = sensores.terreno[14];
		matriz_aux[st.fil+3][st.col+2] = sensores.terreno[13];
		matriz_aux[st.fil+3][st.col+3] = sensores.terreno[12];
		matriz_aux[st.fil+2][st.col+3] = sensores.terreno[11];
		matriz_aux[st.fil+1][st.col+3] = sensores.terreno[10];
		matriz_aux[st.fil][st.col+3]   = sensores.terreno[9];
		break;
	case 4:
		matriz_aux[st.fil+1][st.col+1] = sensores.terreno[1];
		matriz_aux[st.fil+1][st.col]   = sensores.terreno[2];
		matriz_aux[st.fil+1][st.col-1] = sensores.terreno[3];
		matriz_aux[st.fil+2][st.col+2] = sensores.terreno[4];
		matriz_aux[st.fil+2][st.col+1] = sensores.terreno[5];
		matriz_aux[st.fil+2][st.col]   = sensores.terreno[6];
		matriz_aux[st.fil+2][st.col-1] = sensores.terreno[7];
		matriz_aux[st.fil+2][st.col-2] = sensores.terreno[8];
		matriz_aux[st.fil+3][st.col+3] = sensores.terreno[9];
		matriz_aux[st.fil+3][st.col+2] = sensores.terreno[10];
		matriz_aux[st.fil+3][st.col+1] = sensores.terreno[11];
		matriz_aux[st.fil+3][st.col]   = sensores.terreno[12];
		matriz_aux[st.fil+3][st.col-1] = sensores.terreno[13];
		matriz_aux[st.fil+3][st.col-2] = sensores.terreno[14];
		matriz_aux[st.fil+3][st.col-3] = sensores.terreno[15];
		break;
	case 5:
		matriz_aux[st.fil+1][st.col]   = sensores.terreno[1];
		matriz_aux[st.fil+1][st.col-1] = sensores.terreno[2];
		matriz_aux[st.fil][st.col-1]   = sensores.terreno[3];
		matriz_aux[st.fil+2][st.col]   = sensores.terreno[4];
		matriz_aux[st.fil+2][st.col-1] = sensores.terreno[5];
		matriz_aux[st.fil+2][st.col-2] = sensores.terreno[6];
		matriz_aux[st.fil+1][st.col-2] = sensores.terreno[7];
		matriz_aux[st.fil][st.col-2]   = sensores.terreno[8];
		matriz_aux[st.fil+3][st.col]   = sensores.terreno[9];
		matriz_aux[st.fil+3][st.col-1] = sensores.terreno[10];
		matriz_aux[st.fil+3][st.col-2] = sensores.terreno[11];
		matriz_aux[st.fil+3][st.col-3] = sensores.terreno[12];
		matriz_aux[st.fil+2][st.col-3] = sensores.terreno[13];
		matriz_aux[st.fil+1][st.col-3] = sensores.terreno[14];
		matriz_aux[st.fil][st.col-3]   = sensores.terreno[15];
		break;
	case 6:
		matriz_aux[st.fil+1][st.col-1] = sensores.terreno[1];
		matriz_aux[st.fil][st.col-1]   = sensores.terreno[2];
		matriz_aux[st.fil-1][st.col-1] = sensores.terreno[3];
		matriz_aux[st.fil+2][st.col-2] = sensores.terreno[4];
		matriz_aux[st.fil+1][st.col-2] = sensores.terreno[5];
		matriz_aux[st.fil][st.col-2]   = sensores.terreno[6];
		matriz_aux[st.fil-1][st.col-2] = sensores.terreno[7];
		matriz_aux[st.fil-2][st.col-2] = sensores.terreno[8];
		matriz_aux[st.fil+3][st.col-3] = sensores.terreno[9];
		matriz_aux[st.fil+2][st.col-3] = sensores.terreno[10];
		matriz_aux[st.fil+1][st.col-3] = sensores.terreno[11];
		matriz_aux[st.fil][st.col-3]   = sensores.terreno[12];
		matriz_aux[st.fil-1][st.col-3] = sensores.terreno[13];
		matriz_aux[st.fil-2][st.col-3] = sensores.terreno[14];
		matriz_aux[st.fil-3][st.col-3] = sensores.terreno[15];
		break;
	case 7:

		matriz_aux[st.fil-1][st.col]   = sensores.terreno[3];
		matriz_aux[st.fil-1][st.col-1] = sensores.terreno[2];
		matriz_aux[st.fil][st.col-1]   = sensores.terreno[1];
		matriz_aux[st.fil-2][st.col]   = sensores.terreno[8];
		matriz_aux[st.fil-2][st.col-1] = sensores.terreno[7];
		matriz_aux[st.fil-2][st.col-2] = sensores.terreno[6];
		matriz_aux[st.fil-1][st.col-2] = sensores.terreno[5];
		matriz_aux[st.fil][st.col-2]   = sensores.terreno[4];
		matriz_aux[st.fil-3][st.col]   = sensores.terreno[15];
		matriz_aux[st.fil-3][st.col-1] = sensores.terreno[14];
		matriz_aux[st.fil-3][st.col-2] = sensores.terreno[13];
		matriz_aux[st.fil-3][st.col-3] = sensores.terreno[12];
		matriz_aux[st.fil-2][st.col-3] = sensores.terreno[11];
		matriz_aux[st.fil-1][st.col-3] = sensores.terreno[10];
		matriz_aux[st.fil][st.col-3]   = sensores.terreno[9];
		break;
	}
}