#ifndef MODIFICA_H
#define MODIFICA_H

#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QListView>
#include <QStandardPaths>
#include <QFileDialog>
#include "../Visitor.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/Dvd.h"
#include "../modello_logico/Vinile.h"

class Modifica : public QWidget, public Visitor {
    Q_OBJECT
//Classe per la modifica delle risorse multimediali che sfrutta visitor per personalizzare il pannello
public:
    explicit Modifica(Risorsa* r, QWidget* parent = nullptr);
    ~Modifica() = default;

    void visit(Libro* libro) override;
    void visit(Rivista* rivista) override;
    void visit(Dvd* film) override;
    void visit(Vinile* vin) override;

signals:
    void confermato(Risorsa* r);
    void annullato();

private slots:
    void conferma();
    void cancella();

private:
    Risorsa* originale;
    QFormLayout* form;

    //Campi comuni
    QLineEdit* titolo;
    QSpinBox* anno;
    QDoubleSpinBox* prezzo;
    QSpinBox* copie;
    QLineEdit* imgPath;

    //Campi specifici
    QLineEdit* autore;
    QLineEdit* casaEditrice;
    QSpinBox* pagine;
    QComboBox* genere;
    QLineEdit* lingua;
    QComboBox* periodicita;
    QComboBox* argomento;
    QSpinBox* durata;
    QLineEdit* regista;
    QComboBox* extra;
    QLineEdit* autoreVinile;
    QLineEdit* casaDiscografica;
    QSpinBox* tracce;

    void campiComuni(const Risorsa* r);
};//Modifica.h

#endif //MODIFICA_H
