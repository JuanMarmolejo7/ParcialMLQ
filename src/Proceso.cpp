//
// Created by juanf on 3/07/2026.
//
#include "Proceso.h"

Proceso::Proceso(std::string etiqueta, double bt, double at, int q, int pr): etiqueta(etiqueta),BT(bt),AT(at),Q(q),Pr(pr),
        restante(bt),WT(0),CT(0),RT(-1),TAT(0),finalizado(false){}