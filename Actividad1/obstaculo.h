#ifndef OBSTACULO_H
#define OBSTACULO_H

using namespace std;

class Obstaculo {
public:
    double x;
    double y;
    double ancho;
    double alto;
    double restitucion;

    Obstaculo(double x, double y, double ancho, double alto, double restitucion);

    void mostrar();
};

#endif