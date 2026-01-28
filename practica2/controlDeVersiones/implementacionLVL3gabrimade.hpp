#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <iostream>

struct state{
  ubicacion jugador;
  ubicacion colaborador;

  Action ultimaOrdenColaborador;

  bool operator==(const state &x) const{
    if (jugador == x.jugador && colaborador == x.colaborador){
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
  list<Action> secuencia;

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
};

struct node2{
  node nodoBasico;
  int coste_total_secuencia;
  bool tieneBikini = false;
  bool tieneZapatillas = false;

  bool operator==(const node2 &n) const{
    return (nodoBasico.st == n.nodoBasico.st && tieneBikini == n.tieneBikini && tieneZapatillas == n.tieneZapatillas);
  }

  bool operator<(const node2 &b) const{
    if (nodoBasico.st.jugador.f < b.nodoBasico.st.jugador.f){
      return true;
    }
    else if (nodoBasico.st.jugador.f == b.nodoBasico.st.jugador.f && nodoBasico.st.jugador.c < b.nodoBasico.st.jugador.c)
    {
      return true;
    }
    else if (nodoBasico.st.jugador.f == b.nodoBasico.st.jugador.f && nodoBasico.st.jugador.c == b.nodoBasico.st.jugador.c && nodoBasico.st.jugador.brujula < b.nodoBasico.st.jugador.brujula)
    {
      return true;
    }
    else if (nodoBasico.st.jugador.f == b.nodoBasico.st.jugador.f && nodoBasico.st.jugador.c == b.nodoBasico.st.jugador.c && nodoBasico.st.jugador.brujula == b.nodoBasico.st.jugador.brujula && tieneBikini < b.tieneBikini)
    {
      return true;
    }
    else if (nodoBasico.st.jugador.f == b.nodoBasico.st.jugador.f && nodoBasico.st.jugador.c == b.nodoBasico.st.jugador.c && nodoBasico.st.jugador.brujula == b.nodoBasico.st.jugador.brujula && tieneBikini == b.tieneBikini && tieneZapatillas < b.tieneZapatillas)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

struct node3{
  node nodoBasico;
  int coste_total_secuencia;
  int coste_heuristico = 0;
  bool tieneBikini_jugador;
  bool tieneZapatillas_jugador;
  bool tieneBikini_colab;
  bool tieneZapatillas_colab;

  bool operator==(const node3 &b) const{
    if (nodoBasico.st == b.nodoBasico.st
        && tieneBikini_jugador == b.tieneBikini_jugador
        && tieneBikini_colab == b.tieneBikini_colab
        && tieneZapatillas_colab == b.tieneZapatillas_colab
        && tieneZapatillas_jugador == b.tieneZapatillas_jugador){
          return true;
        }
        else
        {
          return false;
        }
        
  }

  bool operator<(const node3 &n) const
  {
    if(nodoBasico.st.jugador.f < n.nodoBasico.st.jugador.f)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c < n.nodoBasico.st.jugador.c)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula < n.nodoBasico.st.jugador.brujula)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador < n.tieneZapatillas_jugador)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador < n.tieneBikini_jugador)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador == n.tieneBikini_jugador and nodoBasico.st.colaborador.f < n.nodoBasico.st.colaborador.f)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador == n.tieneBikini_jugador and nodoBasico.st.colaborador.f == n.nodoBasico.st.colaborador.f and nodoBasico.st.colaborador.c < n.nodoBasico.st.colaborador.c)
      return true;
  
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador == n.tieneBikini_jugador and nodoBasico.st.colaborador.f == n.nodoBasico.st.colaborador.f and nodoBasico.st.colaborador.c == n.nodoBasico.st.colaborador.c and nodoBasico.st.colaborador.brujula < n.nodoBasico.st.colaborador.brujula)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador == n.tieneBikini_jugador and nodoBasico.st.colaborador.f == n.nodoBasico.st.colaborador.f and nodoBasico.st.colaborador.c == n.nodoBasico.st.colaborador.c and nodoBasico.st.colaborador.brujula == n.nodoBasico.st.colaborador.brujula and tieneZapatillas_colab < n.tieneZapatillas_colab)
      return true;
    
    else if(nodoBasico.st.jugador.f == n.nodoBasico.st.jugador.f and nodoBasico.st.jugador.c == n.nodoBasico.st.jugador.c and nodoBasico.st.jugador.brujula == n.nodoBasico.st.jugador.brujula and tieneZapatillas_jugador == n.tieneZapatillas_jugador and tieneBikini_jugador == n.tieneBikini_jugador and nodoBasico.st.colaborador.f == n.nodoBasico.st.colaborador.f and nodoBasico.st.colaborador.c == n.nodoBasico.st.colaborador.c and nodoBasico.st.colaborador.brujula == n.nodoBasico.st.colaborador.brujula and tieneZapatillas_colab == n.tieneZapatillas_colab and tieneBikini_colab < n.tieneBikini_colab)
      return true;
    
    else
      return false;
  }
};

struct ordenarCola{

  bool operator()( const node2& x,const node2& y){
    return x.coste_total_secuencia > y.coste_total_secuencia;
  }

};

struct ordenarCola3{

  bool operator()( const node3& x,const node3& y){
    return x.coste_total_secuencia > y.coste_total_secuencia;
  }

};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      clbEnVision = false;
      hayPlan = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      clbEnVision = false;
      hayPlan = false;
      esLlamadaRecursiva = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    list<Action> AvanzaASaltosDeCaballo();
    bool AnchuraSoloJugador(const state &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa);
    bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char> > &mapa);
    ubicacion NextCasilla(const ubicacion &pos);
    state apply(const Action &a, const state &st, const vector<vector<unsigned char> > &mapa);
    state apply2(const Action &a, const state &st, const vector<vector<unsigned char> > &mapa);

    bool Find(const state &item, const list<state> &lista);
    bool Find(const state &item, const list<node> &lista);
    void AnulaMatriz(vector<vector<unsigned char> > &matriz);
    void VisualizarPlan(const state &st, const list<Action> &plan);
    void PintaPlan(const list<Action> &plan);
    list <Action> AnchuraSoloJugador_V3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> AnchuraLvl1(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> DijkstraLvl2(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);
    list <Action> AnchuraLvl3(const state &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa);


    int calculaCosteDelPaso(Action accion,char casilla,const node2 &nodo);
    int calculaCosteDelPaso(Action accion,char casilla,const node3 &nodo);
    int costeHeuristico (const state &st, ubicacion posi);

    // bool llegaRepitiendo(const list<Action> &secuencia);
    // bool seChocan(const node &n1, const node &n2);

    bool colaboradorEnRangoVision(const state &st);
  private:
    // Declarar Variables de Estado
    list<Action> plan;
    bool hayPlan;
    state c_state;
    ubicacion goal;
    bool clbEnVision;
    bool esLlamadaRecursiva;
};

#endif
