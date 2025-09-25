#include "JsonUtilities.h"
#include "JsonVisitor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

//Crea un oggetto a partie da json
Risorsa* JsonUtilities::jsonToObj(const QJsonObject& obj){
	
	int id = obj["id"].toInt();
    QString classe = obj["classe"].toString();
    QString titolo = obj["titolo"].toString();
    int anno_pubblicazione = obj["anno_pubblicazione"].toInt();
    double prezzo = obj["prezzo"].toDouble();
    QString path_img = obj["path_img"].toString();
    int copie_biblioteca = obj["copie_biblioteca"].toInt();
    int disponibili = obj["disponibili"].toInt();

    if(classe == "Libro"){
        QString autore = obj["autore"].toString();
        QString casa_editrice = obj["casa_editrice"].toString();
        unsigned int n_pagine = (unsigned int) obj["n_pagine"].toInt();
        QString genere = obj["genere"].toString();
        QString lingua_originale = obj["lingua_originale"].toString();

        return new Libro(id, titolo.toStdString(), anno_pubblicazione, prezzo, path_img.toStdString(), autore.toStdString(), casa_editrice.toStdString(), n_pagine, JsonUtilities::stringToGenere(genere), lingua_originale.toStdString(), copie_biblioteca, disponibili);
    }
    else if(classe == "Rivista"){
        QString autore = obj["autore"].toString();
        QString casa_editrice = obj["casa_editrice"].toString();
        unsigned int n_pagine = (unsigned int) obj["n_pagine"].toInt();
        QString periodicita = obj["periodicita"].toString();
        QString argomento = obj["argomento"].toString();

        return new Rivista(id, titolo.toStdString(), anno_pubblicazione, prezzo, path_img.toStdString(), autore.toStdString(), casa_editrice.toStdString(), n_pagine, JsonUtilities::stringToPeriodicita(periodicita), JsonUtilities::stringToArg(argomento), copie_biblioteca, disponibili);
    }
    else if(classe == "Dvd"){
        int durata = obj["durata"].toInt();
        QString regista = obj["regista"].toString();
        bool contenuti_aggiuntivi = obj["contenuti_aggiuntivi"].toBool();

        return new Dvd(id, titolo.toStdString(), anno_pubblicazione, prezzo, path_img.toStdString(), durata, regista.toStdString(), contenuti_aggiuntivi, copie_biblioteca, disponibili);

    }
    else if(classe == "Vinile"){
        int durata = obj["durata"].toInt();
        QString autore = obj["autore"].toString();
        QString casa_discografica = obj["casa_discografica"].toString();
        int n_tracce = obj["n_tracce"].toInt();

        return new Vinile(id, titolo.toStdString(), anno_pubblicazione, prezzo, path_img.toStdString(), durata, autore.toStdString(), casa_discografica.toStdString(), n_tracce, copie_biblioteca, disponibili);
    }
    else{
        return nullptr;
    }

}


//Carica l'intero file Json in una lista 
//Return lista vuota se non ha caricato nulla
QList<Risorsa*> JsonUtilities::loadAllFromJson(const QString& path){
    QList<Risorsa*> list;

    //Apertura del file
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) return list;
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if(!doc.isArray()) return list;

    //popolamento lista
    for (auto val : doc.array()){
        auto obj = val.toObject();
        auto risorsa = jsonToObj(obj);
        if(risorsa) list.append(risorsa);
    }

    return list;

}

//Salva l'intera lista nel file Json indicato da path
bool JsonUtilities::saveAllToJson (const QString& path, const QList<Risorsa*>& ris){
    QJsonArray array;
    for(auto& r : ris){
        JsonVisitor v;
        r->accept(&v);
        array.append(v.getJson());
    }

    QJsonDocument document(array);
    QFile f(path);
    if(!f.open(QIODevice::WriteOnly)) return false;
    f.write(document.toJson());
    return true;
}


//metodo privato
Libro::Genere JsonUtilities::stringToGenere(const QString& s){
    if(s == "Fantascienza") return Libro::Fantascienza;
    if(s == "Fantasy") return Libro::Fantasy;
    if(s == "Gotico") return Libro::Gotico;
    if(s == "Autobiografia") return Libro::Autobiografia;
    if(s == "Narrativa") return Libro::Narrativa;
    throw std::invalid_argument("Genere non valido: ");
}

Rivista::Periodicita JsonUtilities::stringToPeriodicita(const QString& s){
    if(s == "Settimanale") return Rivista::Settimanale;
    if(s == "Mensile") return Rivista::Mensile;
    if(s == "Bimestrale") return Rivista::Bimestrale;
    throw std::invalid_argument("Periodicita non valida: ");
}

Rivista::Argomento JsonUtilities::stringToArg(const QString& s){
    if(s == "Attualita") return Rivista::Attualita;
    if(s == "Cronaca") return Rivista::Cronaca;
    if(s == "Scienze") return Rivista::Scienze;
    if(s == "Enigmistica") return Rivista::Enigmistica;
    throw std::invalid_argument("Argomento non valido: ");
}