#include <QApplication>
#include "interfaccia_grafica/MainWindow.h"
#include "Biblioteca.h"

//main method
int main(int argc, char*argv[]){
    //Setup modello logico e grafico
    QApplication app(argc, argv);
    Biblioteca biblioteca;
    MainWindow window(&biblioteca);

    QPixmap pixmap(":/icon/logo_full.png");
    if(!pixmap.isNull()) {
        QIcon icon(pixmap);
        app.setWindowIcon(icon);
    }

    
    window.setWindowTitle("Biblioteca");
    window.resize(1200, 650);
    window.setMaximumWidth(1200);
    window.setMaximumHeight(650);
    window.show();

    //Applicazione in esecuzione
    app.exec();
}




