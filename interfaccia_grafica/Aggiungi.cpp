#include "Aggiungi.h"

Aggiungi::Aggiungi(Biblioteca* bib, QWidget* parent)
    : QWidget(parent), biblioteca(bib)
{
    stack = new QStackedWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);

    QString panelStyle = R"(
        QLabel {
            font-size: 15pt;
        }
        QLineEdit, QSpinBox, QDoubleSpinBox {
            font-size: 13pt;
            min-height: 40px;
            min-width: 300px;
        }
        QPushButton {
            background-color: white;
            border: 1px solid #333333;
            border-radius: 10px;
            padding: 6px 12px;
            color: #333333;
        }
        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }
        QPushButton:pressed {
            background-color: #36555B;
            color: white;
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

    //Stile bottoni pannello di scelta
    QString sceltaButtonStyle = R"(
        QPushButton {
            background-color: white;
            border: 2px solid #333333;
            border-radius: 10px;
            color: #333333;
            min-height: 40px;   /* più spessi */
            max-height: 40px;
            min-width: 400px;   /* più corti */
            font-size: 15px;
        }
        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }
    )";

    //Stile generico
    QString navButtonStyle = R"(
        QPushButton {
            background-color: white;
            border: 2px solid #333333;
            border-radius: 10px;
            color: #333333;
            min-height: 30px;
            max-height: 30px;
            min-width: 200px;
            max-width: 400px;
            font-size: 15px;
        }
        QPushButton:hover {
            background-color: #48727A;
            color: white;
        }
    )";


//PANNELLO SCELTA
    pannelloScelta = new QWidget();
    QVBoxLayout* layoutScelta = new QVBoxLayout(pannelloScelta);

    layoutScelta->setAlignment(Qt::AlignCenter);
    layoutScelta->setSpacing(50);

    QPushButton* btnLibro   = new QPushButton("Aggiungi LIBRO");
    QPushButton* btnRivista = new QPushButton("Aggiungi RIVISTA");
    QPushButton* btnDvd     = new QPushButton("Aggiungi DVD");
    QPushButton* btnVinile  = new QPushButton("Aggiungi VINILE");

    btnLibro->setStyleSheet(sceltaButtonStyle);
    btnRivista->setStyleSheet(sceltaButtonStyle);
    btnDvd->setStyleSheet(sceltaButtonStyle);
    btnVinile->setStyleSheet(sceltaButtonStyle);

    layoutScelta->addWidget(btnLibro, 0, Qt::AlignCenter);
    layoutScelta->addWidget(btnRivista, 0, Qt::AlignCenter);
    layoutScelta->addWidget(btnDvd, 0, Qt::AlignCenter);
    layoutScelta->addWidget(btnVinile, 0, Qt::AlignCenter);

    stack->addWidget(pannelloScelta);


