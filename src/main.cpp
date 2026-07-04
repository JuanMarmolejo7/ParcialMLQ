#include <iostream>
#include <vector>
#include <string>

#include "Proceso.h"
#include "Cola.h"
#include  "RR.h"
#include "SJF.h"
#include "PlanificadorMLQ.h"
#include "ArchivoIO.h"

//Simulador MLQ esquema RR(1) + RR(3) + SJF_H

int main(int argc,char* argv[]) {
    std::string entrada=(argc>1) ? argv[1]: "input/mlq001.txt";
    std::string salida=(argc>2) ? argv[2]: "output/mlq001_out.txt";

    try {
        //Leer los procesos del archivo de entrada
        std::vector<Proceso*> procesos = ArchivoIO::leer(entrada);
        if (procesos.empty()) {
            std::cerr<<"El archivo de entrada no contiene procesos validos \n";
            return 1;
        }

        //Construiccion de colas de acuerdo a su esquema
        std::vector<Cola*> colas={
            new Cola(1,new RR(1)),
            new Cola(2,new RR(3) ),
            new Cola(3,new SJF())

        };
        //Ejecutar simulacion
        PlanificadorMLQ planificador(procesos,colas);
        planificador.simular();

        //Escribe resultados y muestra en consola
        ArchivoIO::escribir(salida,procesos);

        std::cout <<"Simulacion MLQ RR(1) + RR(3) + SJF \n";
        std::cout << "Entrada: "<<entrada<<" \n";
        std::cout << "Salida: "<<salida<<" \n";
        std::cout << "Etiqueta BT AT Q Pr WT CT RT TAT \n";

        double sWT = 0, sCT = 0, sRT = 0, sTAT = 0;
        for (const Proceso* p : procesos) {
            std::cout << p->etiqueta << "\t" << p->BT << "  " << p->AT << "  "
                      << p->Q << "  " << p->Pr << "  " << p->WT << "  "
                      << p->CT << "  " << p->RT << "  " << p->TAT << "\n";
            sWT += p->WT; sCT += p->CT; sRT += p->RT; sTAT += p->TAT;
        }
        int n = static_cast<int>(procesos.size());
        std::cout << "\nPromedios -> WT=" << (sWT / n) << " CT=" << (sCT / n)
                  << " RT=" << (sRT / n) << " TAT=" << (sTAT / n) << "\n";

        //Liberacion dememoria

        for (Cola* c : colas){
            delete c->politica;
            delete c;
        }
        for (Proceso* p : procesos) {
            delete p;
        }



    }catch (const std::exception& e) {
        std::cerr<<"Error: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
}