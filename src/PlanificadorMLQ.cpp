//
// Created by juanf on 3/07/2026.
//
#include "PlanificadorMLQ.h"
#include <algorithm>

PlanificadorMLQ::PlanificadorMLQ(std::vector<Proceso *> procesos, std::vector<Cola *> colas):procesos(std::move(procesos)), colas(std::move(colas)) {
    //Aseguramos que las colas queden de manera ascendente con orden nivel 1: menor prioridad
    std::sort(this->colas.begin(), this->colas.end(),
              [](Cola* a, Cola* b) {
                  return a->nivel < b->nivel;
              });
}

Cola* PlanificadorMLQ::colaDe(int nivel) {
    for (Cola*c : colas) if (c->nivel==nivel) return c;
    return nullptr;
}
Cola* PlanificadorMLQ::colaMasPrioritaria() {
    for (Cola*c : colas) if (!c->vacia()) return c; //Ya están ordenadas asc
    return nullptr;
}
void PlanificadorMLQ::simular() {
    const int N = static_cast<int>(procesos.size());
    int completados = 0;
    int tiempo = 0;
    int slice = 0;

    Proceso* actual = nullptr;
    std::vector<bool> agregado(N, false);

    while (completados < N) {
        // Ingresan procesos que llegan en este instante
        for (int i = 0; i < N; i++) {
            if (!agregado[i] && procesos[i]->AT == tiempo) {
                colaDe(procesos[i]->Q)->encolarFinal(procesos[i]);
                agregado[i] = true;
            }
        }

        Cola* alta = colaMasPrioritaria();

        // Expropiación / fin de quantum
        if (actual != nullptr) {
            if (alta != nullptr && alta->nivel < actual->Q) {
                colaDe(actual->Q)->encolarInicio(actual);
                actual = nullptr;
                slice = 0;
            } else {
                int q = colaDe(actual->Q)->quantum();
                if (q > 0 && slice == q) {
                    colaDe(actual->Q)->encolarFinal(actual);
                    actual = nullptr;
                    slice = 0;
                }
            }
        }

        // Despachar si no hay proceso en CPU
        if (actual == nullptr) {
            Cola* c = colaMasPrioritaria();
            if (c != nullptr) {
                actual = c->siguiente();
                slice = 0;
                if (actual->RT == -1) actual->RT = tiempo - actual->AT;
            } else {
                tiempo++;
                continue;
            }
        }

        // Ejecutar una unidad de tiempo
        --actual->restante;
        slice++;
        tiempo++;

        // Verificar terminación
        if (actual->restante == 0) {
            actual->finalizado = true;
            actual->CT = tiempo;
            actual->TAT = actual->CT - actual->AT;
            actual->WT = actual->TAT - actual->BT;
            completados++;
            actual = nullptr;
            slice = 0;
        }
    }
}
