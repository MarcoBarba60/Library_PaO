#ifndef VINILE_H
#define VINILE_H
#include "Multimedia.h"
using std::string;

class Vinile : public Multimedia{
    private:
        string autore;
        string casa_discografica;
        unsigned int n_tracce;
    
    public:
        Vinile(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata, string autore, string casa_discografica, unsigned int n_tracce , int copie_biblioteca = 1, int disponibili = 0);
        virtual ~Vinile() = default;

        //getter
        string getAutore() const;
        string getCasaDiscografica() const;
        unsigned int getNTracce() const;

        //setter
        void setAutore(const string& autore_nuovo);
        void setCasaDiscografica(const string& casa_discografica_nuovo);
        void setNTracce(const unsigned int& n_tracce_nuovo); 

        //altri metodi 
        virtual void accept(Visitor* visitor) override;
        virtual Risorsa* clone() const override;

}; //Vinile

#endif //VINILE_H