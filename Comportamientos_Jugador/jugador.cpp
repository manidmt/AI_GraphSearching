#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

list<Action> AvanzaASaltosDeCaballo(){

	list<Action> secuencia;
	secuencia.push_back(actWALK);
	secuencia.push_back(actWALK);
	secuencia.push_back(actTURN_L);
	secuencia.push_back(actWALK);
	return secuencia;
}


/**
 * Devuelve si una ubicación en el mapa es transitable para el agente
 */
bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa) {
    return (mapa[x.f][x.c] != 'P' && mapa[x.f][x.c] != 'M');
}


/**
 * Devuelve la ubicación siguiente según el avance del agente
 */
ubicacion NextCasilla(const ubicacion &pos){
    ubicacion next = pos;
    switch (pos.brujula)
    {
        case norte:
            next.f = pos.f - 1;
            break;
        case noreste:
            next.f = pos.f - 1;
            next.c = pos.c + 1;
            break;
        case este:
            next.c = pos.c + 1;
            break;
        case sureste:
            next.f = pos.f + 1;
            next.c = pos.c + 1;
            break;
        case sur:
            next.f = pos.f + 1;
            break;
        case suroeste:
            next.f = pos.f + 1;
            next.c = pos.c - 1;
            break;
        case oeste:
            next.c = pos.c - 1;
            break;
        case noroeste:
            next.f = pos.f - 1;
            next.c = pos.c - 1;
            break;
    }
    return next;
}

/**
 * Devuelve el estado que se genera si el agente puede avanzar.
 * Si no puede avanzar, devuelve como salida el mismo estado de entrada
 */
stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa){
    stateN0 st_result = st;
    ubicacion sig_ubicacion, sig_ubicacion2;
    switch (a) {
        case actWALK: //Si prox casilla es transitable y no está ocupada por el colaborador
            sig_ubicacion = NextCasilla(st.jugador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.colaborador.f and sig_ubicacion.c == st.colaborador.c)){
                	st_result.jugador = sig_ubicacion;
            }
            break;

        case actRUN: //Si prox 2 casillas son transitable y no está ocupada por el colaborador
            sig_ubicacion = NextCasilla(st.jugador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.colaborador.f and sig_ubicacion.c == st.colaborador.c)){
                	sig_ubicacion2 = NextCasilla(sig_ubicacion);
                if (CasillaTransitable(sig_ubicacion2, mapa) and
                    !(sig_ubicacion2.f == st.colaborador.f and sig_ubicacion2.c == st.colaborador.c)){
                    st_result.jugador = sig_ubicacion2;
                }
            }
            break;
        case actTURN_L:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+6)%8);
            break;
        case actTURN_SR:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+1)%8);
            break;
    }
    return st_result;
}


/**
 * Encuentra si el elemento item está en la lista
 */
bool Find(const stateN0 &item, const list<stateN0> &lista) {
    auto it = lista.begin();
    while (it != lista.end() && !(*it == item))
        it++;
    return !(it == lista.end());
}


/** primera aproximación a la implementación de la búsqueda en anchura*/
bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion & final,
	const vector<vector<unsigned char>> &mapa){
	
	stateN0 current_state = inicio;
    list<stateN0> frontier;
    list<stateN0> explored;
    frontier.push_back(current_state);
    bool SolutionFound = (current_state.jugador.f == final.f &&
                        current_state.jugador.c == final.c);
    while (!frontier.empty() && !SolutionFound) {
		
		frontier.pop_front();
		explored.push_back(current_state);

		// Generar hijo actWALK
		stateN0 child_walk = apply(actWALK, current_state, mapa);
		if (child_walk.jugador.f == final.f && child_walk.jugador.c == final.c) {
			current_state = child_walk;
			SolutionFound = true;
		} else if (!Find(child_walk, frontier) && !Find(child_walk, explored)) {
			frontier.push_back(child_walk);
		}

		if (!SolutionFound) {
			// Generar hijo actRUN
			stateN0 child_run = apply(actRUN, current_state, mapa);
			if (child_run.jugador.f == final.f && child_run.jugador.c == final.c) {
				current_state = child_run;
				SolutionFound = true;
			} else if (!Find(child_run, frontier) && !Find(child_run, explored)) {
				frontier.push_back(child_run);
			}
		}

		if (!SolutionFound) {
			// Generar hijo actTURN_L
			stateN0 child_turnl = apply(actTURN_L, current_state, mapa);
			if (!Find(child_turnl, frontier) && !Find(child_turnl, explored)) {
				frontier.push_back(child_turnl);
			}

			// Generar hijo actTURN_SR
			stateN0 child_turnsr = apply(actTURN_SR, current_state, mapa);
			if (!Find(child_turnsr, frontier) && !Find(child_turnsr, explored)) {
				frontier.push_back(child_turnsr);
			}
		}

		if (!SolutionFound && !frontier.empty()) {
			current_state = frontier.front();
		}
	}	

    return SolutionFound;
}

// Este es el método principal que se piden en la práctica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
    Action accion = actIDLE;
    if (!hayPlan)
    {
        cout << "Calculamos un nuevo plan\n";
        c_state.jugador.f = sensores.posF;
        c_state.jugador.c = sensores.posC;
        c_state.jugador.brujula = sensores.sentido;
        c_state.colaborador.f = sensores.CLBposF;
        c_state.colaborador.c = sensores.CLBposC;
        c_state.colaborador.brujula = sensores.CLBsentido;
        goal.f = sensores.destinoF;
        goal.c = sensores.destinoC;

        hayPlan = AnchuraSoloJugador(c_state, goal, mapaResultado);
        if (hayPlan) cout << "Se encontró un plan\n";
    }

    if (hayPlan && plan.size() > 0)
    {
        accion = plan.front();
        plan.pop_front();
    }

    if (plan.size() == 0)
    {
        cout << "Se completó el plan\n";
        hayPlan = false;
    }

    return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}