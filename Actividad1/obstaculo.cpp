#include "obstaculo.h"
#include <iostream>
using namespace std;

Obstaculo::Obstaculo(double x, double y, double ancho, double alto, double restitucion) {
    this->x           = x;
    this->y           = y;
    this->ancho       = ancho;
    this->alto        = alto;
    this->restitucion = restitucion;
}

void Obstaculo::mostrar() {
    cout << "Obstaculo en (" << x << ", " << y << ") "
         << "ancho=" << ancho << " alto=" << alto
         << " e=" << restitucion << endl;
}