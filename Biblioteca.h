#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "json/JsonUtilities.h"
#include "modello_logico/FiltroVisitor.h"
#include <QObject>

//Classe di connessione tra JSON Utilities, interfaccia grafica e modello logico
class Biblioteca : public QObject{
    Q_OBJECT
    private:
        QList<Risorsa*> list;
        int indice;
    public:
        Biblioteca(QObject* parent = nullptr);
        ~Biblioteca() override;
        QList<Risorsa*> getList() const;
        void addRisorsa(Risorsa* ris);
        bool deleteRisorsa(Risorsa* ris);
        bool load(QString path);
        bool save(QString path) const;
        int usaIndice();
        QList<Risorsa*> search(const QString& txt, const QString& typ, int aMin, int aMax, bool disp)const;
        void sortByTitle();
    signals:
        void listaAggiornata();

}; //Biblioteca


#endif //BIBLIOTECA_H