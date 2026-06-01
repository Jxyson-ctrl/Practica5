#ifndef PARTICULA_H
#define PARTICULA_H

#include <cmath>
using namespace std;

class Particula {
public:
    double x;
    double y;
    double velocidadX;
    double velocidadY;
    double masa;
    double radio;
    bool activa;

    Particula(double x, double y, double velocidadX, double velocidadY,
              double masa, double radio);

    void actualizar(double dt);
    void fusionar(Particula& otra);
};

#endif
