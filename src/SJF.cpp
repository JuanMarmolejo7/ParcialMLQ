//
// Created by juanf on 3/07/2026.
//
#include "SJF.h"

//Escoge el proceso con menor BT, criterios de desempate:
// 1. Menor BT, 2. Menor AT, 3. Mayor prioridad (Pr), 4. Etiqueta menor

Proceso*
    SJF::seleccionar(std::deque<Proceso*>&listos) {
    if (listos.empty()) return nullptr;

    auto mejor=listos.begin();
    for (auto it = listos.begin(); it != listos.end(); it++) {
        const Proceso* a= *it;
        const Proceso* b= *mejor;
        bool mejorA=(a->BT < b->BT) || (a->BT == b->BT && a->AT < b->AT) || (a->BT==b->BT && a->AT == b->AT && a->Pr > b->Pr)||
            (a->BT == b->BT && a->AT==b->AT && a->Pr==b->Pr&&a->etiqueta<b->etiqueta);
        if (!mejorA) mejor = it;
    }
    Proceso* p = *mejor;
    listos.erase(mejor);
    return p;
}

std::string SJF::nombre() const {
    return "SJF";
}