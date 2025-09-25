#include "Vinile.h"
using std::string;

//costruttore
Vinile::Vinile(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata, string autore, string casa_discografica, unsigned int n_tracce, int copie_biblioteca, int disponibili)
    :Multimedia(id,titolo, anno_pubblicazione, prezzo, path, durata ,copie_biblioteca, disponibili), autore(autore), casa_discografica(casa_discografica), n_tracce(n_tracce) {}


//getter
string Vinile::getCasaDiscografica() const{return casa_discografica;}
string Vinile::getAutore() const{return autore;}
unsigned int Vinile::getNTracce() const{return n_tracce;}

//setter
void Vinile::setAutore(const string& autore_nuovo){autore = autore_nuovo;}
void Vinile::setCasaDiscografica(const string& casa_discografica_nuovo){casa_discografica = casa_discografica_nuovo;}
void Vinile::setNTracce(const unsigned int& n_tracce_nuovo){n_tracce = n_tracce_nuovo;} 

//altri metodi 
void Vinile::accept(Visitor* visitor){
    visitor->visit(this);
}

Risorsa* Vinile::clone() const{
    return new Vinile(*this);
}