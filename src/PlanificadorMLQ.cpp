//
// Created by juanf on 3/07/2026.
//
#include "PlanificadorMLQ.h"
#include <algorithm>

PlanificadorMLQ::PlanificadorMLQ(std::vector<Proceso *> procesos, std::vector<Cola *> colas):procesos(std::move(procesos)), colas(std::move(colas)) {
    //Aseguramos que las colas queden de manera ascendente con orden nivel 1: menor prioridad
    std::sort(this->colas.begin(), this->colas.end(),[](Cola* a, Cola* b)); {
        return a-> nivel < b-> nivel;    }
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
    int completados=0;
    int tiempo=0;
    int slice=0; //unidades ejecutadas en el quantum actual

    Proceso* actual = nullptr; //proceso en CPU
    std::vector<bool> agregado (N,false);

    while (completados<N) {
        // 1 Ingresan a su cola los procesos que llegan en ese momento
        for ( int=0; i <N; i++) {
            if (!agregado[i]&& procesos[i]->AT==tiempo) {
                colaDe(procesos[i]->Q)->encolarFinal(procesos[i]);
                agregado[i] = true;
            }
        }

        // 2 Cola de mayor prioridad con rocesos listos o puede ser nullptr

        Cola* alta= colaMasPrioritaria();

        // 3 Expropiacion fin de quantum sobre el proceso actual
        if (actual != nullptr) {
            if (alta != nullptr && alta->nivel <actual->) {
                //Llega trabajo a una cola mas prioritaria entonces se expropia y vuelve al frente de su propia cola para reanudad en otro momento
                colaDe(actual->Q)->encolarInicio(actual);
                actual=nullptr;
                slice=0;
            }else{
                int q= colaDe(actual->Q)->quantum();
                if (q>0 && slice==q) {
                    // Se acabó el quantum rota al final de la cola
                    colaDe(actual->Q)->encolarFinal(actual);
                    actual=nullptr;
                    slice=0;

                }

            }
        }

        //4 Si no hay proceso en CPU tomamos uno de la cola conn mayor prioridad
        if (actual==nullptr) {
            Cola* c = colaMasPrioritaria();
            if (c!=nullptr) {
                actual = c->siguiente();
                slice=0;
                if ( actual -> RT ==-1) actual -> RT = tiempo - actual->AT;

            }else {
                tiempo++;
                continue;
            }
            //5 Ejecutamos una unidad de tiempo del proceso actual
            --actual-> restante;
            slice++;
            tiempo++;
        }
        //6 Si terminó calculamos las stats
        if (actual -> restante==0) {
            actual -> finalizado=true;

        actual->CT = tiempo;
        actual->TAT=actual->CT-actual->AT;
        actual->WT=actual->TAT-actual->BT;
        completados++;
        actual=nullptr;
        slice=0;
        }
    }



}

