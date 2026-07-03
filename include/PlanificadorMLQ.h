//
// Created by juanf on 3/07/2026.
//

#ifndef PLANIFICADOR_MLQ_H
#define PLANIFICADOR_MLQ_H

#include <vector>
#include "Proceso.h"
#include "Cola.h"

// Se encarga de simular MLQ
// Mueve procesos a su cola cuando lleguen segun su AT
// En cada unidad de tiempo elige la cola no vacia que tenga más prioridad
// Delega en la politica de esa cola quien ejecuta
// Aplica expropiacion entre colas
// Al terminar un proceso calcula CT,TAT Y WT

class PlanificadorMLQ {
    std::vector<Proceso*> procesos; //Todos los procesos de simulacion
    std::vector<Cola*> colas; // Colas ordenadas por nivel indice=nivel-1

    Cola* colaDe(int nivel); //Devuelve la cola con ese nivel
    Cola* colaMasPrioritario(); //Cola no vacio con menor nivel o nullpointer

public:
    PlanificadorMLQ(std::vector<Proceso*> procesos, std::vector<Cola*> colas);
    //Ejecuta la simulacion completa y avanza el tiempo 1 unidad a la vez
    void simular();

    const std::vector<Proceso*>& getProcesos() const {
        return procesos;
    }
};



#endif //PLANIFICADOR_MLQ_H
