#ifndef JUEGO_H
#define JUEGO_H

#include "proyectil.h"
#include "obstaculojuego.h"
#include <vector>
#include <string>
using namespace std;

class Juego {
public:
    double anchoCaja;
    double altoCaja;
    double dt;
    int turno;
    bool juegoTerminado;
    string ganador;

    double rivalX1, rivalY1;
    double rivalX2, rivalY2;
    double rivalAncho, rivalAlto;

    bool hayColisionRival(Proyectil* p, double rx, double ry, double rw, double rh);

    vector<ObstaculoJuego> obstaculosJugador1;
    vector<ObstaculoJuego> obstaculosJugador2;

    Proyectil* proyectil;

    Juego(double anchoCaja, double altoCaja, double dt);
    ~Juego();

    void iniciar();
    void lanzarProyectil(double x, double y, double angulo, double velocidad, double masa);
    void paso();
    void cambiarTurno();
    bool verificarVictoria();

private:
    void colisionParedes();
    void colisionObstaculos();
    bool hayColision(Proyectil* p, ObstaculoJuego& o);
    void resolverColision(Proyectil* p, ObstaculoJuego& o);
};

#endif
