#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state
{
  int fil;
  int col;
  Orientacion brujula;
};

struct position
{
  int fil;
  int col;
  unsigned char type;
  bool dirigirse;
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

      dirigiendose = false;

      no_pudo_continuar = false;
      pendiente_traslacion = true;

      current_state.fil = 99;
      current_state.col = 99;
      current_state.brujula = norte;

      //parte de gestion del heat map
      nfil = mapaResultado.at(0).size();
      ncol = mapaResultado.size();

      aux_state.fil = nfil;
      aux_state.col = ncol;
      aux_state.brujula = current_state.brujula;

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

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector < vector < unsigned char> > &matriz);
    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void showInfoParameters(Sensores Sensores, Action accion);
    Action dirigeHacia(const state &st, Sensores sensores );
    Action dirigeHaciaCiego(const state &st, Sensores sensores);
    pair <pair<int,int>,bool> buscaPosicion(const char buscado);
    pair <pair<int,int>,bool> buscaPuerta();
    pair <pair<int,int>,bool> potencialSiguiente(const state &st, bool distancia);
    // pair <pair<int,int>,bool> potencialSiguienteLejano(const state &st);
    void actualizaHeatMap(const state &st,Sensores sensores);
    // vector<int> aLaVista(const state &st);
    // Action protocoloNoPudoContinuar(const state &st, Sensores sensores);
    // Action calculaMovValido(state &st,Sensores sensores);
    bool estoyEncerrado();
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

    bool _canRun(Sensores sensores);
    // bool _rodeadoSinObjetos(const state &st,Sensores sensores);


  private:
  // Declarar aquí las variables de estado
  state current_state;
  state aux_state;
  Action last_action;
  Orientacion brujula;

  bool girar_derecha;
	bool bien_situado;

  bool tiene_zapatillas;
  bool tiene_bikini;

  bool dirigiendose;

  bool no_pudo_continuar;
  bool pendiente_traslacion;

  int ciclos_de_recarga;

  //parte de gestion del heat map.
  int heatMap[1000][1000];
  int nfil;
  int ncol;

  // unsigned char matrizAux[1000][1000];
  unsigned char matrizAux[1000][1000];

  pair < pair<int,int> , bool > posiToward;
  
};

#endif
