#include "juego.h"
#include <iostream>
#include <cmath>
using namespace std;

Juego::Juego(double anchoCaja, double altoCaja, double dt) {
    this->anchoCaja      = anchoCaja;
    this->altoCaja       = altoCaja;
    this->dt             = dt;
    this->turno          = 0;
    this->juegoTerminado = false;
    this->ganador        = "";
    this->proyectil      = nullptr;
    this->rivalX1    = 95;
    this->rivalY1    = 250;
    this->rivalX2    = 575;
    this->rivalY2    = 250;
    this->rivalAncho = 70;
    this->rivalAlto  = 90;
}

Juego::~Juego() {
    if (proyectil != nullptr) delete proyectil;
}

void Juego::iniciar() {
    obstaculosJugador1.push_back(ObstaculoJuego(20,  250, 70, 80, 200, 0.3));
    obstaculosJugador1.push_back(ObstaculoJuego(210, 250, 70, 80, 200, 0.3));
    obstaculosJugador1.push_back(ObstaculoJuego(60,  225, 160, 25, 150, 0.8));

    obstaculosJugador2.push_back(ObstaculoJuego(490, 250, 70, 80, 200, 0.3));
    obstaculosJugador2.push_back(ObstaculoJuego(680, 250, 70, 80, 200, 0.3));
    obstaculosJugador2.push_back(ObstaculoJuego(530, 225, 160, 25, 150, 0.8));
}

void Juego::lanzarProyectil(double x, double y, double angulo, double velocidad, double masa) {
    if (proyectil != nullptr) delete proyectil;

    double rad        = angulo * M_PI / 180.0;
    double velocidadX = velocidad * cos(rad);
    double velocidadY = -velocidad * sin(rad);

    proyectil = new Proyectil(x, y, velocidadX, velocidadY, masa, 10);
}

void Juego::colisionParedes() {
    if (proyectil == nullptr) return;

    double amortiguacion = 0.7;

    if (proyectil->x - proyectil->radio < 0) {
        proyectil->x = proyectil->radio;
        proyectil->velocidadX = -proyectil->velocidadX * amortiguacion;
    }
    if (proyectil->x + proyectil->radio > anchoCaja) {
        proyectil->x = anchoCaja - proyectil->radio;
        proyectil->velocidadX = -proyectil->velocidadX * amortiguacion;
    }
    if (proyectil->y - proyectil->radio < 0) {
        proyectil->y = proyectil->radio;
        proyectil->velocidadY = -proyectil->velocidadY * amortiguacion;
    }
    if (proyectil->y + proyectil->radio > altoCaja) {
        proyectil->y = altoCaja - proyectil->radio;
        proyectil->velocidadY = -proyectil->velocidadY * amortiguacion;
    }
}

bool Juego::hayColision(Proyectil* p, ObstaculoJuego& o) {
    double cercanoPX = p->x;
    double cercanoPY = p->y;

    if (p->x < o.x)           cercanoPX = o.x;
    if (p->x > o.x + o.ancho) cercanoPX = o.x + o.ancho;
    if (p->y < o.y)           cercanoPY = o.y;
    if (p->y > o.y + o.alto)  cercanoPY = o.y + o.alto;

    double dx = p->x - cercanoPX;
    double dy = p->y - cercanoPY;

    return (dx * dx + dy * dy) < (p->radio * p->radio);
}

