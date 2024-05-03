#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>

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


/** pone a cero todos los elementos de una matriz */
void AnulaMatriz(vector<vector<unsigned char>> &matriz){
    for (int i = 0; i < matriz.size(); i++)
        for (int j = 0; j < matriz[0].size(); j++)
            matriz[i][j] = 0;
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


bool ComportamientoJugador::ColaboradorCerca(const stateN0 &st){

    switch (st.jugador.brujula)
	{
	case norte:
		for (int i = 1; i < 4; i++)
		{
			if (st.jugador.f - i == st.colaborador.f)
			{
				switch (i)
				{
				case 1:
					for (int j = -1; j < 2; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;

				case 2:
					for (int j = -2; j < 3; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;

				case 3:
					for (int j = -3; j < 4; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;
				}
			}
		}
		break;

	case este:
		for (int i = 1; i < 4; i++)
		{
			if (st.jugador.c + i == st.colaborador.c)
			{
				switch (i)
				{
				case 1:
					for (int j = -1; j < 2; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;

				case 2:
					for (int j = -2; j < 3; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;

				case 3:
					for (int j = -3; j < 4; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;
				}
			}
		}
		break;

	case sur:
		for (int i = 1; i < 4; i++)
		{
			if (st.jugador.f + i == st.colaborador.f)
			{
				switch (i)
				{
				case 1:
					for (int j = -1; j < 2; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;

				case 2:
					for (int j = -2; j < 3; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;

				case 3:
					for (int j = -3; j < 4; j++)
					
						if (st.jugador.c + j == st.colaborador.c)   return true;
					break;
				}
			}
		}
		break;

	case oeste:
		for (int i = 1; i < 4; i++)
		{
			if (st.jugador.c - i == st.colaborador.c)
			{
				switch (i)
				{
				case 1:
					for (int j = -1; j < 2; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;

				case 2:
					for (int j = -2; j < 3; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;

				case 3:
					for (int j = -3; j < 4; j++)
					
						if (st.jugador.f + j == st.colaborador.f)   return true;
					break;
				}
			}
		}
		break;
	
    case noreste:
        for (int i = 0; i < 4; i++)
        {
            if (st.jugador.f - i == st.colaborador.f)
                
                for (int j = 0; j < 4; j++)
                
                    if (st.jugador.f + j == st.colaborador.c)   return true;

        }
        break;
    
    case sureste:
        for (int i = 0; i < 4; i++)
        {
            if (st.jugador.f + i == st.colaborador.f)
                
                for (int j = 0; j < 4; j++)
                
                    if (st.jugador.f + j == st.colaborador.c)   return true;

        }
        break;
    
    case noroeste:
        for (int i = 0; i < 4; i++)
        {
            if (st.jugador.f - i == st.colaborador.f)
                
                for (int j = 0; j < 4; j++)
                
                    if (st.jugador.f - j == st.colaborador.c)   return true;

        }
        break;

    case suroeste:
        for (int i = 0; i < 4; i++)
        {
            if (st.jugador.f + i == st.colaborador.f)
                
                for (int j = 0; j < 4; j++)
                
                    if (st.jugador.f - j == st.colaborador.c)   return true;

        }
        break;
    }

	return false;
}

/**
 * Devuelve el estado que se genera si el agente puede avanzar.
 * Si no puede avanzar, devuelve como salida el mismo estado de entrada
 */
stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa){
    stateN0 st_result = st;
    ubicacion sig_ubicacion, sig_ubicacion2;
    switch (a) {
        case actIDLE:
            if(st.ultimaOrdenColaborador != act_CLB_STOP){
                if (st.ultimaOrdenColaborador == act_CLB_WALK){
                    sig_ubicacion = NextCasilla(st.colaborador);
                    if (CasillaTransitable(sig_ubicacion, mapa) and
                        !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                            st_result.colaborador = sig_ubicacion;
                    }
                }

                else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                    st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                }
            }
            break;
        case actWALK: //Si prox casilla es transitable y no está ocupada por el colaborador
            sig_ubicacion = NextCasilla(st.jugador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.colaborador.f and sig_ubicacion.c == st.colaborador.c)){
                	st_result.jugador = sig_ubicacion;

                    if(st.ultimaOrdenColaborador != act_CLB_STOP){
                        if (st.ultimaOrdenColaborador == act_CLB_WALK){
                            sig_ubicacion = NextCasilla(st.colaborador);
                            if (CasillaTransitable(sig_ubicacion, mapa) and
                                !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                                    st_result.colaborador = sig_ubicacion;
                            }else{
                                st_result = st;
                            }
                        }
                        else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                            st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                        }
                    }
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

                    if(st.ultimaOrdenColaborador != act_CLB_STOP){

                        if (st.ultimaOrdenColaborador == act_CLB_WALK){
                            sig_ubicacion = NextCasilla(st.colaborador);
                            if (CasillaTransitable(sig_ubicacion, mapa) and
                                !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                                    st_result.colaborador = sig_ubicacion;
                            }else{
                                st_result = st;
                            }
                        }

                        else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                            st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                        }
                    }
                }
            }
        
            break;
            
        case actTURN_L:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+6)%8);
            
            if(st.ultimaOrdenColaborador != act_CLB_STOP){
                if (st.ultimaOrdenColaborador == act_CLB_WALK){
                    sig_ubicacion = NextCasilla(st.colaborador);
                    if (CasillaTransitable(sig_ubicacion, mapa) and
                        !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                            st_result.colaborador = sig_ubicacion;
                    }else{
                        st_result = st;
                    }
                }
                else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                    st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                    
                }
        }
            break;
        case actTURN_SR:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+1)%8);
            if(st.ultimaOrdenColaborador != act_CLB_STOP){
            if (st.ultimaOrdenColaborador == act_CLB_WALK){
                sig_ubicacion = NextCasilla(st.colaborador);
                if (CasillaTransitable(sig_ubicacion, mapa) and
                    !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                        st_result.colaborador = sig_ubicacion;
                }else{
                    st_result = st;
                }
            }
            else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                
            }
        }
            break;

        case act_CLB_WALK:
            sig_ubicacion = NextCasilla(st.colaborador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.jugador.f and sig_ubicacion.c == st.jugador.c)){
                    st_result.colaborador = sig_ubicacion;
                    st_result.ultimaOrdenColaborador = act_CLB_WALK;
            }
            break;

        case act_CLB_TURN_SR:
            st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
            st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;
            break;

        case act_CLB_STOP:
            st_result.ultimaOrdenColaborador = act_CLB_STOP;
            break;
    
    }
    return st_result;
}

