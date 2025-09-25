#ifndef AGGIUNGI_H
#define AGGIUNGI_H

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "../modello_logico/Risorsa.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QListView>
#include "../modello_logico/Libro.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/Dvd.h"
#include "../modello_logico/Vinile.h"
#include "../Biblioteca.h"

//Classe per aggiungere risorse alla biblioteca 

class Aggiungi : public QWidget {
    Q_OBJECT

public:
    explicit Aggiungi(Biblioteca* bib, QWidget* parent = nullptr);

private:
    Biblioteca* biblioteca;

    QStackedWidget* stack;

    //Pannelli per ogni tipo di risorsa
    QWidget* pannelloScelta;
    QWidget* pannelloLibro;
    QWidget* pannelloRivista;
    QWidget* pannelloDvd;
    QWidget* pannelloVinile;
};
//Aggiungi.h


#endif//AGGIUNGI_H