#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    contadorPasos = 0;
    juego = new Juego(775, 340, 0.1);
    juego->iniciar();

    spriteJugador1.load(":/sprites/jugador1.png");
    spriteJugador2.load(":/sprites/jugador2.png");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);
}

MainWindow::~MainWindow() {
    delete ui;
    delete juego;
}

void MainWindow::actualizar() {
    juego->paso();
    update();

    if (juego->proyectil != nullptr && juego->proyectil->activo) {
        if (juego->proyectil->rapidez() < 8.0) {
            juego->cambiarTurno();
            timer->stop();
            update();
        }
    }

    if (juego->juegoTerminado) {
        timer->stop();
        QMessageBox::information(this, "Juego terminado",
                                 QString::fromStdString("Gano " + juego->ganador));
    }
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    // Fondo oscuro
    painter.fillRect(0, 0, 775, 340, QColor(30, 30, 30));
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(0, 0, 774, 339);

    // Obstáculos jugador 1
    for (int i = 0; i < juego->obstaculosJugador1.size(); i++) {
        ObstaculoJuego& o = juego->obstaculosJugador1[i];
        if (!o.estaDestruido()) {
            painter.setBrush(QColor(80, 160, 80));
            painter.setPen(QPen(Qt::white, 1));
            painter.drawRect(o.x, o.y, o.ancho, o.alto);
            painter.setPen(Qt::white);
            painter.drawText(o.x + 5, o.y + 18,
                             QString::number((int)o.resistencia));
        }
    }

    // Obstáculos jugador 2
    for (int i = 0; i < juego->obstaculosJugador2.size(); i++) {
        ObstaculoJuego& o = juego->obstaculosJugador2[i];
        if (!o.estaDestruido()) {
            painter.setBrush(QColor(160, 80, 80));
            painter.setPen(QPen(Qt::white, 1));
            painter.drawRect(o.x, o.y, o.ancho, o.alto);
            painter.setPen(Qt::white);
            painter.drawText(o.x + 5, o.y + 18,
                             QString::number((int)o.resistencia));
        }
    }

    painter.drawPixmap(95, 250, 70, 90, spriteJugador1);
    painter.setPen(Qt::white);
    painter.drawText(110, 345, "Rival");

    painter.drawPixmap(575, 250, 70, 90, spriteJugador2);
    painter.setPen(Qt::white);
    painter.drawText(590, 345, "Rival");

    // Proyectil
    if (juego->proyectil != nullptr && juego->proyectil->activo) {
        painter.setBrush(Qt::red);
        painter.setPen(Qt::black);
        painter.drawEllipse(
            (int)(juego->proyectil->x - juego->proyectil->radio),
            (int)(juego->proyectil->y - juego->proyectil->radio),
            (int)(juego->proyectil->radio * 2),
            (int)(juego->proyectil->radio * 2)
            );
    }

    // Turno
    painter.setPen(Qt::white);
    if (juego->turno == 0) {
        painter.drawText(320, 20, "Turno: Jugador 1");
    } else {
        painter.drawText(320, 20, "Turno: Jugador 2");
    }
}

void MainWindow::on_btnLanzar_clicked() {
    if (juego->juegoTerminado) return;

    double angulo    = ui->spinAngulo->value();
    double velocidad = ui->spinVelocidad->value();
    double masa      = 1.0;

    if (juego->turno == 0) {
        juego->lanzarProyectil(280, 220, angulo, velocidad, masa);
    } else {
        juego->lanzarProyectil(490, 220, 180 - angulo, velocidad, masa);
    }

    contadorPasos = 0;
    timer->start(16);
}

void MainWindow::on_btnCambiarTurno_clicked() {
    juego->cambiarTurno();
    contadorPasos = 0;
    timer->stop();
    update();
}
