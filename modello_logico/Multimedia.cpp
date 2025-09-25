#include "Multimedia.h"
using std::string;

Multimedia::Multimedia(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata, int copie_biblioteca, int disponibili)
    : Risorsa(id, titolo, anno_pubblicazione, prezzo, path, copie_biblioteca, disponibili), durata(durata){};

//getter
unsigned int Multimedia::getDurata() const{return durata;}

//setter
void Multimedia::setDurata(const unsigned int& durata_nuova){durata = durata_nuova;}