//PANNELLO LIBRO
    pannelloLibro = new QWidget();
    pannelloLibro->setStyleSheet(panelStyle);
    QVBoxLayout* mainLayoutLibro = new QVBoxLayout(pannelloLibro);

    QFormLayout* libroLayout = new QFormLayout(pannelloLibro);
    libroLayout->setFormAlignment(Qt::AlignCenter);
    libroLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);


    QLineEdit* titoloLibro = new QLineEdit();
    QSpinBox* annoLibro = new QSpinBox(); annoLibro->setRange(0, 2200);
    QDoubleSpinBox* prezzoLibro = new QDoubleSpinBox(); prezzoLibro->setRange(1, 1000); prezzoLibro->setDecimals(2);
    QSpinBox* copieLibro = new QSpinBox(); copieLibro->setRange(1, 100);
    QLineEdit* imgPathLibro = new QLineEdit();
    QPushButton* browseLibro = new QPushButton("Sfoglia...");
    QHBoxLayout* pathLayoutLibro = new QHBoxLayout(); pathLayoutLibro->addWidget(imgPathLibro); pathLayoutLibro->addWidget(browseLibro);
    QLineEdit* autoreLibro = new QLineEdit();
    QLineEdit* casaEditriceLibro = new QLineEdit();
    QSpinBox* pagineLibro = new QSpinBox(); pagineLibro->setRange(1, 6000);
    QComboBox* genereLibro = new QComboBox(); genereLibro->addItems({"Fantascienza","Fantasy","Gotico","Autobiografia","Narrativa"});
    QLineEdit* linguaLibro = new QLineEdit();

    genereLibro->setView(new QListView(genereLibro));
    genereLibro->view()->setMouseTracking(true); 


    libroLayout->addRow("Titolo", titoloLibro);
    libroLayout->addRow("Anno", annoLibro);
    libroLayout->addRow("Prezzo", prezzoLibro);
    libroLayout->addRow("Copie", copieLibro);
    libroLayout->addRow("Copertina", pathLayoutLibro);
    libroLayout->addRow("Autore", autoreLibro);
    libroLayout->addRow("Casa editrice", casaEditriceLibro);
    libroLayout->addRow("Pagine", pagineLibro);
    libroLayout->addRow("Genere", genereLibro);
    libroLayout->addRow("Lingua originale", linguaLibro);
    
    QPushButton* confermaLibro = new QPushButton("Conferma");
    QPushButton* backLibro = new QPushButton("Indietro");
    confermaLibro->setStyleSheet(navButtonStyle);
    backLibro->setStyleSheet(navButtonStyle);
    confermaLibro->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    backLibro->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

   
    QHBoxLayout* btnLayoutLibro = new QHBoxLayout();
    btnLayoutLibro->addStretch();
    btnLayoutLibro->addWidget(confermaLibro);
    btnLayoutLibro->addWidget(backLibro);
    btnLayoutLibro->addStretch();

    mainLayoutLibro->addStretch();
    mainLayoutLibro->addLayout(libroLayout);
    mainLayoutLibro->addStretch();
    mainLayoutLibro->addLayout(btnLayoutLibro);

    stack->addWidget(pannelloLibro);

    connect(browseLibro, &QPushButton::clicked, this, [=](){
        QString file = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), "Immagini (*.png *.jpg)");
        if (!file.isEmpty()) imgPathLibro->setText(file);
    });

    connect(backLibro, &QPushButton::clicked, this, [=](){stack->setCurrentWidget(pannelloScelta);});

    connect(confermaLibro, &QPushButton::clicked, this, [=](){
        
        if(!titoloLibro->text().isEmpty()){
            Libro::Genere g = static_cast<Libro::Genere>(genereLibro->currentIndex());

            Libro* l = new Libro(
                biblioteca->usaIndice(),
                titoloLibro->text().toStdString(),
                annoLibro->value(),
                prezzoLibro->value(),
                (imgPathLibro->text().isEmpty())? ":/icon/logo_full.png" :imgPathLibro->text() .toStdString(),
                autoreLibro->text().toStdString(),
                casaEditriceLibro->text().toStdString(),
                pagineLibro->value(),
                g,
                linguaLibro->text().toStdString(),
                copieLibro->value(),
                copieLibro->value()
            );

            biblioteca->addRisorsa(l);
            QMessageBox::information(this, "Info", "Risorsa creata con successo");

            //Reset
            titoloLibro->clear();
            annoLibro->setValue(0);
            prezzoLibro->setValue(1);
            copieLibro->setValue(1);
            imgPathLibro->clear();
            autoreLibro->clear();
            casaEditriceLibro->clear();
            pagineLibro->setValue(1);
            genereLibro->setCurrentIndex(0);
            linguaLibro->clear();

            stack->setCurrentWidget(pannelloScelta);
        }
    });

