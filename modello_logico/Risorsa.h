#ifndef RISORSA_H
#define RISORSA_H
#include "../Visitor.h"
#include <string>
using std::string;

class Risorsa{
    private:
        int id;
        string titolo;
        int anno_pubblicazione;
        double prezzo;
        string path_img;
        int copie_biblioteca; //# di copie che appartengono alla bilbioteca
        int disponibili; //# di copie che sono state prese in prestito

    public:
        //Costruttore e distruttore
        Risorsa(int id, string titolo, int anno_pubblicazione, double prezzo, string path, int copie_biblioteca = 1, int disponibili = 0);
        Risorsa() = default;
        virtual ~Risorsa() = default;

        //Getter
        int getId() const;
        string getTitolo() const;
        int getAnnoPubblicazione() const;
        double getPrezzo() const;
        string getImgPath() const;
        int getCopieBiblioteca() const;
        int getDisponibili() const;

        //Setter
        void setId(const int& id_nuovo);
        void setTitolo(const string& titolo_nuovo);
        void setAnnoPubblicazione(const int& anno_nuovo);
        void setPrezzo(const double& prezzo_nuovo);
        void setImgPath(const string& percorso_nuovo);
        void setCopieBiblioteca(const int& n_copie_nuovo);
        void setDisponibili(const int& n_disponibili);

        //Altri metodi
        bool prestito();
        bool restituzione();
        virtual void accept(Visitor * visitor) = 0;
        virtual Risorsa* clone() const =0;

}; //Risorsa

#endif //RISORSA_H