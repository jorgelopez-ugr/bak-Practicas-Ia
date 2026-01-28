#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, 
												 const state &st,
												 vector <vector<unsigned char>> &matriz){

	matriz[st.fil][st.col] = terreno[0];

	for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < ncol ; j++){
          matriz[i][j] = 'P';
          matriz[nfil - i-1][j] = 'P';
          matriz[j][i] = 'P';
          matriz[j][ncol-i-1] = 'P';
        }
	}

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "¿donde esta ahora mismo?: (" << current_state.fil << "," << current_state.col << ")" << endl;
	cout << "a donde se esta dirigiendo ahora mismo?: (" << posiToward.fil << "," << posiToward.col << ")" << endl;

	if (!posicionesDeInteres.empty()){
		cout << "la siguiente posicion de interes es: (" << posicionesDeInteres.top().fil << "," << posicionesDeInteres.top().col << ")" << endl;
	}

	cout << "¿como esta el valor de la variable pudo_continuar? :";
	if (pudo_continuar){
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

		posiToward.fil = 0;
		posiToward.col = 0;
		posiToward.dirigiendose = false;

		matriz_aux = mapaResultado;
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

	if (pudo_continuar){
		posicion posi_bikini = buscaPosicion(current_state, 'K');
		posicion posi_zapas = buscaPosicion(current_state,'D');
		posicion posi_bateria = buscaPosicion(current_state,'X');
		posicion posi_no_descubierta = buscaPosicion(current_state,'?');
				
		if (!tiene_bikini && posi_bikini.fil != -1){
			posiToward = posi_bikini;
			
			accion = dirigeHacia(current_state,sensores);
		}
		else if (!tiene_zapatillas && posi_zapas.fil != -1){
			posiToward = posi_zapas;

			accion = dirigeHacia(current_state,sensores);
		}
		else if (sensores.bateria < 1000 && posi_bateria.fil != -1 && ciclos > 2000){
			posiToward = posi_bateria;

			accion = dirigeHacia(current_state,sensores);
		}
		else if ( ciclos < 2800)
		{
			posiToward = posi_no_descubierta;

			accion = dirigeHacia(current_state,sensores);
		}
	}
	
	if (accion == actIDLE){
		contador++;
		int const ciclos_reactivacion = 50;

		if (contador == ciclos_reactivacion){
			pudo_continuar = true;
			contador = 0;
		}
		
		// if (sensores.nivel == 1 && !bien_situado){
		// 	accion = dirigeHaciaCiego(current_state,sensores);
		// }

		if (accion == actIDLE){
			int random = rand() % 100;

			if (random < 80){
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
			else if (random < 90)
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
	else if (sensores.terreno[0] == 'X' && sensores.bateria < 2000 && ciclos > 2000){
		while (ciclos_recargando < 50)
		{
			ciclos_recargando++;

			last_action = actIDLE;
			return actIDLE;
		}
		
		ciclos_recargando = 0;
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

posicion ComportamientoJugador::buscaPosicion(const state &st,const char buscado){
	posicion solucion;
	bool encontrado = false;
	bool posi_valida;
	solucion.fil = -1;
	solucion.col = -1;

	for (int i = 0 ; i < nfil ; i++){
		for (int j = -i ; j <= i ; j++){
			for (int k = -i ; k <= i ; k++){
				if (j != 0 && k != 0){

					int accFil = st.fil + i;
					int accCol = st.col + j;

					if (accFil >= 0 && accFil < nfil && accCol >= 0 && accCol < ncol){
						if (mapaResultado[accFil][accCol] == buscado){
							solucion.fil = accFil;
							solucion.col = accCol;
							solucion.dirigiendose = true;
							encontrado = true;
						}			
					}
				}
			}
		}
	}

	return solucion;
}
//rehacer
bool ComportamientoJugador::esPuerta(int fil, int col){
	posicion potencial;
	potencial.fil = 0;
	potencial.col = 0;
	potencial.dirigiendose = true;
	
	if (mapaResultado[fil][col] != 'M' && mapaResultado[fil][col] != 'P'
		&& (mapaResultado[fil+1][col] == 'M' && mapaResultado[fil-1][col] == 'M'
		|| mapaResultado[fil][col+1] == 'M' && mapaResultado[fil][col-1] == 'M'
		|| mapaResultado[fil+1][col] == 'P' && mapaResultado[fil-1][col] == 'P'
		|| mapaResultado[fil][col+1] == 'P' && mapaResultado[fil][col-1] == 'P')){
		return true;
	}

	return false;
}
//rehacer
void ComportamientoJugador::potencialSiguiente(const state &st){
	posicion potencial;
	potencial.fil = 0;
	potencial.col = 0;
	potencial.dirigiendose = true;
	bool yaVisitada = false;

	for (int i = 0 ; i < ncol ; i++){
		for (int j = 0 ; j < nfil ; j++){
			yaVisitada = false;

			if (esPuerta(i,j)){	
				potencial.fil = i;
				potencial.col = j;
				potencial.dirigiendose = true;

				for (int k = 0 ; k < yaVisitadas.size() && !yaVisitadas.empty() ; i++){
					if (potencial.fil == yaVisitadas[i].fil && potencial.col == yaVisitadas[i].col){
						yaVisitada = true;
					}
				}

				if (!yaVisitada){
					posicionesDeInteres.push(potencial);
				}
			}
		}
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
				if (i == 1 || i == 4 || i == 5 || (i >= 9 && i <= 11)){
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
				if (i == 1 || i == 4 || i == 5 || (i >= 9 && i <= 11)){
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
				if (i == 1 || i == 4 || i == 5 || (i >= 9 && i <= 11)){
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

				if (i == 1 || i == 4 || i == 5 || (i >= 9 && i <= 11)){
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
    else
    {  
      return false;
    }
      
}
