#include "simulacion.h"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

Simulacion::Simulacion(double anchoCaja, double altoCaja, double dt) {
    this->anchoCaja    = anchoCaja;
    this->altoCaja     = altoCaja;
    this->dt           = dt;
    this->tiempoActual = 0;
}

void Simulacion::agregarParticula(Particula p) {
    particulas.push_back(p);
}

void Simulacion::agregarObstaculo(Obstaculo o) {
    obstaculos.push_back(o);
}

void Simulacion::colisionParedes(Particula& p) {
    if (p.x - p.radio < 0) {
        p.x = p.radio;
        p.velocidadX = -p.velocidadX;
    }
    if (p.x + p.radio > anchoCaja) {
        p.x = anchoCaja - p.radio;
        p.velocidadX = -p.velocidadX;
    }
    if (p.y - p.radio < 0) {
        p.y = p.radio;
        p.velocidadY = -p.velocidadY;
    }
    if (p.y + p.radio > altoCaja) {
        p.y = altoCaja - p.radio;
        p.velocidadY = -p.velocidadY;
    }
}

bool Simulacion::hayColisionObstaculo(Particula& p, Obstaculo& o) {
    double cercanoPX = p.x;
    double cercanoPY = p.y;

    if (p.x < o.x)           cercanoPX = o.x;
    if (p.x > o.x + o.ancho) cercanoPX = o.x + o.ancho;
    if (p.y < o.y)            cercanoPY = o.y;
    if (p.y > o.y + o.alto)  cercanoPY = o.y + o.alto;

    double dx = p.x - cercanoPX;
    double dy = p.y - cercanoPY;

    return (dx * dx + dy * dy) < (p.radio * p.radio);
}

void Simulacion::colisionObstaculo(Particula& p, Obstaculo& o) {
    if (!hayColisionObstaculo(p, o)) return;

    double solapIzq = (p.x + p.radio) - o.x;
    double solapDer = (o.x + o.ancho) - (p.x - p.radio);
    double solapArr = (p.y + p.radio) - o.y;
    double solapAba = (o.y + o.alto)  - (p.y - p.radio);

    double minSolap = solapIzq;
    if (solapDer < minSolap) minSolap = solapDer;
    if (solapArr < minSolap) minSolap = solapArr;
    if (solapAba < minSolap) minSolap = solapAba;

    if (minSolap == solapIzq) {
        p.velocidadX = -o.restitucion * p.velocidadX;
        p.x = o.x - p.radio;
    } else if (minSolap == solapDer) {
        p.velocidadX = -o.restitucion * p.velocidadX;
        p.x = o.x + o.ancho + p.radio;
    } else if (minSolap == solapArr) {
        p.velocidadY = -o.restitucion * p.velocidadY;
        p.y = o.y - p.radio;
    } else {
        p.velocidadY = -o.restitucion * p.velocidadY;
        p.y = o.y + o.alto + p.radio;
    }
}

bool Simulacion::hayColisionParticula(Particula& a, Particula& b) {
    double dx   = a.x - b.x;
    double dy   = a.y - b.y;
    double dist = sqrt(dx * dx + dy * dy);
    return dist < (a.radio + b.radio);
}

void Simulacion::paso() {
}

void Simulacion::ejecutar(int pasos, string nombreArchivo) {
    ofstream archivo;
    archivo.open(nombreArchivo);

    archivo << "= Simulacion de particulas =\n\n";
    archivo << "tiempo";
    for (int i = 0; i < particulas.size(); i++) {
        archivo << ",x" << i << ",y" << i;
    }
    archivo << "\n";

    for (int s = 0; s < pasos; s++) {
        tiempoActual = s * dt;

        archivo << tiempoActual;
        for (int i = 0; i < particulas.size(); i++) {
            if (particulas[i].activa) {
                archivo << "," << particulas[i].x << "," << particulas[i].y;
            } else {
                archivo << ",-1,-1";
            }
        }
        archivo << "\n";

        for (int i = 0; i < particulas.size(); i++) {
            if (!particulas[i].activa) continue;
            particulas[i].actualizar(dt);
            colisionParedes(particulas[i]);
            for (int j = 0; j < obstaculos.size(); j++) {
                colisionObstaculo(particulas[i], obstaculos[j]);
            }
        }

        for (int i = 0; i < particulas.size(); i++) {
            if (!particulas[i].activa) continue;
            for (int j = i + 1; j < particulas.size(); j++) {
                if (!particulas[j].activa) continue;
                if (hayColisionParticula(particulas[i], particulas[j])) {
                    cout << "Colision entre particula " << i
                         << " y particula " << j
                         << " en t=" << tiempoActual << endl;

                    archivo << ">>> Colision entre particula " << i
                            << " y particula " << j
                            << " en t=" << tiempoActual << "\n";

                    particulas[i].fusionar(particulas[j]);
                }
            }
        }
    }

    archivo.close();
    cout << "Simulacion terminada. Archivo: " << nombreArchivo << endl;
}