//PANNELLO RIVISTA
    pannelloRivista = new QWidget();
    pannelloRivista->setStyleSheet(panelStyle);
    QVBoxLayout* mainLayoutRivista = new QVBoxLayout(pannelloRivista);

    QFormLayout* rivistaLayout = new QFormLayout(pannelloRivista);
    rivistaLayout->setFormAlignment(Qt::AlignCenter);
    rivistaLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLineEdit* titoloRivista = new QLineEdit();
    QSpinBox* annoRivista = new QSpinBox(); annoRivista->setRange(0, 2200);
    QDoubleSpinBox* prezzoRivista = new QDoubleSpinBox(); prezzoRivista->setRange(1, 1000); prezzoRivista->setDecimals(2);
    QSpinBox* copieRivista = new QSpinBox(); copieRivista->setRange(1, 100);
    QLineEdit* imgPathRivista = new QLineEdit();
    QPushButton* browseRivista = new QPushButton("Sfoglia...");
    QHBoxLayout* pathRivista = new QHBoxLayout(); pathRivista->addWidget(imgPathRivista); pathRivista->addWidget(browseRivista);
    QLineEdit* autoreRivista = new QLineEdit();
    QLineEdit* casaEditriceRivista = new QLineEdit();
    QSpinBox* pagineRivista = new QSpinBox(); pagineRivista->setRange(1, 6000);
    QComboBox* periodicita = new QComboBox(); periodicita->addItems({"Settimanale", "Mensile", "Bimestrale"});
    QComboBox* argomento = new QComboBox(); argomento->addItems({"Attualita", "Cronaca", "Scienze", "Enigmistica"});

    periodicita->setView(new QListView(periodicita));
    periodicita->view()->setMouseTracking(true); 

    argomento->setView(new QListView(argomento));
    argomento->view()->setMouseTracking(true); 
    
    rivistaLayout->addRow("Titolo", titoloRivista);
    rivistaLayout->addRow("Anno", annoRivista);
    rivistaLayout->addRow("Prezzo", prezzoRivista);
    rivistaLayout->addRow("Copie", copieRivista);
    rivistaLayout->addRow("Copertina", pathRivista);
    rivistaLayout->addRow("Autore", autoreRivista);
    rivistaLayout->addRow("Casa editrice", casaEditriceRivista);
    rivistaLayout->addRow("Pagine", pagineRivista);
    rivistaLayout->addRow("Periodicità", periodicita);
    rivistaLayout->addRow("Argomento", argomento);

    QPushButton* confermaRivista = new QPushButton("Conferma");
    QPushButton* backRivista = new QPushButton("Indietro");
    confermaRivista->setStyleSheet(navButtonStyle);
    backRivista->setStyleSheet(navButtonStyle);
    confermaRivista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    backRivista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
 
    QHBoxLayout* btnLayoutRivista = new QHBoxLayout();
    btnLayoutRivista->addStretch();
    btnLayoutRivista->addWidget(confermaRivista);
    btnLayoutRivista->addWidget(backRivista);
    btnLayoutRivista->addStretch();

    mainLayoutRivista->addStretch();
    mainLayoutRivista->addLayout(rivistaLayout);
    mainLayoutRivista->addStretch();
    mainLayoutRivista->addLayout(btnLayoutRivista);

    stack->addWidget(pannelloRivista);

    connect(browseRivista, &QPushButton::clicked, this, [=](){
        QString file = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), "Immagini (*.png *.jpg)");
        if (!file.isEmpty()) imgPathRivista->setText(file);
    });

    connect(backRivista, &QPushButton::clicked, this, [=](){stack->setCurrentWidget(pannelloScelta);});

    connect(confermaRivista, &QPushButton::clicked, this, [=](){
        
        if(!titoloRivista->text().isEmpty()){
            Rivista::Periodicita p = static_cast<Rivista::Periodicita>(periodicita->currentIndex());
            Rivista::Argomento a = static_cast<Rivista::Argomento>(argomento->currentIndex());

            Rivista* r = new Rivista(
                biblioteca->usaIndice(),
                titoloRivista->text().toStdString(),
                annoRivista->value(),
                prezzoRivista->value(),
                (imgPathRivista->text().isEmpty())? ":/icon/logo_full.png" :imgPathRivista->text() .toStdString(),
                autoreRivista->text().toStdString(),
                casaEditriceRivista->text().toStdString(),
                pagineRivista->value(),
                p,
                a,
                copieRivista->value(),
                copieRivista->value()
            );

            biblioteca->addRisorsa(r);
            QMessageBox::information(this, "Info", "Risorsa creata con successo");

            titoloRivista->clear();
            annoRivista->setValue(0);
            prezzoRivista->setValue(1);
            copieRivista->setValue(1);
            imgPathRivista->clear();
            autoreRivista->clear();
            casaEditriceRivista->clear();
            pagineRivista->setValue(1);
            periodicita->setCurrentIndex(0);
            argomento->setCurrentIndex(0);

            stack->setCurrentWidget(pannelloScelta);
        }
    });

