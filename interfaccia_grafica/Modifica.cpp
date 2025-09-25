#include "Modifica.h"

Modifica::Modifica(Risorsa* r, QWidget* parent)
    : QWidget(parent), originale(r)
{
    //Layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15,15,15,15);
    mainLayout->setSpacing(10);
    
    form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    mainLayout->addLayout(form);

    //Campi comuni
    campiComuni(r);

    //Campi specifici
    r->accept(this);


    //Pulsanti
    QHBoxLayout* barraLayout = new QHBoxLayout();
    barraLayout->setSpacing(20);
    barraLayout->addStretch();

    QPushButton* confermaBtn = new QPushButton("Conferma");
    QPushButton* annullaBtn = new QPushButton("Annulla");

    //Stile pulsanti
    QString buttonStyle = R"(
        QPushButton {
            background-color: white;
            border: 2px solid #333333;
            border-radius: 10px;
            color: #333333;
            min-height: 25px;
            max-height: 25px;
            min-width: 150px;
            max-width: 300px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }
    )";

    confermaBtn->setStyleSheet(buttonStyle);
    annullaBtn->setStyleSheet(buttonStyle);
    
    barraLayout->addWidget(confermaBtn);
    barraLayout->addWidget(annullaBtn);
    barraLayout->addStretch();
    
    mainLayout->addLayout(barraLayout);

    //Stile generale
    QString modificaStyle = R"(
        QLabel {
            font-size: 13pt;
            color: #333333;
        }

        QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {
            font-size: 13pt;
            min-height: 30px;
            min-width: 300px;
            padding: 4px 8px;
        }

        QPushButton {
            background-color: white;
            border: 1px solid #333333;
            border-radius: 10px;
            padding: 6px 12px;
            color: #333333;
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
            spacing: 10px;
        }
            QComboBox {
            background: white;
            border-radius: 2px;
            padding: 4px 10px;       
            min-width: 245px;        
            min-height: 30px;       
            font-size: 13px;
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


    this->setStyleSheet(modificaStyle);
    

    //Connessioni 
    connect(confermaBtn, &QPushButton::clicked, this, &Modifica::conferma);
    connect(annullaBtn, &QPushButton::clicked, this, &Modifica::cancella);
}

void Modifica::campiComuni(const Risorsa* r) {
    titolo = new QLineEdit(QString::fromStdString(r->getTitolo()));
    anno = new QSpinBox(); anno->setRange(0, 2200); anno->setValue(r->getAnnoPubblicazione());
    prezzo = new QDoubleSpinBox(); prezzo->setRange(0.0, 10000.0); prezzo->setDecimals(2); prezzo->setValue(r->getPrezzo());
    copie = new QSpinBox(); copie->setRange(1, 1000); copie->setValue(r->getCopieBiblioteca());
    imgPath = new QLineEdit(QString::fromStdString(r->getImgPath()));
    QPushButton* browse = new QPushButton("Sfoglia...");
    QHBoxLayout* pathLayout = new QHBoxLayout(); pathLayout->addWidget(imgPath); pathLayout->addWidget(browse);
    connect(browse, &QPushButton::clicked, this, [=](){
        QString file = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), "Immagini (*.png *.jpg)");
        if (!file.isEmpty()) imgPath->setText(file);
    });

    form->addRow("Titolo", titolo);
    form->addRow("Anno pubblicazione", anno);
    form->addRow("Prezzo", prezzo);
    form->addRow("Copie", copie);
    form->addRow("Copertina", pathLayout);
}

//VISITOR

void Modifica::visit(Libro* libro){
    autore = new QLineEdit(QString::fromStdString(libro->getAutore()));
    casaEditrice = new QLineEdit(QString::fromStdString(libro->getCasaEditrice()));
    pagine = new QSpinBox(); pagine->setRange(1, 5000); pagine->setValue(libro->getNPagine());
    genere = new QComboBox(); genere->addItems({"Fantascienza","Fantasy","Gotico","Autobiografia","Narrativa"});
    genere->setCurrentText(QString::fromStdString(libro->getGenereToString()));
    genere->setView(new QListView(genere));
    genere->view()->setMouseTracking(true); 
    lingua = new QLineEdit(QString::fromStdString(libro->getLinguaOriginale()));

    form->addRow("Autore", autore);
    form->addRow("Casa editrice", casaEditrice);
    form->addRow("Pagine", pagine);
    form->addRow("Genere", genere);
    form->addRow("Lingua originale", lingua);
}

