#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct stateN0{
  ubicacion jugador;
  ubicacion colaborador;

  Action ultimaOrdenColaborador;

  bool operator==(const stateN0 &x) const{
    if (jugador == x.jugador && colaborador.f == x.colaborador.f
        && colaborador.c == x.colaborador.c){
          return true;
        }
    else {
      return false;
    }
  } 
};

struct nodeN0{
  stateN0 st;
  list<Action> secuencia;

  bool operator==(const nodeN0 &n) const{
    return (st == n.st);
  }

  bool operator<(const nodeN0 &b) const{
    if (st.jugador.f < b.st.jugador.f){
      return true;
    }
    else if (st.jugador.f == b.st.jugador.f && st.jugador.c < b.st.jugador.c)
    {
       return true;
    }
    else if (st.jugador.f == b.st.jugador.f && st.jugador.c == b.st.jugador.c && st.jugador.brujula < b.st.jugador.brujula)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      hayPlan = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    list<Action> AvanzaASaltosDeCaballo();
    bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa);
    bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char> > &mapa);
    ubicacion NextCasilla(const ubicacion &pos);
    stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char> > mapa);
    bool Find(const stateN0 &item, const list<stateN0> &lista);
    bool Find(const stateN0 &item, const list<nodeN0> &lista);
    void AnulaMatriz(vector<vector<unsigned char> > &matriz);
    void VisualizarPlan(const stateN0 &st, const list<Action> &plan);
    void PintaPlan(const list<Action> &plan);
    list <Action> AnchuraSoloJugador_V2(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> AnchuraSoloJugador_V3(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);


  private:
    // Declarar Variables de Estado
    list<Action> plan;
    bool hayPlan;
    stateN0 c_state;
    ubicacion goal;




};

#endif

