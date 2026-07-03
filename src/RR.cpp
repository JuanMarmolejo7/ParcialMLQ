//
// Created by juanf on 3/07/2026.
//
#include "RR.h"

RR::RR(int quantum):q(quantum){}

//Round Robin funciona FIFO, siempre ejecuta el que está enfrente

Proceso*
    RR::seleccionar(std::deque<Proceso*>&listos) {
    if (listos.empty()) return nullptr;
    Proceso* p =listos.front();
    listos.pop_front();
    return p;
}

int RR::quantum() const {
    return q;
}

std::string RR::nombre() const {
    return "RR( " +std::to_string(q)+" )";
}

