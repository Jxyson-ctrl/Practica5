#ifndef OBSTACULOJUEGO_H
#define OBSTACULOJUEGO_H

using namespace std;

class ObstaculoJuego {
public:
    double x;
    double y;
    double ancho;
    double alto;
    double resistencia;
    double restitucion;

    ObstaculoJuego(double x, double y, double ancho, double alto,
                   double resistencia, double restitucion);

    void recibirDanio(double velocidadImpacto, double masaProyectil);
    bool estaDestruido();
};

#endif