//PANNELLO DVD
    pannelloDvd = new QWidget();
    pannelloDvd->setStyleSheet(panelStyle);
    QVBoxLayout* mainLayoutDvd = new QVBoxLayout(pannelloDvd);


    QFormLayout* dvdLayout = new QFormLayout(pannelloDvd);
    dvdLayout->setFormAlignment(Qt::AlignCenter);
    dvdLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLineEdit* titoloDvd = new QLineEdit();
    QSpinBox* annoDvd = new QSpinBox(); annoDvd->setRange(0, 2200);
    QDoubleSpinBox* prezzoDvd = new QDoubleSpinBox(); prezzoDvd->setRange(1, 1000); prezzoDvd->setDecimals(2);
    QSpinBox* copieDvd = new QSpinBox(); copieDvd->setRange(1, 100);
    QLineEdit* imgPathDvd = new QLineEdit();
    QPushButton* browseDvd = new QPushButton("Sfoglia...");
    QHBoxLayout* pathDvd = new QHBoxLayout(); pathDvd->addWidget(imgPathDvd); pathDvd->addWidget(browseDvd);
    QLineEdit* regista = new QLineEdit();
    QSpinBox* durata = new QSpinBox(); durata->setRange(1, 1000);
    QComboBox* extra = new QComboBox(); extra->addItems({"Si", "No"});

    extra->setView(new QListView(extra));
    extra->view()->setMouseTracking(true); 

    dvdLayout->addRow("Titolo", titoloDvd);
    dvdLayout->addRow("Anno", annoDvd);
    dvdLayout->addRow("Prezzo", prezzoDvd);
    dvdLayout->addRow("Copie", copieDvd);
    dvdLayout->addRow("Copertina", pathDvd);
    dvdLayout->addRow("Regista", regista);
    dvdLayout->addRow("Durata", durata);
    dvdLayout->addRow("Contenuti extra", extra);

    QPushButton* confermaDvd = new QPushButton("Conferma");
    QPushButton* backDvd= new QPushButton("Indietro");
    confermaDvd->setStyleSheet(navButtonStyle);
    backDvd->setStyleSheet(navButtonStyle);
    confermaDvd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    backDvd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
 
    QHBoxLayout* btnLayoutDvd = new QHBoxLayout();
    btnLayoutDvd->addStretch();
    btnLayoutDvd->addWidget(confermaDvd);
    btnLayoutDvd->addWidget(backDvd);
    btnLayoutDvd->addStretch();

    mainLayoutDvd->addStretch();
    mainLayoutDvd->addLayout(dvdLayout);
    mainLayoutDvd->addStretch();
    mainLayoutDvd->addLayout(btnLayoutDvd);

    stack->addWidget(pannelloDvd);

    connect(browseDvd, &QPushButton::clicked, this, [=](){
        QString file = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", QDir::homePath(), "Immagini (*.png *.jpg)");
        if (!file.isEmpty()) imgPathDvd->setText(file);
    });

    connect(backDvd, &QPushButton::clicked, this, [=](){stack->setCurrentWidget(pannelloScelta);});

    connect(confermaDvd, &QPushButton::clicked, this, [=](){
        
        if(!titoloDvd->text().isEmpty()){
            bool cbExtra = (extra->currentText() == "Si");
            Dvd* d = new Dvd(
                biblioteca->usaIndice(),
                titoloDvd->text().toStdString(),
                annoDvd->value(),
                prezzoDvd->value(),
                (imgPathDvd->text().isEmpty())? ":/icon/logo_full.png" :imgPathDvd->text() .toStdString(),
                durata->value(),
                regista->text().toStdString(),
                cbExtra,
                copieDvd->value(),
                copieDvd->value()
            );
            biblioteca->addRisorsa(d);
            QMessageBox::information(this, "Info", "Risorsa creata con successo");

            titoloDvd->clear();
            annoDvd->setValue(0);
            prezzoDvd->setValue(1);
            copieDvd->setValue(1);
            imgPathDvd->clear();
            regista->clear();
            durata->setValue(1);
            extra->setCurrentIndex(0);

            stack->setCurrentWidget(pannelloScelta);
        }
    });

