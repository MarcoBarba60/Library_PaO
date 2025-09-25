#ifndef DVD_H
#define DVD_H
#include "Multimedia.h"
using std::string;

class Dvd : public Multimedia{
    private:
        string regista;
        bool contenuti_bonus;
    
    public:
        Dvd(int id, string titolo, int anno_pubblicazione, double prezzo, string path, unsigned int durata, string regista, bool contenuti_bonus , int copie_biblioteca = 1, int disponibili = 0);
        virtual ~Dvd() = default;

        //Getter
        string getRegista() const;
        bool getContenutiBonus() const;

        //setter
        void setRegista(const string& regista_nuovo);
        void setContenutiBonus(const bool& contenuti_nuovo);

        //altri metodi
        virtual void accept(Visitor* visitor) override;
        virtual Risorsa* clone() const override;
}; //Dvd

#endif //DVD_H