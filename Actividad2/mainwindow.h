#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include "juego.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Juego* juego;
    QTimer* timer;
    int contadorPasos;
    QPixmap spriteJugador1;
    QPixmap spriteJugador2;

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void actualizar();
    void on_btnLanzar_clicked();
    void on_btnCambiarTurno_clicked();

private:
    Ui::MainWindow *ui;
};

#endif
