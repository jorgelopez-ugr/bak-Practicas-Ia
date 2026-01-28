#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <iostream>

enum entidad {
  CLB,
  AGNT
};

struct state{
  ubicacion jugador;
  ubicacion colaborador;

  Action ultimaOrdenColaborador;

  bool operator==(const state &x) const{
    if (jugador == x.jugador && colaborador.f == x.colaborador.f
        && colaborador.c == x.colaborador.c){
          return true;
        }
    else {
      return false;
    }
  } 

  void operator=(const state &otro){
    jugador = otro.jugador;
    colaborador = otro.colaborador;

    ultimaOrdenColaborador = otro.ultimaOrdenColaborador;
  }
};

struct node{
  state st;
  //secuencia que almacenará la secuencia de acción que han sido necesarias
  //desde el estado inicial para llegar al estado codificado en st.
  list<Action> secuencia;

  void toString(){
    cout << "la secuencia que se esta siguiendo es: ";

      for (auto it : secuencia){
        cout << it << " ";
      }

      cout << endl;
  }

  bool operator==(const node &n) const{
    return (st == n.st);
  }

  bool operator<(const node &b) const{
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
    else if (st.jugador.f == b.st.jugador.f && st.jugador.c == b.st.jugador.c && st.jugador.brujula == b.st.jugador.brujula
            && st.colaborador.f < b.st.colaborador.f)
    {
      return true;
    }
    else if (st.jugador.f == b.st.jugador.f && st.jugador.c == b.st.jugador.c && st.jugador.brujula == b.st.jugador.brujula
            && st.colaborador.f == b.st.colaborador.f && st.colaborador.c < b.st.colaborador.c)
    {
      return true;
    }
    else if (st.jugador.f == b.st.jugador.f && st.jugador.c == b.st.jugador.c && st.jugador.brujula == b.st.jugador.brujula
            && st.colaborador.f == b.st.colaborador.f && st.colaborador.c == b.st.colaborador.c && st.colaborador.brujula < b.st.colaborador.brujula)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void operator=(const node &otro){
    st = otro.st;

    secuencia.clear();

    for (auto it : otro.secuencia){
      secuencia.push_back(it);
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
      clbEnVision = false;
      hayPlan = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    list<Action> AvanzaASaltosDeCaballo();
    bool AnchuraSoloJugador(const state &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa);
    bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char> > &mapa);
    ubicacion NextCasilla(const ubicacion &pos);
    state apply(const Action &a, const state &st, const vector<vector<unsigned char> > mapa);
    bool Find(const state &item, const list<state> &lista);
    bool Find(const state &item, const list<node> &lista);
    void AnulaMatriz(vector<vector<unsigned char> > &matriz);
    void VisualizarPlan(const state &st, const list<Action> &plan);
    void PintaPlan(const list<Action> &plan);
    list <Action> AnchuraSoloJugador_V2(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> AnchuraSoloJugador_V3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> AnchuraLvl1(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);


    void generaVectores(pair<int, int> &del_1_al_3, pair<int, int> &del_3_al_2, pair<int, int> &del_3_al_4, Orientacion ori);
    bool colaboradorEnRangoVision(const ubicacion &j, const ubicacion &s);
    bool colaboradorEnRangoVision(const state &st);

  private:
    // Declarar Variables de Estado
    list<Action> plan;
    bool hayPlan;
    state c_state;
    ubicacion goal;
    bool clbEnVision;
};

#endif

