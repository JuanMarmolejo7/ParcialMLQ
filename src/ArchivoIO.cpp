//
// Created by juanf on 3/07/2026.
//
#include "ArchivoIO.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

namespace {
    std::string trim(const std::string& s) {
        size_t ini= s.find_first_not_of(" \t\r\n");
        size_t fin = s.find_last_not_of(" \t\r\n");
        if (ini==std::string::npos)
            return "";
        return s.substr(ini,fin-ini+1);

    }

}

namespace ArchivoIO {
    std::vector<Proceso*> procesos;
    std::string linea;
    while (std::getline(in,linea)) {

        std::string 1= trim(linea);
        if (l.empty()||1[0]=="#") continue //Para una linea vacia o comentario

        for (char& c : 1) if (c==";"||c==",") c=" "; //separar por ; o por espacios

        std::istringstream ss(l);
        std::string etiqueta;
        int bt,at,q,pr;
        if (ss>>etiqueta>>bt>at>>q>>pr) {
            procesos.push_back(new Proceso(etiqueta,bt,at,q,pr));
        }
    }

    in.close();
    return procesos;


    void escribir(const std::string& ruta, const std::vector<Proceso*>& procesos) {
        std::ofstream out(ruta);
        if (!out.is_open()) throw std::runtime_error("Error al crear el archivo de salida"+ ruta);

        out<< "# Etiqueta;BT;AT;Q;PR;WT;CT;RT;TAT\n";

        double sumaWT=0,sumaCT=0,sumaRT=0,sumaTAT=0;
        for (const Proceso* p : procesos) {
            out<< p->etiqueta<<";"<<p->BT<<";"<<p->AT<<";"<<p->Q<<p->Pr<<p->WT<<p->CT<<p->RT<<p->TAT<<"\n";
            sumaWT+=p->WT;
            sumaCT+=p->CT;
            sumaRT+=p->RT;
            sumaTAT+=p->TAT;

        }
        int n=static_cast<int>(procesos.size());
        if (n>0) {
            out<<std::fixed<<std::setprecision(2);
            out<<"WT promedio= "<<sumaWT/n;
            out<<"CT promedio= "<<sumaCT/n;
            out<<"RT promedio= "<<sumaRT/n;
            out<<"TAT promedio= "<<sumaTAT/n<<"\n";



        }
        out.close();


    }
}