#include "Risorsa.h"
using std::string;

//costruttore --> NB vincoli su copie e prestiti gestiti direttamente dall'interfaccia grafica che impedisce direttamente l'inserimento di dati errati
Risorsa::Risorsa(int id, string titolo, int anno_pubblicazione, double prezzo, string path, int copie_biblioteca, int disponibili) 
    : id(id), titolo(titolo), anno_pubblicazione(anno_pubblicazione), prezzo(prezzo), path_img(path), copie_biblioteca(copie_biblioteca), disponibili(disponibili) {};


//getter
int Risorsa::getId() const{return id;}
string Risorsa::getTitolo() const{return titolo;}
int Risorsa::getAnnoPubblicazione() const{return anno_pubblicazione;}
double Risorsa::getPrezzo() const{return prezzo;}
string Risorsa::getImgPath() const{return path_img;}
int Risorsa::getCopieBiblioteca() const{return copie_biblioteca;}
int Risorsa::getDisponibili() const{return disponibili;}

//setter
void Risorsa::setId(const int& id_nuovo){id = id_nuovo;}
void Risorsa::setTitolo(const string& titolo_nuovo){titolo = titolo_nuovo;}
void Risorsa::setAnnoPubblicazione(const int& anno_nuovo){anno_pubblicazione = anno_nuovo;}
void Risorsa::setPrezzo(const double& prezzo_nuovo){prezzo = prezzo_nuovo;}
void Risorsa::setImgPath(const string& percorso_nuovo){path_img = percorso_nuovo;}
void Risorsa::setCopieBiblioteca(const int& n_copie_nuovo){copie_biblioteca = n_copie_nuovo;}
void Risorsa::setDisponibili(const int& n_disponibili){disponibili = n_disponibili;}

//altri metodi
bool Risorsa::prestito(){
    if(disponibili!=0){
        disponibili --;
        return true;
    }
    return false;
}

bool Risorsa::restituzione(){
    if(disponibili +1 <= copie_biblioteca){
        disponibili ++;
        return true;
    }
    return false;
}