//PANNELLO VINILE
    pannelloVinile = new QWidget();
    pannelloVinile->setStyleSheet(panelStyle);
    QVBoxLayout* mainLayoutVinile = new QVBoxLayout(pannelloVinile);

    QFormLayout* vinileLayout = new QFormLayout(pannelloVinile);
    vinileLayout->setFormAlignment(Qt::AlignCenter);
    vinileLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLineEdit* titoloVinile = new QLineEdit();
    QSpinBox* annoVinile = new QSpinBox(); annoVinile->setRange(0, 2200);
    QDoubleSpinBox* prezzoVinile = new QDoubleSpinBox(); prezzoVinile->setRange(1, 1000); prezzoVinile->setDecimals(2);
    QSpinBox* copieVinile = new QSpinBox(); copieVinile->setRange(1, 100);
    QLineEdit* imgPathVinile = new QLineEdit();
    QPushButton* browseVinile = new QPushButton("Sfoglia...");
    QHBoxLayout* pathVinile = new QHBoxLayout(); pathVinile->addWidget(imgPathVinile); pathVinile->addWidget(browseVinile);
    QLineEdit* autoreVinile = new QLineEdit();
    QLineEdit* casaDiscografica = new QLineEdit();
    QSpinBox* durataVinile = new QSpinBox(); durataVinile->setRange(1, 1000);
    QSpinBox* tracce = new QSpinBox(); tracce->setRange(1, 40);
    
    vinileLayout->addRow("Titolo", titoloVinile);
    vinileLayout->addRow("Anno", annoVinile);
    vinileLayout->addRow("Prezzo", prezzoVinile);
    vinileLayout->addRow("Copie", copieVinile);
    vinileLayout->addRow("Copertina", pathVinile);
    vinileLayout->addRow("Autore", autoreVinile);
    vinileLayout->addRow("Casa discografica", casaDiscografica);
    vinileLayout->addRow("Durata", durataVinile);
    vinileLayout->addRow("Numero di tracce", tracce);

    QPushButton* confermaVinile = new QPushButton("Conferma");
    QPushButton* backVinile = new QPushButton("Indietro");
    confermaVinile->setStyleSheet(navButtonStyle);
    backVinile->setStyleSheet(navButtonStyle);
    confermaVinile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    backVinile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* btnLayoutVinile = new QHBoxLayout();
    btnLayoutVinile->addStretch();
    btnLayoutVinile->addWidget(confermaVinile);
    btnLayoutVinile->addWidget(backVinile);
    btnLayoutVinile->addStretch();

    mainLayoutVinile->addStretch();
    mainLayoutVinile->addLayout(vinileLayout);
    mainLayoutVinile->addStretch();
    mainLayoutVinile->addLayout(btnLayoutVinile);

    stack->addWidget(pannelloVinile);

    connect(browseVinile, &QPushButton::clicked, this, [=](){
        QString file = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", QDir::homePath(), "Immagini (*.png *.jpg)");
        if (!file.isEmpty()) imgPathVinile->setText(file);
    });

    connect(backVinile, &QPushButton::clicked, this, [=](){stack->setCurrentWidget(pannelloScelta);});

    connect(confermaVinile, &QPushButton::clicked, this, [=](){
        
        if(!titoloVinile->text().isEmpty()){
            Vinile* v = new Vinile(
                biblioteca->usaIndice(),
                titoloVinile->text().toStdString(),
                annoVinile->value(),
                prezzoVinile->value(),
                (imgPathVinile->text().isEmpty())? ":/icon/logo_full.png" :imgPathVinile->text() .toStdString(),
                durataVinile->value(),
                autoreVinile->text().toStdString(),
                casaDiscografica->text().toStdString(),
                tracce->value(),
                copieVinile->value(),
                copieVinile->value()
            );
            biblioteca->addRisorsa(v);
            QMessageBox::information(this, "Info", "Risorsa creata con successo");

            titoloVinile->clear();
            annoVinile->setValue(0);
            prezzoVinile->setValue(1);
            copieVinile->setValue(1);
            imgPathVinile->clear();
            autoreVinile->clear();
            casaDiscografica->clear();
            durataVinile->setValue(1);
            tracce->setValue(1);

            stack->setCurrentWidget(pannelloScelta);
        }
    });

    //Conessioni del pannello iniziale di scelta 
    connect(btnLibro, &QPushButton::clicked, this, [=](){ stack->setCurrentWidget(pannelloLibro); });
    connect(btnRivista, &QPushButton::clicked, this, [=](){ stack->setCurrentWidget(pannelloRivista); });
    connect(btnDvd, &QPushButton::clicked, this, [=](){ stack->setCurrentWidget(pannelloDvd); });
    connect(btnVinile, &QPushButton::clicked, this, [=](){ stack->setCurrentWidget(pannelloVinile); });

    stack->setCurrentWidget(pannelloScelta);
}