stateN2 apply(const Action &a, const stateN2 &st, const vector<vector<unsigned char>> &mapa){
    stateN2 st_result = st;
    ubicacion sig_ubicacion, sig_ubicacion2;
    switch (a) {
        case actIDLE:
            if(st.ultimaOrdenColaborador != act_CLB_STOP){
                if (st.ultimaOrdenColaborador == act_CLB_WALK){
                    sig_ubicacion = NextCasilla(st.colaborador);
                    if (CasillaTransitable(sig_ubicacion, mapa) and
                        !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                            st_result.colaborador = sig_ubicacion;
                    }
                }

                else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                    st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                }
            }
            break;
        case actWALK: //Si prox casilla es transitable y no está ocupada por el colaborador
            sig_ubicacion = NextCasilla(st.jugador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.colaborador.f and sig_ubicacion.c == st.colaborador.c)){
                	st_result.jugador = sig_ubicacion;
                    
                    if (mapa[sig_ubicacion.f][sig_ubicacion.c] == 'K')
                    {
                        st_result.bikini = true;
                        st_result.zapatillas = false;
                    }
                    else if (mapa[sig_ubicacion.f][sig_ubicacion.c] == 'D')
                    {
                        st_result.bikini = false;
                        st_result.zapatillas = true;
                    }

                    // if(st.ultimaOrdenColaborador != act_CLB_STOP){
                    //     if (st.ultimaOrdenColaborador == act_CLB_WALK){
                    //         sig_ubicacion = NextCasilla(st.colaborador);
                    //         if (CasillaTransitable(sig_ubicacion, mapa) and
                    //             !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                    //                 st_result.colaborador = sig_ubicacion;
                    //         }else{
                    //             st_result = st;
                    //         }
                    //     }
                    //     else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                    //         st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                    //     }
                    // }
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

                    if (mapa[sig_ubicacion2.f][sig_ubicacion2.c] == 'K')
                    {
                        st_result.bikini = true;
                        st_result.zapatillas = false;
                    }
                    else if (mapa[sig_ubicacion2.f][sig_ubicacion2.c] == 'D')
                    {
                        st_result.bikini = false;
                        st_result.zapatillas = true;
                    }

                    // if(st.ultimaOrdenColaborador != act_CLB_STOP){

                    //     if (st.ultimaOrdenColaborador == act_CLB_WALK){
                    //         sig_ubicacion = NextCasilla(st.colaborador);
                    //         if (CasillaTransitable(sig_ubicacion, mapa) and
                    //             !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
                    //                 st_result.colaborador = sig_ubicacion;
                    //         }else{
                    //             st_result = st;
                    //         }
                    //     }

                    //     else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
                    //         st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                    //     }
                    // }
                }
            }
        
            break;
            
        case actTURN_L:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+6)%8);
            
            // if(st.ultimaOrdenColaborador != act_CLB_STOP){
            //     if (st.ultimaOrdenColaborador == act_CLB_WALK){
            //         sig_ubicacion = NextCasilla(st.colaborador);
            //         if (CasillaTransitable(sig_ubicacion, mapa) and
            //             !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
            //                 st_result.colaborador = sig_ubicacion;
            //         }else{
            //             st_result = st;
            //         }
            //     }
            //     else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
            //         st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                    
            //     }
            // }
            break;
        case actTURN_SR:
            st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+1)%8);
            // if(st.ultimaOrdenColaborador != act_CLB_STOP){
            //     if (st.ultimaOrdenColaborador == act_CLB_WALK){
            //         sig_ubicacion = NextCasilla(st.colaborador);
            //         if (CasillaTransitable(sig_ubicacion, mapa) and
            //             !(sig_ubicacion.f == st_result.jugador.f and sig_ubicacion.c == st_result.jugador.c)){
            //                 st_result.colaborador = sig_ubicacion;
            //         }else{
            //             st_result = st;
            //         }
            //     }
            //     else if (st.ultimaOrdenColaborador == act_CLB_TURN_SR){
            //         st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
                    
            //     }
            // }
            break;

        case act_CLB_WALK:
            sig_ubicacion = NextCasilla(st.colaborador);
            if (CasillaTransitable(sig_ubicacion, mapa) and
                !(sig_ubicacion.f == st.jugador.f and sig_ubicacion.c == st.jugador.c)){
                    st_result.colaborador = sig_ubicacion;
                    st_result.ultimaOrdenColaborador = act_CLB_WALK;
            }
            break;

        case act_CLB_TURN_SR:
            st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula+1)%8);
            st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;
            break;

        case act_CLB_STOP:
            st_result.ultimaOrdenColaborador = act_CLB_STOP;
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

