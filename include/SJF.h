//
// Created by juanf on 3/07/2026.
//

#ifndef SJF_H
#define SJF_H

#include "PoliticaPlanificacion.h"

//Shortest job first (no expropiativo)
//Seleccionar elige el menor BT, en caso de BT igual se decide por AT, luego mayor prioridad
//Por ultimo por etiqueta para que el resultado siempre sea determinista

class SJF: public
PoliticaPlanificacion {
public:
    Proceso*
    seleccionar(std, deque<Proceso *> &listos) override;
    std::string nombre() const override;
};



#endif //SJF_H