void Modifica::visit(Rivista* rivista){
    autore = new QLineEdit(QString::fromStdString(rivista->getAutore()));
    casaEditrice = new QLineEdit(QString::fromStdString(rivista->getCasaEditrice()));
    pagine = new QSpinBox(); pagine->setRange(1, 5000); pagine->setValue(rivista->getNPagine());
    periodicita = new QComboBox(); periodicita->addItems({"Settimanale","Mensile","Bimestrale"});
    periodicita->setCurrentText(QString::fromStdString(rivista->getPeriodicitaToString()));
    periodicita->setView(new QListView(periodicita));
    periodicita->view()->setMouseTracking(true); 
    argomento = new QComboBox(); argomento->addItems({"Attualita","Cronaca","Scienze","Enigmistica"});
    argomento->setCurrentText(QString::fromStdString(rivista->getArgomentoToString()));
    argomento->setView(new QListView(argomento));
    argomento->view()->setMouseTracking(true); 

    form->addRow("Autore", autore);
    form->addRow("Casa editrice", casaEditrice);
    form->addRow("Pagine", pagine);
    form->addRow("Periodicità", periodicita);
    form->addRow("Argomento", argomento);
}

void Modifica::visit(Dvd* film){
    durata = new QSpinBox(); durata->setRange(1, 1000); durata->setValue(film->getDurata());
    regista = new QLineEdit(QString::fromStdString(film->getRegista()));
    extra = new QComboBox(); extra->addItems({"Si","No"});
    extra->setCurrentText(film->getContenutiBonus()? "Si" : "No");
    extra->setView(new QListView(extra));
    extra->view()->setMouseTracking(true); 

    form->addRow("Regista", regista);
    form->addRow("Durata", durata);
    form->addRow("Contenuti extra", extra);
}

void Modifica::visit(Vinile* vin){
    durata = new QSpinBox(); durata->setRange(1, 1000); durata->setValue(vin->getDurata());
    autoreVinile = new QLineEdit(QString::fromStdString(vin->getAutore()));
    casaDiscografica = new QLineEdit(QString::fromStdString(vin->getCasaDiscografica()));
    tracce = new QSpinBox(); tracce->setRange(1, 100); tracce->setValue(vin->getNTracce());

    form->addRow("Autore", autoreVinile);
    form->addRow("Casa discografica", casaDiscografica);
    form->addRow("Durata", durata);
    form->addRow("Numero tracce", tracce);
}

//SLOT

void Modifica::conferma(){
    // Campi comuni
    originale->setTitolo(titolo->text().toStdString());
    originale->setAnnoPubblicazione(anno->value());
    originale->setPrezzo(prezzo->value());
    originale->setCopieBiblioteca(copie->value());
    originale->setImgPath(imgPath->text().toStdString());

    // Campi specifici
    if(auto r = dynamic_cast<Libro*>(originale)){
        r->setAutore(autore->text().toStdString());
        r->setCasaEditrice(casaEditrice->text().toStdString());
        r->setNPagine(pagine->value());

        Libro::Genere gen;
        QString g = genere->currentText();
        if(g=="Fantascienza") gen = Libro::Fantascienza;
        else if(g=="Fantasy") gen = Libro::Fantasy;
        else if(g=="Gotico") gen = Libro::Gotico;
        else if(g=="Autobiografia") gen = Libro::Autobiografia;
        else gen = Libro::Narrativa;
        r->setGenere(gen);
        r->setLinguaOriginale(lingua->text().toStdString());
    }
    else if(auto r = dynamic_cast<Rivista*>(originale)){
        r->setAutore(autore->text().toStdString());
        r->setCasaEditrice(casaEditrice->text().toStdString());
        r->setNPagine(pagine->value());

        Rivista::Periodicita per;
        QString p = periodicita->currentText();
        if(p=="Settimanale") per = Rivista::Settimanale;
        else if(p=="Mensile") per = Rivista::Mensile;
        else per = Rivista::Bimestrale;
        r->setPeriodicita(per);

        Rivista::Argomento arg;
        QString a = argomento->currentText();
        if(a=="Attualita") arg = Rivista::Attualita;
        else if(a=="Cronaca") arg = Rivista::Cronaca;
        else if(a=="Scienze") arg = Rivista::Scienze;
        else arg = Rivista::Enigmistica;
        r->setArgomento(arg);
    }
    else if(auto r = dynamic_cast<Dvd*>(originale)){
        r->setDurata(durata->value());
        r->setRegista(regista->text().toStdString());
        r->setContenutiBonus(extra->currentText()=="Si");
    }
    else if(auto r = dynamic_cast<Vinile*>(originale)){
        r->setDurata(durata->value());
        r->setAutore(autoreVinile->text().toStdString());
        r->setCasaDiscografica(casaDiscografica->text().toStdString());
        r->setNTracce(tracce->value());
    }

    emit confermato(originale);
}

void Modifica::cancella(){
    emit annullato();
}



