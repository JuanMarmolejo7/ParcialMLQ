//
// Created by juanf on 3/07/2026.
//

#ifndef COLA_H
#define COLA_H

#include <deque>
#include "Proceso.h"
#include "PoliticaPlanificacion.h"

//Una cola de MLQ, 1 tiene mayor prioridad
//Politica de planificacion y lista de procesos listos que esperan

class Cola {
public:
    int nivel; //1 a 3 con 1 mayor prioridad
    PoliticaPlanificacion* politica; //RR(1), RR(3) ó SJF
    std::deque<Proceso*> procesos; //Estos son los procesos listos en cola

    Cola(int nivel, PoliticaPlanificacion* politica);

    bool vacia()const;
    void encolarFinal(Proceso* p); //Llega o rota al final RR
    void encolarInicio (Proceso* p); //Vuelve al frente luego de ser expropiado
    Proceso* siguiente(); // Delega politica
    int quantum() const; //Quantum de la politica, -1 si no usa nada
};
#endif //COLA_H
