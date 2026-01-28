#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
	    FEROMONA_=false;
		estado = N0;
	}

	enum ActionType
	{
		actNull,
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
		actIDLE
	};

	//enumerado para los estados
	enum Estado{
		N0,N1,N2,N3,N4,S1,S2,S3,S4
	};

	void Perceive(const Environment &env);
	ActionType Think();

private:
	bool FEROMONA_;

	// //variable que almacena si ya hicimos giro a la izquierda
	// bool giro_izda;

	//variable para saber en que estado se encuentra el agente
	Estado estado;

	// //metodos auxiliares para ejecucion de reglas
	// ActionType ejecutarRegla1();
	// ActionType ejecutarRegla2();
	// ActionType ejecutarDefecto();

	ActionType n0();
	ActionType n1();
	ActionType n2();
	ActionType n3();
	ActionType n4();
	ActionType s1();
	ActionType s2();
	ActionType s3();
	ActionType s4();
};

string ActionStr(Agent::ActionType);

#endif
