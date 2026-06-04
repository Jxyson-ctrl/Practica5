/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnLanzar;
    QSpinBox *spinAngulo;
    QSpinBox *spinVelocidad;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnCambiarTurno;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(775, 435);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnLanzar = new QPushButton(centralwidget);
        btnLanzar->setObjectName("btnLanzar");
        btnLanzar->setGeometry(QRect(690, 40, 80, 24));
        spinAngulo = new QSpinBox(centralwidget);
        spinAngulo->setObjectName("spinAngulo");
        spinAngulo->setGeometry(QRect(620, 120, 81, 31));
        spinAngulo->setMaximum(90);
        spinAngulo->setValue(1);
        spinVelocidad = new QSpinBox(centralwidget);
        spinVelocidad->setObjectName("spinVelocidad");
        spinVelocidad->setGeometry(QRect(620, 80, 81, 31));
        spinVelocidad->setMinimum(0);
        spinVelocidad->setMaximum(500);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(710, 130, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(710, 90, 61, 16));
        btnCambiarTurno = new QPushButton(centralwidget);
        btnCambiarTurno->setObjectName("btnCambiarTurno");
        btnCambiarTurno->setGeometry(QRect(690, 10, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 775, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnLanzar->setText(QCoreApplication::translate("MainWindow", "Lanzar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\303\201ngulo:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Velocidad:", nullptr));
        btnCambiarTurno->setText(QCoreApplication::translate("MainWindow", "Pasar Turno", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
