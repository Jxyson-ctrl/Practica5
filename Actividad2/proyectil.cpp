#include "proyectil.h"
#include <cmath>
using namespace std;

Proyectil::Proyectil(double x, double y, double velocidadX, double velocidadY,
                     double masa, double radio) {
    this->x          = x;
    this->y          = y;
    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;
    this->masa       = masa;
    this->radio      = radio;
    this->activo     = true;
}

void Proyectil::actualizar(double dt) {
    x = x + velocidadX * dt;
    y = y + velocidadY * dt;
}

double Proyectil::rapidez() {
    return sqrt(velocidadX * velocidadX + velocidadY * velocidadY);
}
