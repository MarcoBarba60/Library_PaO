#ifndef CATALOGO_H
#define CATALOGO_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSplitter>
#include <QPixmap>
#include <QSizePolicy>
#include "../Biblioteca.h"
#include "../modello_logico/Risorsa.h"
#include "Modifica.h"
#include "CatalogoItem.h"
#include "InfoVisitor.h"


class Catalogo : public QWidget
{
    Q_OBJECT

public:
    explicit Catalogo(Biblioteca* bib, QWidget* parent = nullptr);

    void aggiornaCatalogo();
    void mostraRicerca(const QList<Risorsa*>& risultati);

private slots:
    void cambiaDettaglio(int row);
    void onRichiestaModifica(Risorsa* r);
    void onRichiestaPrestito(Risorsa* r);
    void onRichiestaRestituzione(Risorsa* r);
    void onRichiestaCancellazione(Risorsa* r);

private:
    void mostraLogo();
    void mostraCatalogo();
    void mostraDettaglio(Risorsa* r);

    Biblioteca* biblioteca;
    QListWidget* lista;
    QStackedWidget* pannelli;
    QLabel* logo;
    Modifica* pannelloModifica; 

}; //Catalogo.h

#endif //CATALOGO_H
