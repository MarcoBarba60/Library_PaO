//Mi scuso per i commenti "Evidenti", mi servivano per maggiore ordine visivo
#include "MainWindow.h"

MainWindow::MainWindow(Biblioteca* bib, QWidget* parent) : QMainWindow(parent), biblioteca(bib){
    
    //Widget principale
    QWidget* centrale = new QWidget(this);
    QVBoxLayout* layoutPrincipale = new QVBoxLayout(centrale);
    layoutPrincipale->setContentsMargins(10, 10, 10, 10);

    setStyleSheet("QMainWindow { background-color: #FBF7EE; }");

    ///////////////////////////////////////INPUT INIZIALE ////////////////////////////////

    QMessageBox::StandardButton primoImport = QMessageBox::question(this, "Caricamento libreria multimediale", "Vuoi importare l'elenco delle risorse multimediali da un file JSON?", QMessageBox::Yes | QMessageBox::No);
    if(primoImport == QMessageBox::Yes){
        QString path = QFileDialog::getOpenFileName(
                this,
                "Seleziona il file JSON",
                QStandardPaths::writableLocation(QStandardPaths::AppDataLocation),
                "JSON files(*.json);;All files (*.*)"
            );

        if(!path.isEmpty()) {
            if(biblioteca->load(path)) {
                QMessageBox::information(this, "Importazione avvenuta con successo!", "Tutti i media sono stati importati correttamente");
            }
            else QMessageBox::warning(this, "Errore", "Impossibile importare i media dal file"); 
        }
    }

    ///////////////////BARRA DI NAVIGAZIONE ////////////////////////////////////////////

    //Barra 
    QWidget* barra = new QWidget(this);
    QHBoxLayout* layoutBarra = new QHBoxLayout(barra);
    layoutBarra->setContentsMargins(10, 5, 10, 5);
    layoutBarra->setSpacing(10);

    //Logo
    QLabel* logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/icon/logo.png").scaledToHeight(80, Qt::SmoothTransformation));
    layoutBarra->addWidget(logo);

    //Pulsanti 
    QPushButton* catalogo = new QPushButton("Catalogo");
    QPushButton* ricerca = new QPushButton("Ricerca");
    QPushButton* aggiungi = new QPushButton("Aggiungi risorsa");
    QPushButton* salva = new QPushButton("Salva su Json");
    QPushButton* importa = new QPushButton("Importa da Json");

    QString btnStyle = R"(
        QPushButton {
        font-size: 15px;   
        height: 45px;       
        background-color: white;
        border: 2px solid #333333;
        border-radius: 10px;
        }
        QPushButton:hover {
        color: white;
        background-color: #48727A; 
    })";

    catalogo->setStyleSheet(btnStyle);
    ricerca->setStyleSheet(btnStyle);
    aggiungi->setStyleSheet(btnStyle);
    salva->setStyleSheet(btnStyle);
    importa->setStyleSheet(btnStyle);


    layoutBarra->addWidget(catalogo);
    layoutBarra->addWidget(ricerca);
    layoutBarra->addWidget(aggiungi);
    layoutBarra->addWidget(salva);
    layoutBarra->addWidget(importa);

    layoutPrincipale->addWidget(barra);


    ///////////////COSTRUZIONE DEI WIDGETS GRAFICI DELLE VARIE SCHERMATE ////////////////

    stackedWidget = new QStackedWidget(this);
    Catalogo* widCatalogo = new Catalogo(biblioteca);
    Ricerca* widRicerca = new Ricerca(biblioteca);
    Aggiungi* widAggiungi = new Aggiungi(biblioteca);

    stackedWidget->addWidget(widCatalogo);
    stackedWidget->addWidget(widRicerca);
    stackedWidget->addWidget(widAggiungi);


    layoutPrincipale->addWidget(stackedWidget);

    setCentralWidget(centrale);

    //COLLEGAMENTO PULSANTI A "PAGINE"
    connect(catalogo, &QPushButton::clicked, this, [this](){selezionaPagina(0);});
    connect(ricerca, &QPushButton::clicked, this, [this](){selezionaPagina(1);});
    connect(aggiungi, &QPushButton::clicked, this, [this](){selezionaPagina(2);});
    connect(salva, &QPushButton::clicked, this, [this](){outputJson();});
    connect(importa, &QPushButton::clicked, this, [this](){inputJson();});

    //pagina iniziale
    selezionaPagina(0);

    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(inputJson()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(outputJson()));
}



//SLOTS

void MainWindow::selezionaPagina(int index){
    stackedWidget->setCurrentIndex(index);
}

void MainWindow::inputJson(){

    QString path = QFileDialog::getOpenFileName(
                this,
                "Seleziona il file JSON",
                QStandardPaths::writableLocation(QStandardPaths::AppDataLocation),
                "JSON files(*.json);;All files (*.*)"
            );

    if(path.isEmpty()) {
        return;   
    }

    QMessageBox::StandardButton verificaDecisione = QMessageBox::question(this, "Conferma apertura", "All'apertura del file, la lista di risorse precedente verrà sovrascritta. Continuare?", QMessageBox::Yes | QMessageBox::No);
    if(verificaDecisione == QMessageBox::Yes){
        //Richiamo l'import nella classe logica della biblioteca
        if(biblioteca->load(path)) {
            QMessageBox::information(this, "Importazione avvenuta con successo!", "Tutti i media sono stati importati correttamente");
            selezionaPagina(0);
        }
        else QMessageBox::warning(this, "Errore", "Impossibile importare i media dal file");
    }
    
}

void MainWindow::outputJson(){

    QString path = QFileDialog::getSaveFileName(
                this,
                "Salva la raccolta",
                QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "libreria.json",
                "JSON files(*.json);;All files (*.*)"
            );

    if(path.isEmpty()) {
        return;   
    }

    //Richiamo l'export 
    if(biblioteca->save(path))
        QMessageBox::information(this, "Esportazione avvenuta con successo!", "Tutti i media sono stati esportati correttamente");
    else
        QMessageBox::warning(this, "Errore", "Impossibile esportare i media sul file");


}

