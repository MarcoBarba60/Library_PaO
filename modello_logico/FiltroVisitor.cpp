#include "FiltroVisitor.h"

FiltroVisitor::FiltroVisitor(const QString& txt, const QString& typ, int aMin, int aMax, bool disp) : testo(txt), tipo(typ), anno_min(aMin), anno_max(aMax), disponibile(disp){}

void FiltroVisitor::visit(Libro* l){
    controlla(QString::fromStdString(l->getTitolo()).toLower(), "Libro", l->getAnnoPubblicazione(), l->getDisponibili());
}
void FiltroVisitor::visit(Rivista* r){
    controlla(QString::fromStdString(r->getTitolo()).toLower(), "Rivista", r->getAnnoPubblicazione(), r->getDisponibili());

}
void FiltroVisitor::visit(Dvd* d){
    controlla(QString::fromStdString(d->getTitolo()).toLower(), "Dvd", d->getAnnoPubblicazione(), d->getDisponibili());
}
void FiltroVisitor::visit(Vinile* v){
    controlla(QString::fromStdString(v->getTitolo()).toLower(), "Vinile", v->getAnnoPubblicazione(), v->getDisponibili());
}

bool FiltroVisitor::accetta() const{
    return accepted;
}
void FiltroVisitor::controlla(const QString& txt, const QString& typ, int annoPubb, int disp){
    
    accepted= false;

    //Tipo
    if(tipo != "Tutti" && tipo != typ){
        return;
    }
        

    //Titolo
    if(!testo.isEmpty() && !txt.contains(testo)){
        return;
    }

    //Anno
    if(annoPubb < anno_min || annoPubb >anno_max){
        return;
    }
    
    //Disponibilita
    if(disponibile && disp<= 0){
        return;
    }
    
    accepted = true;
}