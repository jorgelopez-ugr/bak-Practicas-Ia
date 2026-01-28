#include "agent_hormiga.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion = actFORWARD;
	
	// /* ESCRIBA AQUI LAS REGLAS */
	// //intentar la ejecucion de la primera regla
	// accion = ejecutarRegla1();

	// //si no se pudo ejecutar la regla 1 probamos la 2
	// if (accion == actNull){
	// 	accion = ejecutarRegla2();
	// }

	// //si no se pudo ejecucar la regla 2 probamos la default
	// if (accion == actNull){
	// 	accion = ejecutarDefecto();
	// }
	
	// return accion;

	switch (estado)
	{
	case N0: accion = n0();
		break;

	case N1: accion = n1();
		break;

	case N2: accion = n2();
		break;

	case N3: accion = n3();
		break;

	case N4: accion = n4();
		break;

	case S1: accion = s1();
		break;

	case S2: accion = s2();
		break;

	case S3: accion = s3();
		break;

	case S4: accion = s4();
		break;
	}

	return accion;
}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	FEROMONA_ = env.isFeromona();
}

//implementacion de los metodos de las reglas


/**
 * metodo para elmplementar el comporamiento
 * de la regla 1: si encuentro feromona avanzo
 * en caso contrario no hace nada
*/
// Agent::ActionType Agent::ejecutarRegla1(){
// 	ActionType accion = actNull;

// 	//se comprueba si hay feromona
// 	if (FEROMONA_){
// 		accion = actFORWARD;
// 		giro_izda = false;
// 	}

// 	//devolvemos la accion
// 	return accion;
// }

// /**
//  * Si no se ha girado a la izquierda
//  * haremos el giro. 
// */
// Agent::ActionType Agent::ejecutarRegla2(){
// 	ActionType accion = actNull;

// 	if (!giro_izda){
// 		accion = actTURN_L;
// 		giro_izda = true;
// 	}
	
// 	//devolvemos la accion
// 	return accion;
// }

// /**
//  * Regla por defecto: Girar a la derecha 
// */
// Agent::ActionType Agent:: ejecutarDefecto(){
// 	return actTURN_R;
// }

/**
 * Metodo para el estado inicial
*/
Agent::ActionType Agent::n0(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_L;
		estado = N1;
	}

	//devolvemos el estado

	return accion;
	
}
/**
 * Metodo para el comportamiento del estado 1
 * que debe buscar a la izda del estado actual.
*/
Agent::ActionType Agent::n1(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_R;
		estado = N2;
	}

	//devolvemos el estado

	return accion;
}

/**
 * Metodo para el comportamiento del estado 2
 * que debe buscar a la derecha del estado actual.
*/
Agent::ActionType Agent::n2(){
	//vamos a pasar al estado N3.
	// el estado N2 es meramente transitorio

	estado = N3;
	return actTURN_R;
	
}

/**
 * Metodo para el comportamiento del estado 3
 * que debe buscar a la derecha.
*/
Agent::ActionType Agent::n3(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_L;
		estado = N4;
	}

	//devolvemos el estado

	return accion;
	
}

Agent::ActionType Agent::n4(){
	estado = N0;
	return actFORWARD;
}

/**
 * Metodo para el comportamiento del estado 1
 * que debe buscar a la izda del estado actual.
*/
Agent::ActionType Agent::s1(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_L;
		estado = S2;
	}

	//devolvemos el estado

	return accion;
	
}

Agent::ActionType Agent::s2(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_R;
		estado = S3;
	}

	//devolvemos el estado

	return accion;
	
}

Agent::ActionType Agent::s3(){
	estado = S4;
	return actTURN_R;
}

Agent::ActionType Agent::s4(){
	ActionType accion = actIDLE;

	//comprobamos si hay feromona
	if (FEROMONA_){
		accion = actFORWARD;
		estado = S1;
	}
	else
	{
		accion = actTURN_L;
		estado = S1;
	}

	//devolvemos el estado

	return accion;
	
}

// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	default: return "????";
	}
}
