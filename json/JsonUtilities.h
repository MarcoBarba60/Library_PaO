#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H
#include "../modello_logico/Risorsa.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/Dvd.h"
#include "../modello_logico/Vinile.h"
#include <QJsonObject>
#include <QString>

//Classe di utilità per il dialogo Libreria-FileJSON
class JsonUtilities{

    public:
        static Risorsa* jsonToObj(const QJsonObject& obj);
        static QList<Risorsa*> loadAllFromJson(const QString& path);
        static bool saveAllToJson (const QString& path, const QList<Risorsa*>& ris);

    private:
        static Libro::Genere stringToGenere(const QString& s);
        static Rivista::Periodicita stringToPeriodicita(const QString& s);
        static Rivista::Argomento stringToArg(const QString& s);


}; //JsonUtilities


#endif //JSONUTILITIES_H