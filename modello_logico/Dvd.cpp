#include "Dvd.h"
using std::string;

//costruttore
Dvd::Dvd(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata, string regista, bool contenuti_bonus , int copie_biblioteca, int disponibili)
    :Multimedia(id, titolo, anno_pubblicazione, prezzo, path, durata, copie_biblioteca, disponibili), regista(regista), contenuti_bonus(contenuti_bonus){}


//Getter
string Dvd::getRegista() const{return regista;}
bool Dvd::getContenutiBonus() const{return contenuti_bonus;}

//setter
void Dvd::setRegista(const string& regista_nuovo){regista = regista_nuovo;}
void Dvd::setContenutiBonus(const bool& contenuti_nuovo){contenuti_bonus = contenuti_nuovo;}

//altri metodi
void Dvd::accept(Visitor* visitor){
    visitor->visit(this);
}

Risorsa* Dvd::clone() const{
    return new Dvd(*this);
}