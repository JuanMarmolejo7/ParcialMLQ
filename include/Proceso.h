//
// Created by juanf on 3/07/2026.
//

#ifndef PROCESO_H
#define PROCESO_H

#include <string>

//Representa el proceso a planificar
//Guarda los datos de entrada (etiqueta, BT, AT, Q, Pr) y los campos
// Que se van calculando durante la simulacion (restante,WT,CT,RT,TAT)

class Proceso {
public:
    std::string etiqueta; //identificador del proceso
    int BT; //Burst time
    int AT; // Arrival time
    int Q; //Numero de cola a la que pertenece
    int Pr; // prioridad (mayor numero=mas prioridad)

    int restante; //tiempo de CPU que le falta por ejecutar
    int WT; // Waiting time
    int CT; //Completion time
    int RT; //Response time (-1 mientras no ejecuta por primera vez)
    int TAT; //Turn around time
    bool finalizado; //True cuando restante llega a 0

    Proceso(std::string etiqueta="", int bt=0, int at=0, int q=1, int pr=0);

};

#endif //PROCESO_H
