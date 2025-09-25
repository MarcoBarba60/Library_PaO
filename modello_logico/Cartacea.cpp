#include "Cartacea.h"
using std::string;

//Costruttore
Cartacea::Cartacea(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, int copie_biblioteca, int disponibili)
    : Risorsa(id, titolo, anno_pubblicazione, prezzo, path, copie_biblioteca, disponibili), autore(autore), casa_editrice(casa_editrice), n_pagine(n_pagine){};

//getter
string Cartacea::getAutore() const{return autore;}
string Cartacea::getCasaEditrice() const{return casa_editrice;}
unsigned int Cartacea::getNPagine() const{return n_pagine;}

//setter
void Cartacea::setAutore(const string& autore_nuovo){autore = autore_nuovo;}
void Cartacea::setCasaEditrice(const string& casa_editrice_nuova){casa_editrice = casa_editrice_nuova;}
void Cartacea::setNPagine(const unsigned int& nPagine_nuovo){n_pagine = nPagine_nuovo;}