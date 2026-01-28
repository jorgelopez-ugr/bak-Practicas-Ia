#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, 
												 const state &st,
												 vector <vector<unsigned char>> &matriz){

	matriz[st.fil][st.col] = terreno[0];

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "¿donde esta ahora mismo?: (" << current_state.fil << "," << current_state.col << ")" << endl;
	cout << "a donde se esta dirigiendo ahora mismo?: (" << posiToward.first.first << "," << posiToward.first.second << ")" << endl;

	cout << "esta dirigiendose? " << endl;
	if (dirigiendose){
		cout << "si se esta dirigiendo" << endl;
	}
	else
	{
		cout << "no se esta dirigiendo, adopta el movimiento default" << endl;
	}

	cout << "¿como esta el valor de la variable no_pudo_continuar? :";
	if (no_pudo_continuar){
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	switch (st.brujula)
	{
	case 0:
		matriz[st.fil-1][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col]   = terreno[2];
		matriz[st.fil-1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col-2] = terreno[4];
		matriz[st.fil-2][st.col-1] = terreno[5];
		matriz[st.fil-2][st.col]   = terreno[6];
		matriz[st.fil-2][st.col+1] = terreno[7];
		matriz[st.fil-2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col-3] = terreno[9];
		matriz[st.fil-3][st.col-2] = terreno[10];
		matriz[st.fil-3][st.col-1] = terreno[11];
		matriz[st.fil-3][st.col]   = terreno[12];
		matriz[st.fil-3][st.col+1] = terreno[13];
		matriz[st.fil-3][st.col+2] = terreno[14];
		matriz[st.fil-3][st.col+3] = terreno[15];
		break;
	case 1:
		matriz[st.fil-1][st.col]   = terreno[1];
		matriz[st.fil-1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1]   = terreno[3];
		matriz[st.fil-2][st.col]   = terreno[4];
		matriz[st.fil-2][st.col+1] = terreno[5];
		matriz[st.fil-2][st.col+2] = terreno[6];
		matriz[st.fil-1][st.col+2] = terreno[7];
		matriz[st.fil][st.col+2]   = terreno[8];
		matriz[st.fil-3][st.col]   = terreno[9];
		matriz[st.fil-3][st.col+1] = terreno[10];
		matriz[st.fil-3][st.col+2] = terreno[11];
		matriz[st.fil-3][st.col+3] = terreno[12];
		matriz[st.fil-2][st.col+3] = terreno[13];
		matriz[st.fil-1][st.col+3] = terreno[14];
		matriz[st.fil][st.col+3]   = terreno[15];
		break;
	case 2:
		matriz[st.fil-1][st.col+1] = terreno[1];
		matriz[st.fil][st.col+1]   = terreno[2];
		matriz[st.fil+1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col+2] = terreno[4];
		matriz[st.fil-1][st.col+2] = terreno[5];
		matriz[st.fil][st.col+2]   = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[7];
		matriz[st.fil+2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col+3] = terreno[9];
		matriz[st.fil-2][st.col+3] = terreno[10];
		matriz[st.fil-1][st.col+3] = terreno[11];
		matriz[st.fil][st.col+3]   = terreno[12];
		matriz[st.fil+1][st.col+3] = terreno[13];
		matriz[st.fil+2][st.col+3] = terreno[14];
		matriz[st.fil+3][st.col+3] = terreno[15];
		break;
	case 3:
		matriz[st.fil+1][st.col]   = terreno[3];
		matriz[st.fil+1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1]   = terreno[1];
		matriz[st.fil+2][st.col]   = terreno[8];
		matriz[st.fil+2][st.col+1] = terreno[7];
		matriz[st.fil+2][st.col+2] = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[5];
		matriz[st.fil][st.col+2]   = terreno[4];
		matriz[st.fil+3][st.col]   = terreno[15];
		matriz[st.fil+3][st.col+1] = terreno[14];
		matriz[st.fil+3][st.col+2] = terreno[13];
		matriz[st.fil+3][st.col+3] = terreno[12];
		matriz[st.fil+2][st.col+3] = terreno[11];
		matriz[st.fil+1][st.col+3] = terreno[10];
		matriz[st.fil][st.col+3]   = terreno[9];
		break;
	case 4:
		matriz[st.fil+1][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col]   = terreno[2];
		matriz[st.fil+1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col+2] = terreno[4];
		matriz[st.fil+2][st.col+1] = terreno[5];
		matriz[st.fil+2][st.col]   = terreno[6];
		matriz[st.fil+2][st.col-1] = terreno[7];
		matriz[st.fil+2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col+3] = terreno[9];
		matriz[st.fil+3][st.col+2] = terreno[10];
		matriz[st.fil+3][st.col+1] = terreno[11];
		matriz[st.fil+3][st.col]   = terreno[12];
		matriz[st.fil+3][st.col-1] = terreno[13];
		matriz[st.fil+3][st.col-2] = terreno[14];
		matriz[st.fil+3][st.col-3] = terreno[15];
		break;
	case 5:
		matriz[st.fil+1][st.col]   = terreno[1];
		matriz[st.fil+1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1]   = terreno[3];
		matriz[st.fil+2][st.col]   = terreno[4];
		matriz[st.fil+2][st.col-1] = terreno[5];
		matriz[st.fil+2][st.col-2] = terreno[6];
		matriz[st.fil+1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2]   = terreno[8];
		matriz[st.fil+3][st.col]   = terreno[9];
		matriz[st.fil+3][st.col-1] = terreno[10];
		matriz[st.fil+3][st.col-2] = terreno[11];
		matriz[st.fil+3][st.col-3] = terreno[12];
		matriz[st.fil+2][st.col-3] = terreno[13];
		matriz[st.fil+1][st.col-3] = terreno[14];
		matriz[st.fil][st.col-3]   = terreno[15];
		break;
	case 6:
		matriz[st.fil+1][st.col-1] = terreno[1];
		matriz[st.fil][st.col-1]   = terreno[2];
		matriz[st.fil-1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col-2] = terreno[4];
		matriz[st.fil+1][st.col-2] = terreno[5];
		matriz[st.fil][st.col-2]   = terreno[6];
		matriz[st.fil-1][st.col-2] = terreno[7];
		matriz[st.fil-2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col-3] = terreno[9];
		matriz[st.fil+2][st.col-3] = terreno[10];
		matriz[st.fil+1][st.col-3] = terreno[11];
		matriz[st.fil][st.col-3]   = terreno[12];
		matriz[st.fil-1][st.col-3] = terreno[13];
		matriz[st.fil-2][st.col-3] = terreno[14];
		matriz[st.fil-3][st.col-3] = terreno[15];
		break;
	case 7:

		matriz[st.fil-1][st.col]   = terreno[3];
		matriz[st.fil-1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1]   = terreno[1];
		matriz[st.fil-2][st.col]   = terreno[8];
		matriz[st.fil-2][st.col-1] = terreno[7];
		matriz[st.fil-2][st.col-2] = terreno[6];
		matriz[st.fil-1][st.col-2] = terreno[5];
		matriz[st.fil][st.col-2]   = terreno[4];
		matriz[st.fil-3][st.col]   = terreno[15];
		matriz[st.fil-3][st.col-1] = terreno[14];
		matriz[st.fil-3][st.col-2] = terreno[13];
		matriz[st.fil-3][st.col-3] = terreno[12];
		matriz[st.fil-2][st.col-3] = terreno[11];
		matriz[st.fil-1][st.col-3] = terreno[10];
		matriz[st.fil][st.col-3]   = terreno[9];
		break;
	}

}

Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;
	int a;

	cout << "¿estoy encerrado?: " << endl ;
	if (estoyEncerrado()){
		cout << "si" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
	

	for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < ncol ; j++){
			mapaResultado[i][j] = 'P';
			mapaResultado[nfil-i-1][j] = 'P';
        }
	}

	for (int i = 0 ; i < nfil ; i++){
		for (int j = 0 ; j < 3 ; j++){
			mapaResultado[i][j] = 'P';
			mapaResultado[i][ncol-j-1] = 'P';
		}
	}

	//pendiente de revisar para ajustarlo a la nueva forma
	switch (last_action)
	{
		case actWALK:
			switch (current_state.brujula){
				case norte:
				
					current_state.fil--;
					aux_state.fil--; 
				
				break;
				case noreste:
				
				 	current_state.fil--; current_state.col++; 
					aux_state.fil--; aux_state.col++;
				 
				break;
				case este:
				
					current_state.col++; 
					aux_state.col++; 

				
				break;
				case sureste: 
				
					current_state.fil++; current_state.col++; 
					aux_state.fil++; aux_state.col++; 
				
				break;
				case sur:
				
				 	current_state.fil++; 
				 	aux_state.fil++; 


				break;
				case suroeste:
				
					current_state.fil++; current_state.col--; 
					aux_state.fil++; aux_state.col--; 


				break;
				case oeste:
				
					current_state.col--; 
					aux_state.col--; 


				break;
				case noroeste:
				
					current_state.fil--; current_state.col--; 
					aux_state.fil--; aux_state.col--; 

				break;
			}

			break;
		case actRUN:
			switch (current_state.brujula){
				case norte: current_state.fil-=2; break;
				case noreste: current_state.fil-=2; current_state.col+=2; break;
				case este: current_state.col+=2; break;
				case sureste: current_state.fil+=2; current_state.col+=2; break;
				case sur: current_state.fil+=2; break;
				case suroeste: current_state.fil+=2; current_state.col-=2; break;
				case oeste: current_state.col-=2; break;
				case noroeste: current_state.fil-=2; current_state.col-=2; break;
			}
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

	if (!bien_situado){
		aux_state.brujula = current_state.brujula;
		matrizAux[aux_state.fil][aux_state.col] = sensores.terreno[0];

		switch (aux_state.brujula)
		{
			case norte:
				matrizAux[aux_state.fil-1][aux_state.col-1] = sensores.terreno[1];
				matrizAux[aux_state.fil-1][aux_state.col]   = sensores.terreno[2];
				matrizAux[aux_state.fil-1][aux_state.col+1] = sensores.terreno[3];
				matrizAux[aux_state.fil-2][aux_state.col-2] = sensores.terreno[4];
				matrizAux[aux_state.fil-2][aux_state.col-1] = sensores.terreno[5];
				matrizAux[aux_state.fil-2][aux_state.col]   = sensores.terreno[6];
				matrizAux[aux_state.fil-2][aux_state.col+1] = sensores.terreno[7];
				matrizAux[aux_state.fil-2][aux_state.col+2] = sensores.terreno[8];
				matrizAux[aux_state.fil-3][aux_state.col-3] = sensores.terreno[9];
				matrizAux[aux_state.fil-3][aux_state.col-2] = sensores.terreno[10];
				matrizAux[aux_state.fil-3][aux_state.col-1] = sensores.terreno[11];
				matrizAux[aux_state.fil-3][aux_state.col]   = sensores.terreno[12];
				matrizAux[aux_state.fil-3][aux_state.col+1] = sensores.terreno[13];
				matrizAux[aux_state.fil-3][aux_state.col+2] = sensores.terreno[14];
				matrizAux[aux_state.fil-3][aux_state.col+3] = sensores.terreno[15];
				break;
			case noreste:
				matrizAux[aux_state.fil-1][aux_state.col]   = sensores.terreno[1];
				matrizAux[aux_state.fil-1][aux_state.col+1] = sensores.terreno[2];
				matrizAux[aux_state.fil]  [aux_state.col+1]   = sensores.terreno[3];
				matrizAux[aux_state.fil-2][aux_state.col]   = sensores.terreno[4];
				matrizAux[aux_state.fil-2][aux_state.col+1] = sensores.terreno[5];
				matrizAux[aux_state.fil-2][aux_state.col+2] = sensores.terreno[6];
				matrizAux[aux_state.fil-1][aux_state.col+2] = sensores.terreno[7];
				matrizAux[aux_state.fil]  [aux_state.col+2]   = sensores.terreno[8];
				matrizAux[aux_state.fil-3][aux_state.col]   = sensores.terreno[9];
				matrizAux[aux_state.fil-3][aux_state.col+1] = sensores.terreno[10];
				matrizAux[aux_state.fil-3][aux_state.col+2] = sensores.terreno[11];
				matrizAux[aux_state.fil-3][aux_state.col+3] = sensores.terreno[12];
				matrizAux[aux_state.fil-2][aux_state.col+3] = sensores.terreno[13];
				matrizAux[aux_state.fil-1][aux_state.col+3] = sensores.terreno[14];
				matrizAux[aux_state.fil]  [aux_state.col+3]   = sensores.terreno[15];
				break;
			case este:
				matrizAux[aux_state.fil-1][aux_state.col+1] = sensores.terreno[1];
				matrizAux[aux_state.fil]  [aux_state.col+1]   = sensores.terreno[2];
				matrizAux[aux_state.fil+1][aux_state.col+1] = sensores.terreno[3];
				matrizAux[aux_state.fil-2][aux_state.col+2] = sensores.terreno[4];
				matrizAux[aux_state.fil-1][aux_state.col+2] = sensores.terreno[5];
				matrizAux[aux_state.fil]  [aux_state.col+2]   = sensores.terreno[6];
				matrizAux[aux_state.fil+1][aux_state.col+2] = sensores.terreno[7];
				matrizAux[aux_state.fil+2][aux_state.col+2] = sensores.terreno[8];
				matrizAux[aux_state.fil-3][aux_state.col+3] = sensores.terreno[9];
				matrizAux[aux_state.fil-2][aux_state.col+3] = sensores.terreno[10];
				matrizAux[aux_state.fil-1][aux_state.col+3] = sensores.terreno[11];
				matrizAux[aux_state.fil]  [aux_state.col+3]   = sensores.terreno[12];
				matrizAux[aux_state.fil+1][aux_state.col+3] = sensores.terreno[13];
				matrizAux[aux_state.fil+2][aux_state.col+3] = sensores.terreno[14];
				matrizAux[aux_state.fil+3][aux_state.col+3] = sensores.terreno[15];
				break;
			case sureste:
				matrizAux[aux_state.fil+1][aux_state.col]   = sensores.terreno[3];
				matrizAux[aux_state.fil+1][aux_state.col+1] = sensores.terreno[2];
				matrizAux[aux_state.fil]  [aux_state.col+1]   = sensores.terreno[1];
				matrizAux[aux_state.fil+2][aux_state.col]   = sensores.terreno[8];
				matrizAux[aux_state.fil+2][aux_state.col+1] = sensores.terreno[7];
				matrizAux[aux_state.fil+2][aux_state.col+2] = sensores.terreno[6];
				matrizAux[aux_state.fil+1][aux_state.col+2] = sensores.terreno[5];
				matrizAux[aux_state.fil]  [aux_state.col+2]   = sensores.terreno[4];
				matrizAux[aux_state.fil+3][aux_state.col]   = sensores.terreno[15];
				matrizAux[aux_state.fil+3][aux_state.col+1] = sensores.terreno[14];
				matrizAux[aux_state.fil+3][aux_state.col+2] = sensores.terreno[13];
				matrizAux[aux_state.fil+3][aux_state.col+3] = sensores.terreno[12];
				matrizAux[aux_state.fil+2][aux_state.col+3] = sensores.terreno[11];
				matrizAux[aux_state.fil+1][aux_state.col+3] = sensores.terreno[10];
				matrizAux[aux_state.fil]  [aux_state.col+3]   = sensores.terreno[9];
				break;
			case sur:
				matrizAux[aux_state.fil+1][aux_state.col+1] = sensores.terreno[1];
				matrizAux[aux_state.fil+1][aux_state.col]   = sensores.terreno[2];
				matrizAux[aux_state.fil+1][aux_state.col-1] = sensores.terreno[3];
				matrizAux[aux_state.fil+2][aux_state.col+2] = sensores.terreno[4];
				matrizAux[aux_state.fil+2][aux_state.col+1] = sensores.terreno[5];
				matrizAux[aux_state.fil+2][aux_state.col]   = sensores.terreno[6];
				matrizAux[aux_state.fil+2][aux_state.col-1] = sensores.terreno[7];
				matrizAux[aux_state.fil+2][aux_state.col-2] = sensores.terreno[8];
				matrizAux[aux_state.fil+3][aux_state.col+3] = sensores.terreno[9];
				matrizAux[aux_state.fil+3][aux_state.col+2] = sensores.terreno[10];
				matrizAux[aux_state.fil+3][aux_state.col+1] = sensores.terreno[11];
				matrizAux[aux_state.fil+3][aux_state.col]   = sensores.terreno[12];
				matrizAux[aux_state.fil+3][aux_state.col-1] = sensores.terreno[13];
				matrizAux[aux_state.fil+3][aux_state.col-2] = sensores.terreno[14];
				matrizAux[aux_state.fil+3][aux_state.col-3] = sensores.terreno[15];
				break;
			case suroeste:
				matrizAux[aux_state.fil+1][aux_state.col]   = sensores.terreno[1];
				matrizAux[aux_state.fil+1][aux_state.col-1] = sensores.terreno[2];
				matrizAux[aux_state.fil]  [aux_state.col-1]   = sensores.terreno[3];
				matrizAux[aux_state.fil+2][aux_state.col]   = sensores.terreno[4];
				matrizAux[aux_state.fil+2][aux_state.col-1] = sensores.terreno[5];
				matrizAux[aux_state.fil+2][aux_state.col-2] = sensores.terreno[6];
				matrizAux[aux_state.fil+1][aux_state.col-2] = sensores.terreno[7];
				matrizAux[aux_state.fil]  [aux_state.col-2]   = sensores.terreno[8];
				matrizAux[aux_state.fil+3][aux_state.col]   = sensores.terreno[9];
				matrizAux[aux_state.fil+3][aux_state.col-1] = sensores.terreno[10];
				matrizAux[aux_state.fil+3][aux_state.col-2] = sensores.terreno[11];
				matrizAux[aux_state.fil+3][aux_state.col-3] = sensores.terreno[12];
				matrizAux[aux_state.fil+2][aux_state.col-3] = sensores.terreno[13];
				matrizAux[aux_state.fil+1][aux_state.col-3] = sensores.terreno[14];
				matrizAux[aux_state.fil]  [aux_state.col-3]   = sensores.terreno[15];
				break;
			case oeste:
				matrizAux[aux_state.fil+1][aux_state.col-1] = sensores.terreno[1];
				matrizAux[aux_state.fil]  [aux_state.col-1]   = sensores.terreno[2];
				matrizAux[aux_state.fil-1][aux_state.col-1] = sensores.terreno[3];
				matrizAux[aux_state.fil+2][aux_state.col-2] = sensores.terreno[4];
				matrizAux[aux_state.fil+1][aux_state.col-2] = sensores.terreno[5];
				matrizAux[aux_state.fil]  [aux_state.col-2]   = sensores.terreno[6];
				matrizAux[aux_state.fil-1][aux_state.col-2] = sensores.terreno[7];
				matrizAux[aux_state.fil-2][aux_state.col-2] = sensores.terreno[8];
				matrizAux[aux_state.fil+3][aux_state.col-3] = sensores.terreno[9];
				matrizAux[aux_state.fil+2][aux_state.col-3] = sensores.terreno[10];
				matrizAux[aux_state.fil+1][aux_state.col-3] = sensores.terreno[11];
				matrizAux[aux_state.fil]  [aux_state.col-3]   = sensores.terreno[12];
				matrizAux[aux_state.fil-1][aux_state.col-3] = sensores.terreno[13];
				matrizAux[aux_state.fil-2][aux_state.col-3] = sensores.terreno[14];
				matrizAux[aux_state.fil-3][aux_state.col-3] = sensores.terreno[15];
				break;
			case noroeste:
				matrizAux[aux_state.fil-1][aux_state.col]   = sensores.terreno[3];
				matrizAux[aux_state.fil-1][aux_state.col-1] = sensores.terreno[2];
				matrizAux[aux_state.fil]  [aux_state.col-1]   = sensores.terreno[1];
				matrizAux[aux_state.fil-2][aux_state.col]   = sensores.terreno[8];
				matrizAux[aux_state.fil-2][aux_state.col-1] = sensores.terreno[7];
				matrizAux[aux_state.fil-2][aux_state.col-2] = sensores.terreno[6];
				matrizAux[aux_state.fil-1][aux_state.col-2] = sensores.terreno[5];
				matrizAux[aux_state.fil]  [aux_state.col-2]   = sensores.terreno[4];
				matrizAux[aux_state.fil-3][aux_state.col]   = sensores.terreno[15];
				matrizAux[aux_state.fil-3][aux_state.col-1] = sensores.terreno[14];
				matrizAux[aux_state.fil-3][aux_state.col-2] = sensores.terreno[13];
				matrizAux[aux_state.fil-3][aux_state.col-3] = sensores.terreno[12];
				matrizAux[aux_state.fil-2][aux_state.col-3] = sensores.terreno[11];
				matrizAux[aux_state.fil-1][aux_state.col-3] = sensores.terreno[10];
				matrizAux[aux_state.fil]  [aux_state.col-3]   = sensores.terreno[9];
				break;
			}		
	}
	
	for (int i = 0 ; i < 2*nfil; i++){
		for (int j = 0 ; j < 2*ncol ; j++){
			cout << matrizAux[i][j] << " ";
		}
		cout << endl;
	}

	cout << "la orientacion de mi agente en la auxiliar es: ";
	cout << aux_state.brujula << endl;

	cout << "la orientacion de mi agente en la real es: ";
	cout << current_state.brujula << endl;

	if (sensores.terreno[0] == 'G' && !bien_situado){
	// if (sensores.posF != -1 && !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;

		//traslada lo descubierto en la auxiliar al mapaResultado
		// for (int i = 3 ; i < 2*nfil-3 ; i++){
		// 	for (int j = 3 ; j < 2*ncol-3 ; j++){
		// 		if (matrizAux[i][j] != '?'){
		// 			int diffFil = (aux_state.fil-i);
		// 			int diffCol = (aux_state.col-j);
		// 			mapaResultado[current_state.fil-diffFil][current_state.col-diffCol] = matrizAux[i][j];
		// 		}
		// 	}
		// }


	}

	if (bien_situado){
		PonerTerrenoEnMatriz(sensores.terreno,current_state,mapaResultado);
	}

	actualizaHeatMap(current_state,sensores);

	if (bien_situado && !no_pudo_continuar){
		//mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
		if (!dirigiendose){

			cout << "===========================================" << endl;
			cout << "eligiendo nueva posicion a la que dirigirse" << endl;
			cout << "===========================================" << endl;

			pair<pair<int,int>,bool> posi_bikini = buscaPosicion('K');
			pair<pair<int,int>,bool> posi_zapas = buscaPosicion('D');
			pair<pair<int,int>,bool> posi_bateria = buscaPosicion('X');
			pair<pair<int,int>,bool> potencial = potencialSiguiente(current_state,false);
			pair<pair<int,int>,bool> puerta = buscaPuerta();
			
			if (!tiene_bikini && posi_bikini.second){
				cout << "===========================================" << endl;
				cout << "va a buscar el bikini" << endl;
				cout << "===========================================" << endl;
				posiToward = posi_bikini;
			}
			else if (!tiene_zapatillas && posi_zapas.second){
				cout << "===========================================" << endl;
				cout << "va a buscar las zapas" << endl;
				cout << "===========================================" << endl;
				posiToward = posi_zapas;
			}
			// else if (puerta.second)
			// {
			// 	cout << "=================º==========================" << endl;
			// 	cout << "va a buscar una puerta" << endl;
			// 	cout << "===========================================" << endl;
			// 	posiToward = puerta;
			// }
			else if (sensores.bateria < 1500 && posi_bateria.second){
				cout << "===========================================" << endl;
				cout << "va a buscar la bateria" << endl;
				cout << "===========================================" << endl;
				posiToward = posi_bateria;
			}
			else{
				cout << "===========================================" << endl;
				cout << "ha encontrado una posicion potencial y va a por ella" << endl;
				cout << "===========================================" << endl;
				posiToward = potencial;
			}

			dirigiendose = true;
		}
		//importante asegurarse de volver eso a false cuando ya no 
		//se este dirigiendo a nada para recordar que hay que recalcular

		//bloque para cuando no tenga bateria,zapatillas o bikini
		accion = dirigeHacia(current_state,sensores);

		if (accion == actIDLE){
			// actualizaHeatMap(current_state,sensores);
			posiToward = potencialSiguiente(current_state,true);
			accion = dirigeHacia(current_state,sensores);
		}

		cout << "ha pasado del dirigeHacia" << endl;
	}
	else{
		//no es posible lo que tenia pensado porque si no sabe donde esta los 
		//sensores devuelven valores incorrectos luego tengo que tener un movimiento
		//distinto para cuando no sepa donde esta

		//da mejor rendimiento el movimiento normal que el propio mapa de calor
		if (bien_situado){
			// heatMap[posiToward.first.first][posiToward.first.second]+=2;

			// posiToward = potencialSiguiente(current_state);
			
			// accion = dirigeHacia(current_state,sensores);
			// // accion = _vaAEste(current_state);

			// if (accion == actIDLE){
			// 	// actualizaHeatMap(current_state,sensores);

			// 	posiToward = potencialSiguiente(current_state);
			// 	accion = dirigeHacia(current_state,sensores);
			// }

			if(_canStepOn(sensores)){
				accion = actWALK;

				if (((rand() % 5) == 0) && !girar_derecha){
					accion = actTURN_SR;
					girar_derecha = true;
				}
				
			}
			else if (!girar_derecha)
			{
				accion = actTURN_SR;
				girar_derecha = true;				
			}
			else
			{
				accion = actTURN_L;
				girar_derecha = false;
			}

			if (accion == actWALK && ciclos_de_recarga > 100)
			{
				no_pudo_continuar = false;
			}
		}
		else{ 
			
			if (_canStepOn(sensores))
			{
				accion = dirigeHaciaCiego(current_state,sensores);
			
				if (accion == actIDLE){
					accion = actWALK;

					if (rand() % 10 == 0){
						accion = actTURN_L;
					}
				}
			}	
			else if (rand() % 5 == 0 && !girar_derecha){
				accion = actTURN_SR;
				girar_derecha = true;

				if (rand() % 3 == 0){
					accion = actTURN_L;
				}
			}
			else {
				accion = actTURN_SR;
				girar_derecha = false;
			}

			
		}
	}

	// pair<pair<int,int>,bool> puerta = buscaPuerta();

	if (sensores.terreno[0] == 'K'){
		cout << "===========================================" << endl;
		cout << "ha logrado el bikini" << endl;
		cout << "===========================================" << endl;
		tiene_bikini = true;
		dirigiendose = false;
	}
	else if (sensores.terreno[0] == 'D'){
		cout << "===========================================" << endl;
		cout << "ha logrado las zapas" << endl;
		cout << "===========================================" << endl;
		tiene_zapatillas = true;
		dirigiendose = false;
	}
	else if (sensores.terreno[0] == 'X'){
		cout << "===========================================" << endl;
		cout << "ha recargado la bateria" << endl;
		cout << "===========================================" << endl;

		if(sensores.bateria < 2500)
		{
			dirigiendose = false;
			last_action = actIDLE;
			return actIDLE;
		}

		
	}	
	// else if (puerta.second && puerta.first.first == current_state.fil && puerta.first.second == current_state.col)
	// {
	// 	cout << "===========================================" << endl;
	// 	cout << "ha llegado a la puerta" << endl;
	// 	cout << "===========================================" << endl;
	// }
	else if (posiToward.first.first == current_state.fil && posiToward.first.second == current_state.col){
		cout << "===========================================" << endl;
		cout << "ha llegado a la posicion a la que se dirigia y ahora va a recalcular" << endl;
		cout << "===========================================" << endl;
		dirigiendose = false;
	}

	if (accion == actWALK){

		actualizaHeatMap(current_state,sensores);
	}

	//gestion de la entrada y salida de habitaciones

	if (no_pudo_continuar){
		ciclos_de_recarga = 0;
	}

	if (sensores.reset){
		last_action = actIDLE;
		girar_derecha = false;

		bien_situado = false;

		tiene_zapatillas = false;
		tiene_bikini = false;

		dirigiendose = false;

		no_pudo_continuar = false;
		pendiente_traslacion = true;

		current_state.fil = 99;
		current_state.col = 99;
		current_state.brujula = norte;

		aux_state.fil = nfil;
		aux_state.col = ncol;
		aux_state.brujula = norte;

		//parte de gestion del heat map
		nfil = mapaResultado.at(0).size();
		ncol = mapaResultado.size();

		// nrow = 29; 
		// ncol = 29;

		ciclos_de_recarga = 0;

		for (int i = 0 ; i < nfil; i++){
			for (int j = 0 ; j < ncol; j++){
			heatMap[i][j] = 0;
			}
		}

		for (int i = 0 ; i < 3 ; i++){
			for (int j = 0 ; j < ncol ; j++){
			heatMap[i][j] = 1000;
			heatMap[nfil - i-1][j] = 1000;
			heatMap[j][i] = 1000;
			heatMap[j][ncol-i-1] = 1000;
			}
		}

		posiToward.first.first = 0;
		posiToward.first.second = 0;
		posiToward.second = false;

		for (int i = 3 ; i < nfil*2-3 ; i++){
			for (int j = 3 ; j < ncol*2-3 ; j++){
				matrizAux[i][j] = '?';
			}
		}
	}

	ciclos_de_recarga++;
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

void ComportamientoJugador::showInfoParameters(Sensores sensores,Action accion){
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

	switch (accion)
	{
	case actIDLE:
		cout << "===========================================" << endl;
		cout << "esta idle" << endl;
		cout << "===========================================" << endl;
		break;
	case actWALK:
		cout << "===========================================" << endl;
		cout << "va a caminar" << endl;
		cout << "===========================================" << endl;
		break;
	case actTURN_L:
		cout << "===========================================" << endl;
		cout << "va girando izquierda" << endl;
		cout << "===========================================" << endl;
		break;
	case actTURN_SR:
		cout << "===========================================" << endl;
		cout << "va girando soft derecha" << endl;
		cout << "===========================================" << endl;
		break;
	}
}

Action ComportamientoJugador::dirigeHacia(const state &st, Sensores sensores){
	Action solucion;

	if (st.fil == posiToward.first.first && st.col == posiToward.first.second){
		dirigiendose = false;
		return actIDLE;
	}


	float modulo_m = _calculaModulo(st.fil,st.col,posiToward.first.first,posiToward.first.second);
	//comprobaciones iniciales
	if (st.fil == posiToward.first.first){
		//comprobacion pasa a las columnas.
		//si la columna de st es > col de toward
		if (st.col > posiToward.first.second){
			solucion = _vaAOeste(st);
		}
		else
		{
			solucion = _vaAEste(st);
		}
		
	}
	else if(st.col == posiToward.first.second){
		//comprobacion pasa a las filas.
		//si la fila de st es > fil de toward
		if (st.fil > posiToward.first.first){
			solucion = _vaANorte(st);	
		}
		else
		{
			solucion = _vaASur(st);
		}
	}
	else if(modulo_m == 1){
		if (st.fil > posiToward.first.first){
			solucion = _vaANoroeste(st);
		}
		else
		{
			solucion = _vaASureste(st);
		}
	}
	else if (modulo_m == -1){
		if (st.fil > posiToward.first.first){
			solucion = _vaANoreste(st);
		}
		else
		{
			solucion = _vaASuroeste(st);
		}
	}
	else
	{
		//si modulo es >1 --> que vaya a la izquieda y vuelva a comprobar
		//si modulo es <1 --> que vaya hacia abajo y vuelva a comprobar
		if ((modulo_m < -1 || modulo_m > 1)/*comprobacion de filas*/)
		{
			if (st.fil > posiToward.first.first){
				solucion = _vaANoreste(st);
			}
			else
			{
				solucion = _vaASuroeste(st);	
			}
		}
		else if ((modulo_m < 1 && modulo_m > -1)/*comprobacion de filas y columnas*/)
		{
			if (st.fil > posiToward.first.first && st.col > posiToward.first.second
				|| st.fil > posiToward.first.first && st.col < posiToward.first.second)
			{
				solucion = _vaANorte(st);
			}
			else if (st.fil < posiToward.first.first && st.col > posiToward.first.second
					|| st.fil < posiToward.first.first && st.col < posiToward.first.second)
			{
				solucion = _vaASur(st);
			}
		}
	}

	if(solucion == actWALK && !_canStepOn(sensores)){
		no_pudo_continuar = true;
		dirigiendose = false;
		
		return actIDLE;
	}

	return solucion;
}
pair < pair<int,int>, bool> ComportamientoJugador::buscaPosicion(const char buscado){
	pair<pair<int,int>,bool> solucion;
	bool encontrado = false;

	solucion.first.first = -1;
	solucion.first.second = -1;

	for (int i = 0 ; i < nfil && !encontrado ; i++){
		for (int j = 0 ; j < ncol && !encontrado; j++){
			if (mapaResultado[i][j] == buscado){
				solucion.first.first = i;
				solucion.first.second = j;

				encontrado = true;
			}
		}
	}

	solucion.second = encontrado;

	return solucion;
}
pair < pair<int,int>, bool> ComportamientoJugador::buscaPuerta(){
	pair < pair<int,int>, bool> potencial;
	potencial.first.first = 0;
	potencial.first.second = 0;
	potencial.second = false;
	
	for (int i = 3 ; i < nfil-3 && !potencial.second; i++){
		for (int j = 3 ; j < ncol-3 && !potencial.second; j++){

			if ((mapaResultado[i][j] != 'M' && mapaResultado[i-1][j] == 'M' 
				&& mapaResultado[i+1][j] == 'M')||(mapaResultado[i][j] != 'M' && mapaResultado[i][j-1] == 'M' 
				&& mapaResultado[i][j+1] == 'M')){
				potencial.first.first = i;
				potencial.first.second = j;
				potencial.second = true;
			}
		}
	}

	return potencial;
}
pair <pair<int,int>,bool> ComportamientoJugador::potencialSiguiente(const state &st, bool distancia){
	pair < pair<int,int>, bool> potencial;
	potencial.first.first = 0;
	potencial.first.second = 0;
	potencial.second = false;
	
	if (distancia){
		int act_menor = heatMap[st.fil][st.col];

		for (int i = 3 ; i < nfil-3; i++){
			for (int j = 3 ; j < ncol-3; j++){
				if (heatMap[i][j] <= act_menor){
					if (i != 0 && j != 0){
						potencial.first.first = i;
						potencial.first.second = j;
						potencial.second = true;

						act_menor = heatMap[i][j];
					}
				}
			}
		}	
	} else {
		for (int i = 3 ; i < nfil-3 && !potencial.second; i++){
			for (int j = 3 ; j < ncol-3 && !potencial.second; j++){
				if (mapaResultado[i][j] == '?'){
					potencial.first.first = i;
					potencial.first.second = j;
					potencial.second = true;
				}
			}
		}	
	}

	return potencial;
}
void ComportamientoJugador::actualizaHeatMap(const state &st,Sensores sensores){
	heatMap[st.fil][st.col+1]++;
	heatMap[st.fil+1][st.col]++;
	heatMap[st.fil][st.col-1]++;
	heatMap[st.fil-1][st.col]++;
	heatMap[st.fil+1][st.col+1]++;
	heatMap[st.fil-1][st.col-1]++;
	heatMap[st.fil+1][st.col-1]++;
	heatMap[st.fil-1][st.col+1]++;

	if (no_pudo_continuar){
		heatMap[posiToward.first.first][posiToward.first.second]+=2;
	}

	for (int i = 0 ; i < nfil ; i++){
		for (int j = 0 ; j < ncol ; j++){
			if (mapaResultado[i][j] == 'P'){
				heatMap[i][j] = 1000;
			}
			
		}
	}
	//si cambio esto aborta el core
	for (int i = 3 ; i < nfil-3 ; i++){
		for (int j = 3 ; j < ncol-3 ; j++){

			if (mapaResultado[i][j] == 'M'){
				heatMap[i][j] = 1000;
			}

			if (mapaResultado[i][j] == 'B' && !tiene_zapatillas){
				heatMap[i][j] = 100;
			}
			else if (tiene_zapatillas)
			{
				heatMap[i][j] -= 3;
			}
			

			if (mapaResultado[i][j] == 'A' && !tiene_bikini){
				heatMap[i][j] = 100;
			}
			else if (tiene_zapatillas)
			{
				heatMap[i][j] -= 3;
			}
		}
	}

	heatMap[st.fil][st.col] += 3;	
}
float ComportamientoJugador::_calculaModulo(int fil1, int col1, int fil2, int col2){
	float m;

	float dividendo = (col2-col1);
	float divisor = (fil2-fil1);

	if (divisor != 0){
		m = dividendo/divisor;
	}
	else
	{
		m = 0;
	}

	return m;
	}
	//funciones que acortan el movimiento.
Action ComportamientoJugador::_vaANorte(const state &st){
	Action solucion;
	int oneTurn = (norte+7)%8;
	int twoTurn = (norte+6)%8;

	if (st.brujula == norte){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (sur+6)%8;

	if (st.brujula == sur){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (este+6)%8;

	if (st.brujula == este){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (oeste+6)%8;

	if (st.brujula == oeste){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (noreste+6)%8;

	if (st.brujula == noreste){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (noroeste+6)%8;

	if (st.brujula == noroeste){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (sureste+6)%8;

	if (st.brujula == sureste){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	int twoTurn = (suroeste+6)%8;

	if (st.brujula == suroeste){
		solucion = actWALK;

		// st.fil--;
	} 
	else
	{
		if (st.brujula == oneTurn || st.brujula == twoTurn){
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
	if (((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'G')
			|| (sensores.terreno[2] == 'A' && tiene_bikini) || (sensores.terreno[2] == 'B' && tiene_zapatillas)
		|| sensores.terreno[2] == 'K' || sensores.terreno[2] == 'D' || sensores.terreno[2] == 'X')
		&& sensores.agentes[2] == '_'){
		return true;
	}
	else if (estoyEncerrado())
	{  
		return true;
	}
	else
	{
		return false;
	}
}

bool ComportamientoJugador::_canRun(Sensores sensores){
	if ((((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'G')
			|| (sensores.terreno[2] == 'A' && tiene_bikini) || (sensores.terreno[2] == 'B' && tiene_zapatillas)
		|| sensores.terreno[2] == 'K' || sensores.terreno[2] == 'D' || sensores.terreno[2] == 'X')
		&& sensores.agentes[2] == '_') && (((sensores.terreno[6] == 'T' || sensores.terreno[6] == 'S' || sensores.terreno[6] == 'G')
			|| (sensores.terreno[6] == 'A' && tiene_bikini) || (sensores.terreno[6] == 'B' && tiene_zapatillas)
		|| sensores.terreno[6] == 'K' || sensores.terreno[6] == 'D' || sensores.terreno[6] == 'X')
		&& sensores.agentes[6] == '_')){
		return true;
	}
	else
	{  
		return false;
	}
}

Action ComportamientoJugador::dirigeHaciaCiego(const state &st,Sensores sensores){
	Action accion = actIDLE;

	switch (st.brujula)
	{
	case norte:
		
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){	
				if (i == 1 || i == 4 || i == 5 || i == 9 || i == 10 || i == 11){
					accion = _vaANoroeste(st);
				}
				else if (i == 2 || i == 6 || i == 12)
				{
					accion = _vaANorte(st);
				}
				else
				{
					accion = _vaANoreste(st);
				}
			}
		}

		break;
	case noreste:
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){	
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

		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){	
				if (i == 1 || i == 4 || i == 5 || i == 9 || i == 10 || i == 11){
					accion = _vaANoreste(st);
				}
				else if (i == 2 || i == 6 || i == 12)
				{
					accion = _vaAEste(st);
				}
				else
				{
					accion = _vaASureste(st);
				}
			}
		}

		break;
	case sureste:
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){
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

		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){
				if (i == 1 || i == 4 || i == 5 || i == 9 || i == 10 || i == 11){
					accion = _vaASureste(st);
				}
				else if (i == 2 || i == 6 || i == 12)
				{
					accion = _vaASur(st);
				}
				else
				{
					accion = _vaASuroeste(st);
				}
			}
		}

		break;
	case suroeste:
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){
				if (i == 1 || i == 4 || i == 9){
					accion = _vaAOeste(st);
				}
				else if (i == 3 || i == 8 || i == 15)
				{
					accion = _vaASur(st);
				}
				else
				{
					accion = _vaASuroeste(st);
				}
				
			}
		}

		break;
	case oeste:
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){

				if (i == 1 || i == 4 || i == 5 || i == 9 || i == 10 || i == 11){
					accion = _vaASuroeste(st);
				}
				else if (i == 2 || i == 6 || i == 12)
				{
					accion = _vaAOeste(st);
				}
				else
				{
					accion = _vaANoroeste(st);
				}
			}
		}
		break;
	case noroeste:
		for (int i = 0 ; i < 16 ; i++){
			if (sensores.terreno[i] == 'G' 
				|| (sensores.terreno[i] == 'K' && !tiene_bikini) 
				|| (sensores.terreno[i] == 'D' && !tiene_zapatillas)){

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

bool ComportamientoJugador::estoyEncerrado(){

	bool encerrado = true;

	for (int i = -1 ; i <= 1 ; i++){
		for (int j = -i ; j <= 1 ; j++){
			if (i != 0 && j != 0){
				if (!tiene_bikini && !tiene_zapatillas){
					if ((matrizAux[aux_state.fil+i][aux_state.col+j] != 'B'
						|| matrizAux[aux_state.fil+i][aux_state.col+j] != 'A') && encerrado){
						
						encerrado = false;
					}
				}
				else if (!tiene_bikini)
				{
					if (matrizAux[aux_state.fil+i][aux_state.col+j] != 'A'){
						
						encerrado = false;
					}
				}
				else if (!tiene_zapatillas)
				{
					if (matrizAux[aux_state.fil+i][aux_state.col+j] != 'B'){
						
						encerrado = false;
					}
				}	
			}
		}
	}

	return encerrado;
}