/**Sobrecarga de la función Find para buscar en lista de nodoN0*/
bool Find(const stateN0 &item, const list<nodoN0> &lista) {
    auto it = lista.begin();
    while (it != lista.end() && !(it->st == item))
        it++;
    return !(it == lista.end());
}


void PintaPlan(const list<Action> &plan) {
    auto it = plan.begin();
    while (it != plan.end()) {
        if (*it == actWALK) {
            cout << "W ";
        } else if (*it == actRUN) {
            cout << "R ";
        } else if (*it == actTURN_SR) {
            cout << "r ";
        } else if (*it == actTURN_L) {
            cout << "L ";
        } else if (*it == act_CLB_WALK) {
            cout << "cW ";
        } else if (*it == act_CLB_TURN_SR) {
            cout << "cr ";
        } else if (*it == act_CLB_STOP) {
            cout << "cS ";
        } else if (*it == actIDLE) {
            cout << "I ";
        } else {
            cout << "- ";
        }
        it++;
    }
    cout << "(" << plan.size() << " acciones)\n";
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

/**Versión segunda de la búsqueda en anchura: ahora sí devuelve un plan*/
list<Action> AnchuraSoloJugador_V2(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa) {
    nodoN0 current_node;
    list<nodoN0> frontier;
    list<nodoN0> explored;
    list<Action> plan;
    current_node.st = inicio;
    bool SolutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
    frontier.push_back(current_node);

    while (!frontier.empty() && !SolutionFound) {
		frontier.pop_front();
		explored.push_back(current_node);

		// Generar hijo actWALK
		nodoN0 child_walk = current_node;
		child_walk.st = apply(actWALK, current_node.st, mapa);
		child_walk.secuencia.push_back(actWALK);
		if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c) {
			current_node = child_walk;
			SolutionFound = true;
		} else if (!Find(child_walk.st, frontier) && !Find(child_walk.st, explored)) {
			frontier.push_back(child_walk);
		}

		if (!SolutionFound) {
			// Generar hijo actRUN
			nodoN0 child_run = current_node;
			child_run.st = apply(actRUN, current_node.st, mapa);
			child_run.secuencia.push_back(actRUN);
			if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c) {
				current_node = child_run;
				SolutionFound = true;
			} else if (!Find(child_run.st, frontier) && !Find(child_run.st, explored)) {
				frontier.push_back(child_run);
			}
		}

		if (!SolutionFound) {
			// Generar hijo actTURN_L
			nodoN0 child_turnl = current_node;
			child_turnl.st = apply(actTURN_L, current_node.st, mapa);
			child_turnl.secuencia.push_back(actTURN_L);
			if (!Find(child_turnl.st, frontier) && !Find(child_turnl.st, explored)) {
				frontier.push_back(child_turnl);
			}

			// Generar hijo actTURN_SR
			nodoN0 child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
			child_turnsr.secuencia.push_back(actTURN_SR);
			if (!Find(child_turnsr.st, frontier) && !Find(child_turnsr.st, explored)) {
				frontier.push_back(child_turnsr);
			}
		}

		if (!SolutionFound && !frontier.empty()) {
			current_node = frontier.front();
		}
	}
	
	if (SolutionFound) {
		plan = current_node.secuencia;
		cout << "Encontrado un plan: ";
		PintaPlan(current_node.secuencia);
	}

	return plan;
}


