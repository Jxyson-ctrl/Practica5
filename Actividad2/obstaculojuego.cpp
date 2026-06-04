#include "obstaculojuego.h"
#include <iostream>
using namespace std;

ObstaculoJuego::ObstaculoJuego(double x, double y, double ancho, double alto,
                               double resistencia, double restitucion) {
    this->x           = x;
    this->y           = y;
    this->ancho       = ancho;
    this->alto        = alto;
    this->resistencia = resistencia;
    this->restitucion = restitucion;
}

void ObstaculoJuego::recibirDanio(double velocidadImpacto, double masaProyectil) {
    double factorConstante = 0.1;
    double danio = factorConstante * masaProyectil * velocidadImpacto;
    resistencia = resistencia - danio;
    if (resistencia < 0) resistencia = 0;
    cout << "Danio: " << danio << " Resistencia: " << resistencia << endl;
}

bool ObstaculoJuego::estaDestruido() {
    return resistencia <= 0;
}
