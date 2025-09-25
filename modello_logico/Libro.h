#ifndef LIBRO_H
#define LIBRO_H
#include "Cartacea.h"
using std::string;

class Libro : public Cartacea{
    public:
        enum Genere{Fantascienza, Fantasy, Gotico, Autobiografia, Narrativa};

        Libro(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, Genere genere, string lingua_originale, int copie_biblioteca, int disponibili );
        virtual ~Libro() = default;

        //getter
        string getGenereToString() const;
        string getLinguaOriginale() const;

        //setter
        void setGenere(const Genere& genere_nuovo);
        void setLinguaOriginale(const string& lingua_oroginale_nuova);

        //altri metodi
        void accept(Visitor * visitor) override;
        virtual Risorsa* clone() const override;

    private:
        Genere genere;
        string lingua_originale;

}; //Libro

#endif //LIBRO_H