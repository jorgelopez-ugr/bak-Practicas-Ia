//Jorge López Molina - 78114273V 2A grupo2

#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <stack>
using namespace std;

struct state
{
  int fil;
  int col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      last_action = actIDLE;
      girar_derecha = false;

      bien_situado = false;

      tiene_zapatillas = false;
      tiene_bikini = false;

      pudo_continuar = true;

      ciclos_recargando = 0;
      contador_continua = 0;
      ciclos = 3000;
      veces_misma_posicion = 0;


      current_state.fil = 99;
      current_state.col = 99;
      current_state.brujula = norte;

      //parte de gestion del heat map
      nfil = mapaResultado.at(0).size();
      ncol = mapaResultado.size();

    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector < vector < unsigned char> > &matriz);
    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void showInfoParameters(Sensores Sensores);
    Action dirigeEnCono(const state &st, Sensores sensores);
    //funciones que acortan el movimiento.
    Action _vaANorte(const state &st);
    Action _vaASur(const state &st);
    Action _vaAEste(const state &st);
    Action _vaAOeste(const state &st);
    Action _vaANoreste(const state &st);
    Action _vaANoroeste(const state &st);
    Action _vaASureste(const state &st);
    Action _vaASuroeste(const state &st);
    //en principio el metodo canStepOn pierde su sentido al usarse el mapa de calor
    bool _canStepOn(Sensores sensores);
    // bool _rodeadoSinObjetos(const state &st,Sensores sensores);

  private:
  // Declarar aquí las variables de estado
  state current_state;
  Action last_action;
  Orientacion brujula;

  bool girar_derecha;
	bool bien_situado;

  bool tiene_zapatillas;
  bool tiene_bikini;

  int ciclos_recargando;

  int nfil;
  int ncol;

  int contador_continua;
  bool pudo_continuar;
  int ciclos;
  int veces_misma_posicion;

};

#endif
