#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <cmath>
using namespace std;

class Proyectil {
public:
    double x;
    double y;
    double velocidadX;
    double velocidadY;
    double masa;
    double radio;
    bool activo;

    Proyectil(double x, double y, double velocidadX, double velocidadY,
              double masa, double radio);

    void actualizar(double dt);
    double rapidez();
};

#endif