/**Versión tercera de la búsqueda en anchura*/
list<Action> AnchuraSoloJugador_V3(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa) {
    nodoN0 current_node;
    list<nodoN0> frontier;
    set<nodoN0> explored;
    list<Action> plan;
    current_node.st = inicio;
    bool SolutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
    frontier.push_back(current_node);

    while (!frontier.empty() && !SolutionFound) {

        frontier.pop_front();
        explored.insert(current_node);

        // Generar hijo actWALK
        nodoN0 child_walk = current_node;
        child_walk.st = apply(actWALK, current_node.st, mapa);
        child_walk.secuencia.push_back(actWALK);
        if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c) {
            current_node = child_walk;
            SolutionFound = true;
        } else if (explored.find(child_walk) == explored.end()) {
            frontier.push_back(child_walk);
        }

        if (!SolutionFound) {
            // Generar hijo actRUN
            nodoN0 child_run = current_node;
            child_run.st = apply(actRUN, current_node.st, mapa);
            child_run.secuencia.push_back(actRUN);
            if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c) {
                current_node = child_run;
                SolutionFound = true;
            } else if (explored.find(child_run) == explored.end()) {
                frontier.push_back(child_run);
            }
        }

        if (!SolutionFound) {
            // Generar hijo actTURN_L
            nodoN0 child_turnl = current_node;
            child_turnl.st = apply(actTURN_L, current_node.st, mapa);
            child_turnl.secuencia.push_back(actTURN_L);
            if (explored.find(child_turnl) == explored.end()) {
                frontier.push_back(child_turnl);
            }

            // Generar hijo actTURN_SR
            nodoN0 child_turnsr = current_node;
            child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
            child_turnsr.secuencia.push_back(actTURN_SR);
            if (explored.find(child_turnsr) == explored.end()) {
                frontier.push_back(child_turnsr);
            }
        }

        if (!SolutionFound && !frontier.empty()) {
            current_node = frontier.front();
            while (!frontier.empty() && explored.find(current_node) != explored.end()){
                frontier.pop_front();
                if (!frontier.empty())      current_node = frontier.front();
            }
        }
    }


    if (SolutionFound) {
        plan = current_node.secuencia;
        cout << "Encontrado un plan: ";
        PintaPlan(current_node.secuencia);
    }

    return plan;
}

