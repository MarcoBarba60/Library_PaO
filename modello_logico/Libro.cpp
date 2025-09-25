#include "Libro.h"
using std::string;

//Costruttore
Libro::Libro(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, Genere genere, string lingua_originale, int copie_biblioteca, int disponibili)
    : Cartacea(id, titolo, anno_pubblicazione, prezzo, path, autore, casa_editrice, n_pagine, copie_biblioteca, disponibili), genere(genere), lingua_originale(lingua_originale) {}

//Getter
string Libro::getGenereToString() const{
    switch (genere)
    {
    case Fantascienza:
        return "Fantascienza";
        break;
    case Fantasy:
        return "Fantasy";
        break;
    case Gotico:
        return "Gotico";
        break;
    case Autobiografia:
        return "Autobiografia";
        break;
    case Narrativa:
        return "Narrativa";
        break;
    default:
        return "Non definito";
        break;
    }
}
string Libro::getLinguaOriginale() const{ return lingua_originale;}

//Setter
void Libro::setGenere(const Genere& genere_nuovo){genere = genere_nuovo;}
void Libro::setLinguaOriginale(const string& lingua_oroginale_nuova){lingua_originale = lingua_oroginale_nuova;}

//Altri metodi;
void Libro::accept(Visitor * visitor){
    visitor->visit(this);
}

Risorsa* Libro::clone() const{
    return new Libro(*this);
}