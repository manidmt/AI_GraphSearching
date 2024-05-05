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
            colaborador.c == x.colaborador.c &&
            colaborador.brujula == x.colaborador.brujula &&
            ultimaOrdenColaborador == x.ultimaOrdenColaborador);
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


struct nodoN1{

  stateN0 st;
  list<Action> secuencia;

  bool operator==(const nodoN1& n) const {return (st == n.st);}

  bool operator<(const nodoN1 &n) const
  {
    if (st.jugador.f < n.st.jugador.f)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c < n.st.jugador.c)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula < n.st.jugador.brujula)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f < n.st.colaborador.f)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f == n.st.colaborador.f && st.colaborador.c < n.st.colaborador.c)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f == n.st.colaborador.f && st.colaborador.c == n.st.colaborador.c && st.colaborador.brujula < n.st.colaborador.brujula)
      return true;
    else if (st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f == n.st.colaborador.f && st.colaborador.c == n.st.colaborador.c && st.colaborador.brujula == n.st.colaborador.brujula && st.ultimaOrdenColaborador < n.st.ultimaOrdenColaborador)
      return true;
    else
      return false;
  }
};

struct stateN2{

  ubicacion jugador;
  ubicacion colaborador;
  Action ultimaOrdenColaborador;

  bool bikini;
  bool zapatillas;

  bool operator==(const stateN2 &x) const{

    return (jugador == x.jugador &&
            colaborador.f == x.colaborador.f &&
            colaborador.c == x.colaborador.c &&
            bikini == x.bikini && zapatillas == x.zapatillas && ultimaOrdenColaborador == x.ultimaOrdenColaborador);
  }

  bool operator<(const stateN2 &x) const{

    if (jugador.f < x.jugador.f)
      return true;
    else if (jugador.f == x.jugador.f && jugador.c < x.jugador.c)
      return true;
    else if (jugador.f == x.jugador.f && jugador.c == x.jugador.c and jugador.brujula < x.jugador.brujula)
      return true;
    else if (jugador.f == x.jugador.f && jugador.c == x.jugador.c and jugador.brujula == x.jugador.brujula && bikini < x.bikini)
      return true;
    else if (jugador.f == x.jugador.f && jugador.c == x.jugador.c and jugador.brujula == x.jugador.brujula && bikini == x.bikini && zapatillas < x.zapatillas)
      return true;
    else
      return false;
  }
};

struct nodoN2{

  stateN2 st;
  list<Action> secuencia;
  int coste_acumulado = 0;

  bool operator==(const nodoN2& n) const {return (st == n.st);}

  bool operator<(const nodoN2 &n) const{

    return (coste_acumulado > n.coste_acumulado);
  }
};


struct stateN3
{
  ubicacion jugador;
  ubicacion colaborador;
  Action ultimaOrdenColaborador;
  bool bikini_j;
  bool zapatillas_j;
  bool bikini_c;
  bool zapatillas_c;

  bool operator==(const stateN3 &st) const
  {
    return (jugador == st.jugador && colaborador == st.colaborador && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j && bikini_c == st.bikini_c && zapatillas_c == st.zapatillas_c) && ultimaOrdenColaborador == st.ultimaOrdenColaborador;
  }

  bool operator<(const stateN3 &st) const
  {
    if (jugador.f < st.jugador.f)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c < st.jugador.c)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j < st.bikini_j)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j < st.zapatillas_j)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j && bikini_c < st.bikini_c)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j 
    && bikini_c == st.bikini_c && zapatillas_c < st.zapatillas_c)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j 
    && bikini_c == st.bikini_c && zapatillas_c == st.zapatillas_c && colaborador.f < st.colaborador.f)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j 
    && bikini_c == st.bikini_c && zapatillas_c == st.zapatillas_c && colaborador.f == st.colaborador.f && colaborador.c < st.colaborador.c)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j 
    && bikini_c == st.bikini_c && zapatillas_c == st.zapatillas_c && colaborador.f == st.colaborador.f && colaborador.c == st.colaborador.c && colaborador.brujula < st.colaborador.brujula)
    {
      return true;
    }
    else if (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j 
    && bikini_c == st.bikini_c && zapatillas_c == st.zapatillas_c && colaborador.f == st.colaborador.f && colaborador.c == st.colaborador.c && colaborador.brujula == st.colaborador.brujula && ultimaOrdenColaborador < st.ultimaOrdenColaborador)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

struct nodoN3
{
  stateN3 st;
  list<Action> secuencia;
  int coste_acumulado = 0;
  int heuristica = 0;
  int suma = 0;

  bool operator==(const nodoN3 &n) const
  {
    return (st == n.st);
  }

  bool operator<(const nodoN3 &n) const
  {
    return (suma > n.suma);
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

    list<Action> AnchuraColaborador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa);
    list<Action> Estrellita(const stateN3 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa);
    
    bool ColaboradorCerca(const stateN0 &st);
    bool ColaboradorCerca(const stateN3 &st);
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
