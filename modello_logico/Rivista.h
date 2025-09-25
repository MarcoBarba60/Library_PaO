#ifndef RIVISTA_H
#define RIVISTA_H
#include "Cartacea.h"
using std::string;

class Rivista : public Cartacea{
    public:
        enum Periodicita{Settimanale, Mensile, Bimestrale};
        enum Argomento{Attualita, Cronaca, Scienze, Enigmistica};
        
        Rivista(int id, string titolo, int anno_pubblicazione, double prezzo, string path, string autore, string casa_editrice, unsigned int n_pagine, Periodicita periodicita, Argomento argomento , int copie_biblioteca = 1, int disponibili = 0);
        virtual ~Rivista() = default;

        //setter
        string getPeriodicitaToString() const;
        string getArgomentoToString() const;

        //setter
        void setPeriodicita(const Periodicita& periodicita_nuova);
        void setArgomento(const Argomento& argomento_nuovo);

        //altri metodi 
        void accept(Visitor * visitor) override;
        virtual Risorsa* clone() const override;

    private:
        Periodicita periodicita;
        Argomento argomento;

}; //Rivista

#endif //RIVISTA_H