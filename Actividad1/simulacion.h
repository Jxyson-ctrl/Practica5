#ifndef SIMULACION_H
#define SIMULACION_H

#include "particula.h"
#include "obstaculo.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Simulacion {
public:
    double anchoCaja;
    double altoCaja;
    double dt;
    double tiempoActual;
    vector<Particula> particulas;
    vector<Obstaculo> obstaculos;

    Simulacion(double anchoCaja, double altoCaja, double dt);

    void agregarParticula(Particula p);
    void agregarObstaculo(Obstaculo o);
    void paso();
    void ejecutar(int pasos, string nombreArchivo);

private:
    void colisionParedes(Particula& p);
    void colisionObstaculo(Particula& p, Obstaculo& o);
    void colisionParticulas(ofstream& logColisiones);
    bool hayColisionObstaculo(Particula& p, Obstaculo& o);
    bool hayColisionParticula(Particula& a, Particula& b);
};

#endif
