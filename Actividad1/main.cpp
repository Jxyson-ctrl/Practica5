#include <iostream>
#include "simulacion.h"
using namespace std;

int main() {
    Simulacion sim(800, 600, 0.05);

    sim.agregarParticula(Particula(100, 100,  120,  80, 1.0, 10));
    sim.agregarParticula(Particula(400, 200,  -90, 110, 1.5, 12));
    sim.agregarParticula(Particula(600, 400,   60, -70, 0.8,  8));
    sim.agregarParticula(Particula(200, 500,  100, -90, 2.0, 14));

    sim.agregarObstaculo(Obstaculo(200, 150, 80, 80, 0.7));
    sim.agregarObstaculo(Obstaculo(450, 300, 80, 80, 0.6));
    sim.agregarObstaculo(Obstaculo(150, 380, 80, 80, 0.8));
    sim.agregarObstaculo(Obstaculo(500, 150, 80, 80, 0.5));

    sim.ejecutar(2000, "salida.txt");

    return 0;
}