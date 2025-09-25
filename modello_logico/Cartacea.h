#ifndef CARTACEA_H
#define CARTACEA_H
#include "Risorsa.h"
using std::string;

class Cartacea : public Risorsa{
    private:
        string autore;
        string casa_editrice;
        unsigned int n_pagine;

    public:
        Cartacea(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, int copie_biblioteca = 1, int disponibili = 0);
        virtual ~Cartacea() = default;

        //getter
        string getAutore() const;
        string getCasaEditrice() const;
        unsigned int getNPagine() const;

        //setter
        void setAutore(const string& autore_nuovo);
        void setCasaEditrice(const string& casa_editrice_nuova);
        void setNPagine(const unsigned int& Pagine_nuovo);
        
        //altri metodi
        virtual void accept(Visitor* visitor) override = 0;
        virtual Risorsa* clone() const override =0;


};//Cartacea

#endif //CARTACEA_H