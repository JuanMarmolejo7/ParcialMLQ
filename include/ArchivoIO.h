#ifndef ARCHIVO_IO_H
#define ARCHIVO_IO_H

#include <string>
#include <vector>
#include "Proceso.h"

//Entrada y salida de archivos
//Lineas vacias y # se ignoran
//Formato de entrada: etiqueta;BT;AT;Q;Pr

namespace ArchivoIO {
    //Lee el archivo y devuelve los procesos, runtime error si no se puede abrir
    std::vector<Proceso*> leer(const std::string& ruta);
    //Escribe el resultado con el formato etiqueta;BT;AT;Q;Pr promedios al final
    void escribir (const std::string& ruta, const std::vector<Proceso*>& procesos);

}

#endif //PARCIAL_JAPET_ARCHIVOIO_H