list<Action> ComportamientoJugador::AnchuraColaborador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa) {
    nodoN1 current_node;
    list<nodoN1> frontier;
    set<nodoN1> explored;
    list<Action> plan;
    current_node.st = inicio;
    bool SolutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
    frontier.push_back(current_node);

    while (!frontier.empty() && !SolutionFound) {
    
        frontier.pop_front();
        explored.insert(current_node);

        if (ColaboradorCerca(current_node.st)){

            // Generar hijo act_CLB_WALK
            nodoN1 child_clb_walk = current_node;
            child_clb_walk.st = apply(act_CLB_WALK, current_node.st, mapa);
            child_clb_walk.secuencia.push_back(act_CLB_WALK);
            if (child_clb_walk.st.colaborador.f == final.f && child_clb_walk.st.colaborador.c == final.c) {
                current_node = child_clb_walk;
                SolutionFound = true;
            } else if (explored.find(child_clb_walk) == explored.end()) {
                frontier.push_back(child_clb_walk);
            }

            if (!SolutionFound){

                // Generar hijo act_CLB_TURN_SR
                nodoN1 child_clb_turnsr = current_node;
                child_clb_turnsr.st = apply(act_CLB_TURN_SR, current_node.st, mapa);
                child_clb_turnsr.secuencia.push_back(act_CLB_TURN_SR);
                if (explored.find(child_clb_turnsr) == explored.end()) {
                    frontier.push_back(child_clb_turnsr);
                }
            }

            if (!SolutionFound){

                nodoN1 child_clb_stop = current_node;
                child_clb_stop.st = apply(act_CLB_STOP, current_node.st, mapa);
                child_clb_stop.secuencia.push_back(act_CLB_STOP);
                if (explored.find(child_clb_stop) == explored.end()) {
                    frontier.push_back(child_clb_stop);
                }
            }
        }
        
        if (!SolutionFound){

            // Generar hijo actWALK
            nodoN1 child_idle = current_node;
            child_idle.st = apply(actIDLE, current_node.st, mapa);
            child_idle.secuencia.push_back(actIDLE);
            if (child_idle.st.colaborador.f == final.f && child_idle.st.colaborador.c == final.c) {
                current_node = child_idle;
                SolutionFound = true;
            }
            else if (explored.find(child_idle) == explored.end()) {
                frontier.push_back(child_idle);
            }
        }
        
        if (!SolutionFound){

            // Generar hijo actWALK
            nodoN1 child_walk = current_node;
            child_walk.st = apply(actWALK, current_node.st, mapa);
            child_walk.secuencia.push_back(actWALK);
            if (child_walk.st.colaborador.f == final.f && child_walk.st.colaborador.c == final.c) {
                current_node = child_walk;
                SolutionFound = true;
            }
            else if (explored.find(child_walk) == explored.end()) {
                frontier.push_back(child_walk);
            }
        }

        if (!SolutionFound){
            // Generar hijo actRUN
            nodoN1 child_run = current_node;
            child_run.st = apply(actRUN, current_node.st, mapa);
            child_run.secuencia.push_back(actRUN);
            if (child_run.st.colaborador.f == final.f && child_run.st.colaborador.c == final.c) {
                current_node = child_run;
                SolutionFound = true;
            }
            else if (explored.find(child_run) == explored.end()) {
                frontier.push_back(child_run);
            }
        }
        
        if (!SolutionFound){
            // Generar hijo actTURN_L
            nodoN1 child_turnl = current_node;
            child_turnl.st = apply(actTURN_L, current_node.st, mapa);
            child_turnl.secuencia.push_back(actTURN_L);
            if (child_turnl.st.colaborador.f == final.f && child_turnl.st.colaborador.c == final.c) {
                current_node = child_turnl;
                SolutionFound = true;
            }
            else if (explored.find(child_turnl) == explored.end()) {
                frontier.push_back(child_turnl);
            }
        }
        
        if (!SolutionFound){

            // Generar hijo actTURN_SR
            nodoN1 child_turnsr = current_node;
            child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
            child_turnsr.secuencia.push_back(actTURN_SR);
            if (child_turnsr.st.colaborador.f == final.f && child_turnsr.st.colaborador.c == final.c) {
                current_node = child_turnsr;
                SolutionFound = true;
            }
            else if (explored.find(child_turnsr) == explored.end()) {
                frontier.push_back(child_turnsr);
            }
        }
            

        if (!SolutionFound && !frontier.empty()) {
            current_node = frontier.front();
            while (!frontier.empty() && explored.find(current_node) != explored.end()){
                frontier.pop_front();
                if (!frontier.empty())      current_node = frontier.front();
            }
        }
    }

    if (SolutionFound) {
        plan = current_node.secuencia;
        cout << "Encontrado un plan: ";
        PintaPlan(current_node.secuencia);
    }

    return plan;

}

/** Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st*/
void ComportamientoJugador::VisualizaPlan(const stateN0 &st, const list<Action> &plan)
{
    AnulaMatriz(mapaConPlan);
    stateN0 cst = st;

    auto it = plan.begin();
    while (it != plan.end())
    {
        if ((*it != act_CLB_WALK) && (*it != act_CLB_TURN_SR) && (*it != act_CLB_STOP))
        {
            switch (cst.ultimaOrdenColaborador)
            {
                case act_CLB_WALK:
                    cst.colaborador = NextCasilla(cst.colaborador);
                    mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
                    break;
                case act_CLB_TURN_SR:
                    cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
                    break;
            }
        }

        switch (*it)
        {
            case actRUN:
                cst.jugador = NextCasilla(cst.jugador);
                mapaConPlan[cst.jugador.f][cst.jugador.c] = 3;
                cst.jugador = NextCasilla(cst.jugador);
                mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
                break;
            case actWALK:
                cst.jugador = NextCasilla(cst.jugador);
                mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
                break;
            case actTURN_SR:
                cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 1) % 8);
                break;
            case actTURN_L:
                cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
                break;
            case act_CLB_WALK:
                cst.colaborador = NextCasilla(cst.colaborador);
				cst.ultimaOrdenColaborador = act_CLB_WALK;
                mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
                break;
            case act_CLB_TURN_SR:
                cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
				cst.ultimaOrdenColaborador = act_CLB_TURN_SR;
                break;
            case act_CLB_STOP:
                cst.ultimaOrdenColaborador = act_CLB_STOP;
                break;
        }
        it++;
    }
}


int CalcularCoste(const stateN2 &st, const Action &a, const vector<vector<unsigned char>> &mapa){

    char casilla = mapa[st.jugador.f][st.jugador.c];

    switch(a){

        case actWALK:
            switch(casilla){
                case 'A':
                    if (st.bikini)      return 10;
                    else                return 100;
                case 'B':
                    if (st.zapatillas)  return 15;
                    else                return 50;
                case 'T':
                    return 2;
                default:
                    return 1;
            }
        break;
        case actRUN:
            switch(casilla){
                case 'A':
                    if (st.bikini)      return 15;
                    else                return 150;
                case 'B':
                    if (st.zapatillas)  return 25;
                    else                return 75;
                case 'T':
                    return 3;
                default:
                    return 1;
            }
        break;
        case actTURN_L:
            switch(casilla){
                case 'A':
                    if (st.bikini)      return 5;
                    else                return 30;
                case 'B':
                    if (st.zapatillas)  return 1;
                    else                return 7;
                case 'T':
                    return 2;
                default:
                    return 1;
            }
        break;
        case actTURN_SR:
            switch(casilla){
                case 'A':
                    if (st.bikini)      return 2;
                    else                return 10;
                case 'B':
                    if (st.zapatillas)  return 1;
                    else                return 5;
                case 'T':
                    return 1;
                default:
                    return 1;
            }
        break;
    }
}

