//Mi scuso anche qua per i commenti "Evidenti"
#include "Ricerca.h"

Ricerca::Ricerca(Biblioteca* bib, QWidget* parent)
    : QWidget(parent), biblioteca(bib)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);

    ///////////////////// BARRA DI RICERCA E FILTRI ////////////////////////////////////////////
    QHBoxLayout* layoutRicerca = new QHBoxLayout();

    //Stile generale
    QString ricercaStile = R"(
        QLineEdit{
            font-size: 13pt;
            min-height: 20px;
            padding: 4px 8px;
            border: 2px solid #333333;
        }

        QPushButton {
            background-color: white;
            border: 2px solid #333333;
            border-radius: 10px;
            padding: 3px 6px;
            color: #333333;
            min-height: 20px;
            min-width: 100px;
            font-size: 15px;
        }

        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }

        QPushButton:pressed {
            background-color: #36555B;
            color: white;
        }

        QFormLayout {
            spacing: 8px;
        }
        
        QComboBox {
            background: white;
            border-radius: 2px;
            padding: 4px 10px;              
            min-height: 20px;       
            font-size: 13px;
            border: 2px solid #333333;
        }

        /* drop-down button */
        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 30px;
            border-left: 1px solid #cccccc;
        }

        /* popup*/
        QComboBox QAbstractItemView {
            background: white;
            border: 1px solid #dcdcdc;
            selection-background-color: #48727A;
            selection-color: white;
            outline: 0;
            font-size: 13px;
            padding: 1px;
        }

        /* style per gli item*/
        QComboBox QAbstractItemView::item {
            padding: 4px 8px;
        }

        /* hover / focus */
        QComboBox:hover, QComboBox:focus {
            border-color: #48727A;
        }

        QComboBox QAbstractItemView::item:hover {
            background-color: #48727A;
            color: white;
        }
            QComboBox QAbstractItemView::item:selected {
            background-color: #48727A;
            color: white;
        }
    )";

    //Barra di ricerca
    barra = new QLineEdit(this);
    barra->setPlaceholderText("Ricerca per titolo...");
    barra->setStyleSheet(ricercaStile);
    layoutRicerca->addWidget(barra);
    layoutRicerca->setContentsMargins(10, 5, 10, 5);

    //Filtro tipo
    filtroTipo = new QComboBox(this);
    filtroTipo->addItems({"Tutti", "Libro", "Rivista", "Dvd", "Vinile"});
    filtroTipo->setView(new QListView(filtroTipo));
    filtroTipo->view()->setMouseTracking(true); 
    filtroTipo->setStyleSheet(ricercaStile);
    layoutRicerca->addWidget(filtroTipo);

    //Filtro anno
    filtroAnno = new QComboBox(this);
    filtroAnno->addItems({"Tutti", "Prima del 1800", "1800-1900", "1901-2000", "Dopo il 2000"});
    filtroAnno->setView(new QListView(filtroAnno));
    filtroAnno->view()->setMouseTracking(true); 
    filtroAnno->setStyleSheet(ricercaStile);
    layoutRicerca->addWidget(filtroAnno);

    //Filtro disponibilità
    filtroDisponibili = new QComboBox(this);
    filtroDisponibili->addItems({"Tutti", "Disponibili al prestito"});
    filtroDisponibili->setView(new QListView(filtroDisponibili));
    filtroDisponibili->view()->setMouseTracking(true); 
    filtroDisponibili->setStyleSheet(ricercaStile);
    layoutRicerca->addWidget(filtroDisponibili);

    //Pulsante reset
    QPushButton* resetBtn = new QPushButton("Reset");
    resetBtn->setStyleSheet(ricercaStile);
    layoutRicerca->addWidget(resetBtn);
    connect(resetBtn, &QPushButton::clicked, this, &Ricerca::resetFiltri);

    layout->addLayout(layoutRicerca);

    ////////////////////// CATALOGO ////////////////////////////////////////////////////////////////
    catalogo = new Catalogo(biblioteca, this);
    catalogo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(catalogo);

    ///////////////////// CONNESSIONI ////////////////////////////////////////////////////////////
    connect(barra, &QLineEdit::textChanged, this, &Ricerca::aggiornamento);
    connect(filtroTipo, &QComboBox::currentTextChanged, this, &Ricerca::aggiornamento);
    connect(filtroAnno, &QComboBox::currentTextChanged, this, &Ricerca::aggiornamento);
    connect(filtroDisponibili, &QComboBox::currentTextChanged, this, &Ricerca::aggiornamento);
}

///////////////////// SLOT AGGIORNAMENTO //////////////////////////////////////////////////////
void Ricerca::aggiornamento()
{
    QString testo = barra->text().toLower();
    QString tipo = filtroTipo->currentText();
    QString anno = filtroAnno->currentText();
    bool disp = (filtroDisponibili->currentText() == "Disponibili al prestito");

    int annoMin = 0;
    int annoMax = 2200;

    if (anno == "Prima del 1800") annoMax = 1799;
    else if (anno == "1800-1900") { annoMin = 1800; annoMax = 1900; }
    else if (anno == "1901-2000") { annoMin = 1901; annoMax = 2000; }
    else if (anno == "Dopo il 2000") annoMin = 2001;

    QList<Risorsa*> risultati;

    //mostra tutto se non ci sono condizioni di ricerca
    if (testo.isEmpty() && tipo=="Tutti" && anno=="Tutti" && !disp) {
        risultati = biblioteca->getList();
    } else {
        risultati = biblioteca->search(testo, tipo, annoMin, annoMax, disp);
    }

    catalogo->mostraRicerca(risultati);
}

///////////////////// SLOT RESET //////////////////////////////////////////////////////////////
void Ricerca::resetFiltri()
{
    barra->clear();
    filtroTipo->setCurrentIndex(0);
    filtroAnno->setCurrentIndex(0);
    filtroDisponibili->setCurrentIndex(0);
    aggiornamento();
}
