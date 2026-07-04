//
// Created by juanf on 3/07/2026.
//

#ifndef POLITICA_PLANIFICACION_H
#define POLITICA_PLANIFICACION_H

#include <deque>
#include <string>
#include "Proceso.h"

//Clase abstracta, define el contrato que deben cumplit
// las politicas de planificaion (RR y SJF)
// Con polimorfismo clase Cola puede trabajar con una politica sin conocer detalles
class PoliticaPlanificacion {
public:

    //Elige y retira de la lista de listo el proceso a ejecutar
    //Devuelve nullptr si no hay procesos listos
    virtual Proceso* seleccionar(std::deque<Proceso*>& listos)=0;

    //Quantum de la politica -1 es si no usa quantum, acá es SJF
    virtual int quantum() const {
        return -1;
    }

    //Nombre legible de la politica para reportes o debug
    virtual std::string nombre() const=0;

    
    virtual ~PoliticaPlanificacion(){}


};

#endif //POLITICA_PLANIFICACION_H
