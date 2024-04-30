#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct stateN0{
  ubicacion jugador;
  ubicacion colaborador;
  Action ultimaOrdenColaborador;

  bool operator==(const stateN0 &x) const{
    
    return (jugador == x.jugador &&
            colaborador.f == x.colaborador.f &&
            colaborador.c == x.colaborador.c);
  }
};

//Definición del tipo nodo del nivel 0
struct nodoN0{
  stateN0 st;
  list<Action> secuencia;

  bool operator==(const nodoN0& n) const {return (st == n.st);}

  bool operator<(const nodoN0& b) const {
      if (st.jugador.f < b.st.jugador.f)                        
          return true;
      else if (st.jugador.f == b.st.jugador.f and st.jugador.c < b.st.jugador.c) 
          return true;
      else if (st.jugador.f == b.st.jugador.f and st.jugador.c == b.st.jugador.c and st.jugador.brujula < b.st.jugador.brujula)  
          return true;
            
      else                                                      
          return false;
  }
};


class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    void VisualizaPlan(const stateN0 &st, const list<Action> &plan);

    Action think(Sensores sensores);
    int interact(Action accion, int valor);


  private:
    // Declarar Variables de Estado
    list<Action> plan;
    bool hayPlan;
    stateN0 c_state;
    ubicacion goal;
};

#endif
