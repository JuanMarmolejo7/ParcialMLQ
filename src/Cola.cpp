//
// Created by juanf on 3/07/2026.
//

#include "Cola.h"

Cola::Cola(int nivel, PoliticaPlanificacion* politica):nivel(nivel), politica(politica){}

bool Cola::vacia() const {
    return procesos.empty();
}

void Cola::encolarFinal(Proceso *p) {
procesos.push_back(p);
}

void Cola::encolarInicio(Proceso *p) {
    procesos.push_front(p);
}

Proceso* Cola::siguiente() {
    return politica->seleccionar(procesos);
}

int Cola::quantum() const {
    return politica->quantum();
}