#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QPixmap>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QShortcut>
#include <QStandardPaths>
#include "Catalogo.h"
#include "Aggiungi.h"
#include "Ricerca.h"
#include "../Biblioteca.h"


class MainWindow : public QMainWindow{
    Q_OBJECT

    //Classe principale per la gestione dell'interfaccia grafica.

    private:
        QStackedWidget* stackedWidget;
        Biblioteca* biblioteca;

    public:
        MainWindow(Biblioteca* bib, QWidget* parent = nullptr);

    private slots:
        void selezionaPagina(int index);
        void inputJson();
        void outputJson();

}; //MainWindow

#endif //MAINWINDOW_H