#include "Catalogo.h"


//Classe catalogo per la gestione dell'elenco di Risorse multimediali

Catalogo::Catalogo(Biblioteca* bib, QWidget* parent)
    : QWidget(parent), biblioteca(bib)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    

    QSplitter* splitter = new QSplitter(this);
    splitter->setHandleWidth(3);

    //Lista di sinistra
    lista = new QListWidget(this);
    lista->setSelectionMode(QAbstractItemView::SingleSelection);
    lista->setStyleSheet(
        "QListWidget::item:hover{background-color: #48727A;}"
        "QListWidget::item:selected{background-color: #FBF7EE;}"
    );
    lista->setMinimumWidth(480);
    splitter->addWidget(lista);


    //Stack di pannelli 
    pannelli = new QStackedWidget(this);

    // Logo iniziale
    logo = new QLabel(this);
    logo->setAlignment(Qt::AlignCenter);
    logo->setPixmap(QPixmap(":/icon/logo.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pannelli->addWidget(logo);

    splitter->addWidget(pannelli);
    splitter->setStretchFactor(0, 5);
    splitter->setStretchFactor(1, 6);

    layout->addWidget(splitter);

    //Connessioni
    connect(lista, &QListWidget::currentRowChanged, this, &Catalogo::cambiaDettaglio);
    connect(biblioteca, &Biblioteca::listaAggiornata, this, &Catalogo::aggiornaCatalogo);

    pannelloModifica = nullptr;

    aggiornaCatalogo();
}

//METODI PUBBLICI

void Catalogo::aggiornaCatalogo()
{
    //Salvataggio dell'id della risorsa attuale
    QString idCorrente;
    if (lista->currentRow() >= 0 && lista->currentRow() < lista->count()) {
        QListWidgetItem* currentItem = lista->item(lista->currentRow());
        if (currentItem)
            idCorrente = currentItem->data(Qt::UserRole).toString();
    }

    lista->clear();

    //Rimuovo tutto tranne il logo
    while (pannelli->count() > 1) {
        QWidget* w = pannelli->widget(1);
        pannelli->removeWidget(w);
        delete w;
    }

    int indexToSelect = -1;
    int i = 0;
    

    for (Risorsa* r : biblioteca->getList()) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(200, 80));
        item->setData(Qt::UserRole, QString::number(r->getId()));
        lista->addItem(item);

        CatalogoItem* widgetItem = new CatalogoItem(
            QString::fromStdString(r->getImgPath()),
            QString::fromStdString(r->getTitolo())
        );
        lista->setItemWidget(item, widgetItem);

        InfoVisitor* visitor = new InfoVisitor();
        r->accept(visitor);
        QWidget* pannello = visitor->getWidget();
        pannelli->addWidget(pannello);

        //connesioni con tra pannello e catalogo
        connect(visitor, &InfoVisitor::modificaSig, this, &Catalogo::onRichiestaModifica);
        connect(visitor, &InfoVisitor::prestitoSig, this, &Catalogo::onRichiestaPrestito);
        connect(visitor, &InfoVisitor::restituzioneSig, this, &Catalogo::onRichiestaRestituzione);
        connect(visitor, &InfoVisitor::rimozioneSig, this, &Catalogo::onRichiestaCancellazione);

        if (!idCorrente.isEmpty() && idCorrente == QString::number(r->getId()))
            indexToSelect = i;

        ++i;
    }

    if (lista->count() == 0) {
        mostraLogo();
    } else {
        if (indexToSelect >= 0)
            lista->setCurrentRow(indexToSelect);
        else
            lista->setCurrentRow(0);

        mostraCatalogo();
    }
}

