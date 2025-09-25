#include "InfoVisitor.h"

InfoVisitor::InfoVisitor(QObject* parent) :QObject(parent), widget(nullptr) {}

//Libro
void InfoVisitor::visit(Libro* libro){
    QStringList info;
    info << "<b>Titolo:</b> "+ QString::fromStdString(libro->getTitolo())
        << "<b>Classe:</b> Libro"
        << "<b>Id:</b> "+ QString::number(libro->getId())
        << "<b>Anno:</b> "+ QString::number(libro->getAnnoPubblicazione())
        << "<b>Prezzo:</b> "+ QString::number(libro->getPrezzo())
        << "<b>Copie biblioteca:</b> "+ QString::number(libro->getCopieBiblioteca())
        << "<b>Copie disponibili:</b> "+ QString::number(libro->getDisponibili())
        << "<b>Autore:</b> "+ QString::fromStdString(libro->getAutore())
        << "<b>Casa editrice:</b> "+ QString::fromStdString(libro->getCasaEditrice())
        << "<b>Numero di pagine:</b> "+ QString::number(libro->getNPagine())
        << "<b>Genere:</b> "+ QString::fromStdString(libro->getGenereToString())
        << "<b>Lingua Originale:</b> "+ QString::fromStdString(libro->getLinguaOriginale());

    widget = layoutComune(QString::fromStdString(libro->getImgPath()), info, libro);
}

//Rivista
void InfoVisitor::visit(Rivista* rivista){
    QStringList info;
    info << "<b>Titolo:</b> "+ QString::fromStdString(rivista->getTitolo())
        << "<b>Classe:</b> Rivista"
        << "<b>Id:</b> "+ QString::number(rivista->getId())
        << "<b>Anno:</b> "+ QString::number(rivista->getAnnoPubblicazione())
        << "<b>Prezzo:</b> "+ QString::number(rivista->getPrezzo())
        << "<b>Copie biblioteca:</b> "+ QString::number(rivista->getCopieBiblioteca())
        << "<b>Copie disponibili:</b> "+ QString::number(rivista->getDisponibili())
        << "<b>Autore:</b> "+ QString::fromStdString(rivista->getAutore())
        << "<b>Casa editrice:</b> "+ QString::fromStdString(rivista->getCasaEditrice())
        << "<b>Numero di pagine:</b> "+ QString::number(rivista->getNPagine())
        << "<b>Periodicità:</b> "+ QString::fromStdString(rivista->getPeriodicitaToString())
        << "<b>Argomento:</b> "+ QString::fromStdString(rivista->getArgomentoToString());

    widget = layoutComune(QString::fromStdString(rivista->getImgPath()), info, rivista);
}

//Film
void InfoVisitor::visit(Dvd* film){
    QStringList info;
    info << "<b>Titolo:</b> "+ QString::fromStdString(film->getTitolo())
        << "<b>Classe:</b> Dvd"
        << "<b>Id:</b> "+ QString::number(film->getId())
        << "<b>Anno:</b> "+ QString::number(film->getAnnoPubblicazione())
        << "<b>Prezzo:</b> "+ QString::number(film->getPrezzo())
        << "<b>Copie biblioteca:</b> "+ QString::number(film->getCopieBiblioteca())
        << "<b>Copie disponibili:</b> "+ QString::number(film->getDisponibili())
        << "<b>Durata (minuti):</b> "+ QString::number(film->getDurata())
        << "<b>Regista:</b> "+ QString::fromStdString(film->getRegista())
        << "<b>Contenuti aggiuntivi:</b> "+ QString::fromStdString(film->getContenutiBonus()? "Si" : "No");

    widget = layoutComune(QString::fromStdString(film->getImgPath()), info, film);
}

//Vinile
void InfoVisitor::visit(Vinile* vin){
    QStringList info;
    info << "<b>Titolo:</b> "+ QString::fromStdString(vin->getTitolo())
        << "<b>Classe:</b> Vinile"
        << "<b>Id:</b> "+ QString::number(vin->getId())
        << "<b>Anno:</b> "+ QString::number(vin->getAnnoPubblicazione())
        << "<b>Prezzo:</b> "+ QString::number(vin->getPrezzo())
        << "<b>Copie biblioteca:</b> "+ QString::number(vin->getCopieBiblioteca())
        << "<b>Copie disponibili:</b> "+ QString::number(vin->getDisponibili())
        << "<b>Durata (minuti):</b> "+ QString::number(vin->getDurata())
        << "<b>Autore:</b> "+ QString::fromStdString(vin->getAutore())
        << "<b>Casa discografica:</b> "+ QString::fromStdString(vin->getCasaDiscografica())
        << "<b>Numero tracce:</b> "+ QString::number(vin->getNTracce());

    widget = layoutComune(QString::fromStdString(vin->getImgPath()), info, vin);
}

QWidget* InfoVisitor::getWidget() const{
    return widget;
}

QWidget* InfoVisitor::layoutComune(const QString& path_img, const QStringList& info, Risorsa* r){
    QWidget* w = new QWidget();
    QString panelStyle = R"(
        QWidget {
            background-color: #FBF7EE;
            padding: 0,0;
        }

        QLabel {
            font-size: 13pt;
            color: #333333;
        }

        QPushButton {
            background-color: white;
            border: 2px solid #333333;
            border-radius: 10px;
            padding: 6px 12px;
            color: #333333;
            min-height: 25px;
            max-height: 25px;
            min-width: 110px;
            font-size: 13px;
        }

        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }

        QPushButton:pressed {
            background-color: #36555B;
            color: white;
        }
    )";
    
    QVBoxLayout* layout = new QVBoxLayout(w);
    layout->setAlignment(Qt::AlignTop);
    layout->addStretch();

    //Immagine copertina
    QLabel* cop = new QLabel();
    QPixmap pix(path_img);
    cop->setPixmap(pix.scaled(150,150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cop->setAlignment(Qt::AlignHCenter);
    layout->addWidget(cop);
    layout->addStretch();

    //Informazioni comuni
    for(const QString& s : info){
        QLabel* i = new QLabel(s);
        i->setAlignment(Qt::AlignHCenter);
        layout->addWidget(i);
    }

    layout->addStretch();

    //Bottoni
    QWidget* barra = new QWidget();
    QHBoxLayout* layoutBarra = new QHBoxLayout(barra);
    layoutBarra->setSpacing(10);
    layoutBarra->setContentsMargins(5, 10, 5, 10);

    QPushButton* prestito = new QPushButton("Prendi in prestito");
    QPushButton* restitiuzione = new QPushButton("Restituisci");
    QPushButton* rimuovi = new QPushButton("Rimuovi dal catalogo");
    QPushButton* modifica = new QPushButton("Modifica");

    layoutBarra->addWidget(prestito);
    layoutBarra->addWidget(restitiuzione);
    layoutBarra->addWidget(rimuovi);
    layoutBarra->addWidget(modifica);

    layout->addWidget(barra);

    w->setMinimumWidth(670);
    w->setMinimumHeight(490);
    w->setStyleSheet(panelStyle);
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Collegamento con i signals
    connect(prestito, &QPushButton::clicked, this, [this, r](){emit prestitoSig(r);});
    connect(restitiuzione, &QPushButton::clicked, this, [this, r](){emit restituzioneSig(r);});
    connect(rimuovi, &QPushButton::clicked, this, [this, r](){emit rimozioneSig(r);});
    connect(modifica, &QPushButton::clicked, this, [this, r](){emit modificaSig(r);});

    return w;

}