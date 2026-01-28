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

struct posicion
{
  int fil;
  int col;
  bool dirigiendose;
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
      contador = 0;
      ciclos = 2999;

      current_state.fil = 99;
      current_state.col = 99;
      current_state.brujula = norte;

      //parte de gestion del heat map
      nfil = mapaResultado.at(0).size();
      ncol = mapaResultado.size();

      posiToward.fil = 0;
      posiToward.col = 0;
      posiToward.dirigiendose = false;

      matriz_aux = mapaResultado;

    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector < vector < unsigned char> > &matriz);
    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void showInfoParameters(Sensores Sensores);
    Action dirigeHacia(const state &st, Sensores sensores );
    Action dirigeHaciaCiego(const state &st, Sensores sensores);
    posicion buscaPosicion(const state &st,const char buscado);
    bool esPuerta(int fil, int col);
    void potencialSiguiente(const state &st);
    // pair <pair<int,int>,bool> potencialSiguienteLejano(const state &st);
    void actualizaHeatMap(const state &st,Sensores sensores);
    // vector<int> aLaVista(const state &st);
    // Action protocoloNoPudoContinuar(const state &st, Sensores sensores);
    // Action calculaMovValido(state &st,Sensores sensores);
    // bool estoyEncerrado();
    float _calculaModulo(int fil1, int col1, int fil2, int col2);
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

  int contador;
  bool pudo_continuar;
  int ciclos;

  posicion posiToward;

  stack <posicion> posicionesDeInteres;
  vector <posicion> yaVisitadas;
  vector < vector < unsigned char > > matriz_aux;

};

#endif