void Catalogo::mostraRicerca(const QList<Risorsa*>& risultati)
{
    lista->clear();

    //Rimozione di tutti i pannelli tranne il logo
    while (pannelli->count() > 1) {
        QWidget* w = pannelli->widget(1);
        pannelli->removeWidget(w);
        delete w;
    }

    if (risultati.isEmpty()) {
        mostraLogo();
        return;
    }

    for (Risorsa* r : risultati) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(200, 80));
        item->setData(Qt::UserRole, QString::number(r->getId()));
        lista->addItem(item);

        CatalogoItem* widgetItem = new CatalogoItem(
            QString::fromStdString(r->getImgPath()),
            QString::fromStdString(r->getTitolo())
        );
        lista->setItemWidget(item, widgetItem);

        InfoVisitor* visitor = new InfoVisitor();
        r->accept(visitor);
        QWidget* pannello = visitor->getWidget();
        pannelli->addWidget(pannello);

        //Connessioni tra pannello e catalogo
        connect(visitor, &InfoVisitor::modificaSig, this, &Catalogo::onRichiestaModifica);
        connect(visitor, &InfoVisitor::prestitoSig, this, &Catalogo::onRichiestaPrestito);
        connect(visitor, &InfoVisitor::restituzioneSig, this, &Catalogo::onRichiestaRestituzione);
        connect(visitor, &InfoVisitor::rimozioneSig, this, &Catalogo::onRichiestaCancellazione);

    }

    lista->setCurrentRow(0);
    mostraCatalogo();
}

//METODI PRIVATI

void Catalogo::cambiaDettaglio(int row)
{
    if (row < 0 || row + 1 >= pannelli->count()) {
        mostraLogo();
    } else {
        pannelli->setCurrentIndex(row + 1);//0 =logo
    }
}

void Catalogo::mostraLogo()
{
    pannelli->setCurrentIndex(0);
}

void Catalogo::mostraCatalogo()
{
    if (lista->count() > 0 && lista->currentRow() >= 0)
        pannelli->setCurrentIndex(lista->currentRow() + 1);
}

//SLOT EVENTI

void Catalogo::onRichiestaModifica(Risorsa* r) {
    if (!r) return;
        pannelloModifica = new Modifica(r, this);
        pannelli->addWidget(pannelloModifica); 
        pannelli->setCurrentWidget(pannelloModifica);

        //Conferma
        connect(pannelloModifica, &Modifica::confermato, this, [this, r](Risorsa*){
            mostraDettaglio(r);
            aggiornaCatalogo();         
            emit biblioteca->listaAggiornata();
            //pannelloModifica->deleteLater();
            //daCestinare = pannelloModifica;
        });

        //Annulla
        connect(pannelloModifica, &Modifica::annullato, this, [this, r](){
            mostraDettaglio(r);          
            pannelloModifica->deleteLater();
        });

    
}

void Catalogo::onRichiestaPrestito(Risorsa* r) {
    if(r->prestito()) {
        aggiornaCatalogo();
        emit biblioteca->listaAggiornata();
    }
    
    else QMessageBox::warning(this, "Prestito non disponibile", "Attualmente non ci sono copie disponibili al prestito");
    
}

void Catalogo::onRichiestaCancellazione(Risorsa* r) {

    QMessageBox::StandardButton resp = QMessageBox::question(this,
            "Conferma cancellazione",
            "Sei sicuro di voler cancellare " + QString::fromStdString(r->getTitolo()) + "?",
            QMessageBox::Yes | QMessageBox::No
        );
        if(resp == QMessageBox::Yes){
            biblioteca->deleteRisorsa(r);
        }
}

void Catalogo::onRichiestaRestituzione(Risorsa* r) {

    if(r->restituzione()) {
        aggiornaCatalogo();
        emit biblioteca->listaAggiornata();
    }
    else QMessageBox::warning(this, "Errore di restituzione", "Tutte le copie sono già state restituite");

}

void Catalogo::mostraDettaglio(Risorsa* r) {
    if (!r) return;

    QString idTarget = QString::number(r->getId());

    //La lista e i pannelli hanno lo stesso ordine
    for (int i = 0; i < lista->count(); ++i) {
        QListWidgetItem* item = lista->item(i);
        if (!item) continue;

        QString idItem = item->data(Qt::UserRole).toString();
        if (idItem == idTarget) {
            lista->setCurrentRow(i);
            pannelli->setCurrentIndex(i + 1);
            break;
        }
    }
}

