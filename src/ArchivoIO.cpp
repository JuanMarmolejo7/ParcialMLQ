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
    // Quita espacios en blanco al inicio y al final de una cadena
    std::string trim(const std::string& s) {
        size_t ini = s.find_first_not_of(" \t\r\n");
        size_t fin = s.find_last_not_of(" \t\r\n");
        if (ini == std::string::npos) return "";
        return s.substr(ini, fin - ini + 1);
    }

    // Devuelve solo el nombre del archivo (sin carpetas) para el encabezado
    std::string nombreArchivo(const std::string& ruta) {
        size_t pos = ruta.find_last_of("/\\");
        return (pos == std::string::npos) ? ruta : ruta.substr(pos + 1);
    }
}

namespace ArchivoIO {

    std::vector<Proceso*> leer(const std::string& ruta) {
        std::ifstream in(ruta);
        if (!in.is_open())
            throw std::runtime_error("No se pudo abrir el archivo de entrada: " + ruta);

        std::vector<Proceso*> procesos;
        std::string linea;
        while (std::getline(in, linea)) {
            std::string l = trim(linea);
            if (l.empty() || l[0] == '#') continue; // Linea vacia o comentario

            // Permite separar por ; o por espacios
            for (char& c : l) if (c == ';' || c == ',') c = ' ';

            std::istringstream ss(l);
            std::string etiqueta;
            double bt, at;
            int q, pr;
            if (ss >> etiqueta >> bt >> at >> q >> pr) {
                procesos.push_back(new Proceso(etiqueta, bt, at, q, pr));
            }
        }
        in.close();
        return procesos;
    }

    void escribir(const std::string& ruta, const std::vector<Proceso*>& procesos) {
        std::ofstream out(ruta);
        if (!out.is_open())
            throw std::runtime_error("No se pudo crear el archivo de salida: " + ruta);

        out << "# archivo: " << nombreArchivo(ruta) << "\n";
        out << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

        out << std::fixed << std::setprecision(1);

        double sumaWT = 0, sumaCT = 0, sumaRT = 0, sumaTAT = 0;
        for (const Proceso* p : procesos) {
            out << p->etiqueta << ";" << p->BT << ";" << p->AT << ";"
                << p->Q << ";" << p->Pr << ";" << p->WT << ";" << p->CT
                << ";" << p->RT << ";" << p->TAT << "\n";
            sumaWT += p->WT;
            sumaCT += p->CT;
            sumaRT += p->RT;
            sumaTAT += p->TAT;
        }

        int n = static_cast<int>(procesos.size());
        if (n > 0) {
            out << "# WT=" << (sumaWT / n)
                << "; CT=" << (sumaCT / n)
                << "; RT=" << (sumaRT / n)
                << "; TAT=" << (sumaTAT / n) << ";\n";
        }
        out.close();
    }

}