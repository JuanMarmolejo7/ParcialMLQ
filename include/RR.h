//
// Created by juanf on 3/07/2026.
//

#ifndef RR_H
#define RR_H

#include  "PoliticaPlanificacion.h"

//Round Robin, recibe parametro para usarlo para RR(1) y RR(3) solo cambiando instancia
//Como es cola FIFO con rotacion seleccionar() toma el primero de la fila

class RR : public PoliticaPlanificacion {
  int q; //quantum
public:
  explicit RR(int quantum);
  Proceso* seleccionar(std:: deque<Proceso *> &listos) override;
  int quantum() const override;
  std::string nombre() const override;
};

#endif //RR_H
