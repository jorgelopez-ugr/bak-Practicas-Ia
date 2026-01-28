#include "../Comportamientos_Jugador/colaborador.hpp"
#include<iostream>
#include "motorlib/util.h"

Action ComportamientoColaborador::think(Sensores sensores) {
  Action accion;

  if (sensores.ActionSent == actIDLE)
    accion = last_action;
  else {
    last_action = sensores.ActionSent;
    accion = sensores.ActionSent;
  }

  if (sensores.CLBgoal){
    last_action = act_CLB_STOP;
    accion = act_CLB_STOP;
  }
  return accion;

}

int ComportamientoColaborador::interact(Action accion, int valor) {
    return 0;
}
