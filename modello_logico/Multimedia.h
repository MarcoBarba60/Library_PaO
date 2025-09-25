#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H
#include "Risorsa.h"
using std::string;

class Multimedia : public Risorsa{
    private:
        unsigned int durata; //durata espressa in minuti

    public: 
        Multimedia(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata , int copie_biblioteca = 1, int disponibili = 0);
        virtual ~Multimedia() = default;

        //getter
        unsigned int getDurata() const;

        //setter
        void setDurata(const unsigned int& durata_nuova);

        //altri metodi
        virtual void accept(Visitor* visitor) override = 0;
        virtual Risorsa* clone() const override =0;

}; //Multimedia

#endif //MULTIMEDIA_H