void Juego::resolverColision(Proyectil* p, ObstaculoJuego& o) {
    double solapIzq = (p->x + p->radio) - o.x;
    double solapDer = (o.x + o.ancho)   - (p->x - p->radio);
    double solapArr = (p->y + p->radio) - o.y;
    double solapAba = (o.y + o.alto)    - (p->y - p->radio);

    double minSolap = solapIzq;
    if (solapDer < minSolap) minSolap = solapDer;
    if (solapArr < minSolap) minSolap = solapArr;
    if (solapAba < minSolap) minSolap = solapAba;

    double rapidezImpacto = p->rapidez();
    o.recibirDanio(rapidezImpacto, p->masa);

    if (minSolap == solapIzq) {
        p->velocidadX = -o.restitucion * p->velocidadX;
        p->x = o.x - p->radio;
    } else if (minSolap == solapDer) {
        p->velocidadX = -o.restitucion * p->velocidadX;
        p->x = o.x + o.ancho + p->radio;
    } else if (minSolap == solapArr) {
        p->velocidadY = -o.restitucion * p->velocidadY;
        p->y = o.y - p->radio;
    } else {
        p->velocidadY = -o.restitucion * p->velocidadY;
        p->y = o.y + o.alto + p->radio;
    }
}

void Juego::colisionObstaculos() {
    if (proyectil == nullptr) return;

    if (turno == 0) {
        for (int i = 0; i < obstaculosJugador2.size(); i++) {
            if (!obstaculosJugador2[i].estaDestruido()) {
                if (hayColision(proyectil, obstaculosJugador2[i])) {
                    resolverColision(proyectil, obstaculosJugador2[i]);
                }
            }
        }
    } else {
        for (int i = 0; i < obstaculosJugador1.size(); i++) {
            if (!obstaculosJugador1[i].estaDestruido()) {
                if (hayColision(proyectil, obstaculosJugador1[i])) {
                    resolverColision(proyectil, obstaculosJugador1[i]);
                }
            }
        }
    }
}

void Juego::cambiarTurno() {
    if (proyectil != nullptr) {
        delete proyectil;
        proyectil = nullptr;
    }
    turno = 1 - turno;
}

bool Juego::verificarVictoria() {
    bool j1Destruido = true;
    bool j2Destruido = true;

    for (int i = 0; i < obstaculosJugador1.size(); i++) {
        if (!obstaculosJugador1[i].estaDestruido()) {
            j1Destruido = false;
            break;
        }
    }
    for (int i = 0; i < obstaculosJugador2.size(); i++) {
        if (!obstaculosJugador2[i].estaDestruido()) {
            j2Destruido = false;
            break;
        }
    }

    if (j1Destruido) {
        ganador = "Jugador 2";
        juegoTerminado = true;
        return true;
    }
    if (j2Destruido) {
        ganador = "Jugador 1";
        juegoTerminado = true;
        return true;
    }

    return false;
}

void Juego::paso() {
    if (proyectil == nullptr) return;
    if (!proyectil->activo) return;

    proyectil->velocidadY = proyectil->velocidadY + 9.8 * dt;
    proyectil->velocidadX = proyectil->velocidadX * 0.99;
    proyectil->velocidadY = proyectil->velocidadY * 0.99;

    proyectil->actualizar(dt);
    colisionParedes();
    colisionObstaculos();

    // Turno 0 dispara al rival 2, turno 1 dispara al rival 1
    if (turno == 0) {
        if (hayColisionRival(proyectil, rivalX2, rivalY2, rivalAncho, rivalAlto)) {
            ganador = "Jugador 1";
            juegoTerminado = true;
        }
    } else {
        if (hayColisionRival(proyectil, rivalX1, rivalY1, rivalAncho, rivalAlto)) {
            ganador = "Jugador 2";
            juegoTerminado = true;
        }
    }

    verificarVictoria();
}

bool Juego::hayColisionRival(Proyectil* p, double rx, double ry, double rw, double rh) {
    double cercanoPX = p->x;
    double cercanoPY = p->y;

    if (p->x < rx)       cercanoPX = rx;
    if (p->x > rx + rw)  cercanoPX = rx + rw;
    if (p->y < ry)       cercanoPY = ry;
    if (p->y > ry + rh)  cercanoPY = ry + rh;

    double dx = p->x - cercanoPX;
    double dy = p->y - cercanoPY;

    return (dx * dx + dy * dy) < (p->radio * p->radio);
}
