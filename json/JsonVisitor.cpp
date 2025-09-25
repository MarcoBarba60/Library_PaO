#include "JsonVisitor.h"

//Libro
void JsonVisitor::visit(Libro* libro){
    json["id"] = static_cast<int>(libro->getId());
    json["classe"] = "Libro";
    json["titolo"] = QString::fromStdString(libro->getTitolo());
    json["anno_pubblicazione"] = libro->getAnnoPubblicazione();
    json["prezzo"] = libro->getPrezzo();
    json["path_img"] = QString::fromStdString(libro->getImgPath());
    json["copie_biblioteca"] = libro->getCopieBiblioteca();
    json["disponibili"] = libro->getDisponibili();
    json["autore"] = QString::fromStdString(libro->getAutore());
    json["casa_editrice"] = QString::fromStdString(libro->getCasaEditrice());
    json["n_pagine"] = static_cast<int>(libro->getNPagine());
    json["genere"] = QString::fromStdString(libro->getGenereToString());
    json["lingua_originale"] = QString::fromStdString(libro->getLinguaOriginale());
}

//Rivista
void JsonVisitor::visit(Rivista* rivista){
    json["id"] = static_cast<int>(rivista->getId());
    json["classe"] = "Rivista";
    json["titolo"] = QString::fromStdString(rivista->getTitolo());
    json["anno_pubblicazione"] = rivista->getAnnoPubblicazione();
    json["prezzo"] = rivista->getPrezzo();
    json["path_img"] = QString::fromStdString(rivista->getImgPath());
    json["copie_biblioteca"] = rivista->getCopieBiblioteca();
    json["disponibili"] = rivista->getDisponibili();
    json["autore"] = QString::fromStdString(rivista->getAutore());
    json["casa_editrice"] = QString::fromStdString(rivista->getCasaEditrice());
    json["n_pagine"] = static_cast<int>(rivista->getNPagine());
    json["periodicita"] = QString::fromStdString(rivista->getPeriodicitaToString());
    json["argomento"] = QString::fromStdString(rivista->getArgomentoToString());
}

//Film
void JsonVisitor::visit(Dvd* film){
    json["id"] = static_cast<int>(film->getId());
    json["classe"] = "Dvd";
    json["titolo"] = QString::fromStdString(film->getTitolo());
    json["anno_pubblicazione"] = film->getAnnoPubblicazione();
    json["prezzo"] = film->getPrezzo();
    json["path_img"] = QString::fromStdString(film->getImgPath());
    json["copie_biblioteca"] = film->getCopieBiblioteca();
    json["disponibili"] = film->getDisponibili();
    json["durata"] = static_cast<int>(film->getDurata());
    json["regista"] = QString::fromStdString(film->getRegista());
    json["contenuti_aggiuntivi"] = film->getContenutiBonus();
}

//Vinile
void JsonVisitor::visit(Vinile* vin){
    json["id"] = static_cast<int>(vin->getId());
    json["classe"] = "Vinile";
    json["titolo"] = QString::fromStdString(vin->getTitolo());
    json["anno_pubblicazione"] = vin->getAnnoPubblicazione();
    json["prezzo"] = vin->getPrezzo();
    json["path_img"] = QString::fromStdString(vin->getImgPath());
    json["copie_biblioteca"] = vin->getCopieBiblioteca();
    json["disponibili"] = vin->getDisponibili();
    json["durata"] = static_cast<int>(vin->getDurata());
    json["autore"] = QString::fromStdString(vin->getAutore());
    json["casa_discografica"] = QString::fromStdString(vin->getCasaDiscografica());
    json["n_tracce"] = static_cast<int>(vin->getNTracce());
}

QJsonObject JsonVisitor::getJson() const{
    return json;
}