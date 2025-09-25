#ifndef RICERCA_H
#define RICERCA_H
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "../modello_logico/Risorsa.h"
#include "Catalogo.h"
#include "../Biblioteca.h"

class Ricerca : public QWidget{
    Q_OBJECT

    private:
        QLineEdit* barra;
        QComboBox* filtroTipo;
        QComboBox* filtroAnno;
        QComboBox* filtroDisponibili;
        Catalogo* catalogo;
        Biblioteca* biblioteca;

        void resetFiltri();

    public:
        Ricerca(Biblioteca* bib, QWidget* parent = nullptr);

    private slots:
        void aggiornamento();


}; //Ricerca


#endif //RICERCA_H