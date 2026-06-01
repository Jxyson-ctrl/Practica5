#include "particula.h"
#include <iostream>
using namespace std;

Particula::Particula(double x, double y, double velocidadX, double velocidadY,
                     double masa, double radio) {
    this->x          = x;
    this->y          = y;
    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;
    this->masa       = masa;
    this->radio      = radio;
    this->activa     = true;
}

void Particula::actualizar(double dt) {
    x = x + velocidadX * dt;
    y = y + velocidadY * dt;
}

void Particula::fusionar(Particula& otra) {
    double masaTotal = masa + otra.masa;

    velocidadX = (masa * velocidadX + otra.masa * otra.velocidadX) / masaTotal;
    velocidadY = (masa * velocidadY + otra.masa * otra.velocidadY) / masaTotal;

    x = (masa * x + otra.masa * otra.x) / masaTotal;
    y = (masa * y + otra.masa * otra.y) / masaTotal;

    radio = sqrt(radio * radio + otra.radio * otra.radio);

    masa = masaTotal;
    otra.activa = false;
}