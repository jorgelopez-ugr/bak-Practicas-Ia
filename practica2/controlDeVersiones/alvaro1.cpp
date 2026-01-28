bool operator<(const nodo3 &n) const
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