list<Action> Dijstra(const stateN2 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){

    nodoN2 current_node;
    priority_queue<nodoN2> frontier;
    set<stateN2> explored;
    int coste;
    list<Action> plan;
    current_node.st = inicio;
    bool SolutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
    frontier.push(current_node);
    
    while (!frontier.empty() && !SolutionFound) {

        frontier.pop();
        explored.insert(current_node.st);

        // Generar hijo actWALK
        nodoN2 child_walk = current_node;
        coste = CalcularCoste(current_node.st, actWALK, mapa);
        child_walk.st = apply(actWALK, current_node.st, mapa);

        if (explored.find(child_walk.st) == explored.end()) {
            child_walk.secuencia.push_back(actWALK);
            child_walk.coste_acumulado += coste;
            //current_node = child_walk;
            frontier.push(child_walk);
        }

        
        // Generar hijo actRUN
        nodoN2 child_run = current_node;
        coste = CalcularCoste(current_node.st, actRUN, mapa);
        child_run.st = apply(actRUN, current_node.st, mapa);

        if (explored.find(child_run.st) == explored.end()) {
            child_run.secuencia.push_back(actRUN);
            child_run.coste_acumulado += coste;
            //current_node = child_run;
            frontier.push(child_run);
        }  
        

        
        // Generar hijo actTURN_L
        nodoN2 child_turnl = current_node;
        coste = CalcularCoste(current_node.st, actTURN_L, mapa);
        child_turnl.st = apply(actTURN_L, current_node.st, mapa);
        
        if (explored.find(child_turnl.st) == explored.end()) {
            child_turnl.secuencia.push_back(actTURN_L);
            child_turnl.coste_acumulado += coste;
            //current_node = child_turnl;
            frontier.push(child_turnl);
        }

        // Generar hijo actTURN_SR
        nodoN2 child_turnsr = current_node;
        coste = CalcularCoste(current_node.st, actTURN_SR, mapa);
        child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
        
        if (explored.find(child_turnsr.st) == explored.end()) {
            child_turnsr.secuencia.push_back(actTURN_SR);
            child_turnsr.coste_acumulado += coste;
            //current_node = child_turnsr;
            frontier.push(child_turnsr);
        }
        

        if (!frontier.empty()) {
            current_node = frontier.top();
            while (!frontier.empty() && explored.find(current_node.st) != explored.end()){
                frontier.pop();
                if (!frontier.empty())      current_node = frontier.top();
                if (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c){
                    explored.insert(current_node.st);
                    SolutionFound = true;
                }
            }
        }
    }


    if (SolutionFound) {
        plan = current_node.secuencia;
        cout << "Encontrado un plan: ";
        PintaPlan(current_node.secuencia);
    }

    return plan;
}


// Este es el método principal que se piden en la práctica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
    Action accion = actIDLE;
    if (sensores.nivel != 4)
    {
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

            switch (sensores.nivel)
            {
                case 0:
                    plan = AnchuraSoloJugador_V3(c_state, goal, mapaResultado);
                    break;
                case 1: 
                    plan = AnchuraColaborador(c_state, goal, mapaResultado);
                    break;
                case 2: 
                    stateN2 state_nivel2;
                    state_nivel2.jugador = c_state.jugador;
                    state_nivel2.colaborador = c_state.colaborador;

                    if(mapaResultado[sensores.posF][sensores.posC] == 'K'){state_nivel2.bikini = true; state_nivel2.zapatillas = false;}
                    else if(mapaResultado[sensores.posF][sensores.posC] == 'D'){state_nivel2.bikini = false; state_nivel2.zapatillas = true;}
                    else{state_nivel2.bikini = false; state_nivel2.zapatillas = false;}

                    plan = Dijstra(state_nivel2, goal, mapaResultado);
                    break;
                case 3: // Incluir aquí la llamada al algoritmo de búsqueda del nivel 3
                    cout << "Pendiente de implementar el nivel 3\n";
                    break;
            }

            if (plan.size() > 0)
            {
                VisualizaPlan(c_state, plan);
                hayPlan = true;
            }
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
    }
    else // Incluir aquí la solución al nivel 4
    {
        cout << "Solución al nivel 4 pendiente de implementación.\n";
    }

    return accion;
}


int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
