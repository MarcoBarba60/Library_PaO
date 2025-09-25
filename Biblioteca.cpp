#include "Biblioteca.h"

Biblioteca::Biblioteca(QObject* parent) : QObject(parent), list(), indice(1) {}

Biblioteca::~Biblioteca() = default;

//restituisce la lista
QList<Risorsa*> Biblioteca::getList() const{
    return list;
}

//Aggiunge risorsa alla lista
void Biblioteca::addRisorsa(Risorsa* ris){
    list.append(ris);
    sortByTitle();
    emit listaAggiornata();
}

//rimuove la risorsa dalla lista
bool Biblioteca::deleteRisorsa(Risorsa* ris){
    
    bool removed = list.removeOne(ris);
    delete ris;
    if(removed) emit listaAggiornata();
    return removed;
}

//carica la lista con i contenuti del json
bool Biblioteca::load(QString path){
    QList<Risorsa*> tmp;
    tmp = JsonUtilities::loadAllFromJson(path);
    if(tmp.size() == 0) return false;
    list.clear();
    list = tmp;
    indice = list.size();
    sortByTitle();
    emit listaAggiornata();
    return true;
    
}

//salva gli items della lista nel json indicato dal path
bool Biblioteca::save(QString path) const{
    return JsonUtilities::saveAllToJson(path, list);
}

int Biblioteca::usaIndice(){
    return indice ++;
}

//ricerca gli elementi della lista sulla base delle keywords e dei filtri
QList<Risorsa*> Biblioteca::search(const QString& txt, const QString& typ, int aMin, int aMax, bool disp)const{
    
    QList<Risorsa*> out;
    
    FiltroVisitor fv(txt, typ, aMin, aMax, disp);

    for(Risorsa* r : list){
        r->accept(&fv);
        if(fv.accetta()){
            out.append(r);
        }
            
    }

    return out;

}

//Ordina per ordine alfaetico
void Biblioteca::sortByTitle(){
    std::sort(list.begin(), list.end(), [](Risorsa* a, Risorsa* b){
        return QString::fromStdString(a->getTitolo()).toLower() < QString::fromStdString(b->getTitolo()).toLower();
    });
}
