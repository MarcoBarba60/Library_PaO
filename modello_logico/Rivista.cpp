#include "Rivista.h"
using std::string;

//costruttore
Rivista::Rivista(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, Periodicita periodicita, Argomento argomento, int copie_biblioteca, int disponibili)
    : Cartacea(id, titolo, anno_pubblicazione, prezzo, path, autore, casa_editrice, n_pagine, copie_biblioteca, disponibili), periodicita(periodicita), argomento(argomento) {}

//setter
string Rivista::getPeriodicitaToString() const{
    switch (periodicita)
    {
    case Settimanale:
        return "Settimanale";
        break;
    case Mensile:
        return "Mensile";
        break;
    case Bimestrale:
        return "Bimestrale";
        break;
    
    default:
        return "Non definito";
        break;
    }

}
string Rivista::getArgomentoToString() const{
    switch (argomento)
    {
    case Attualita:
        return "Attualita";
        break;
    case Scienze:
        return "Scienze";
        break;
    case Cronaca:
        return "Cronaca";
        break;
    case Enigmistica:
        return "Enigmistica";
        break;
    
    default:
        return "Non definito";
        break;
    }

}

//setter
void Rivista::setPeriodicita(const Periodicita& periodicita_nuova){
    periodicita = periodicita_nuova;
}
void Rivista::setArgomento(const Argomento& argomento_nuovo){
    argomento = argomento_nuovo;
}

//altri metodi 
void Rivista::accept(Visitor * visitor){
    visitor->visit(this);
}

Risorsa* Rivista::clone() const{
    return new Rivista(*this);
}
