#ifndef JSONVISITOR_H
#define JSONVISITOR_H
#include "../Visitor.h"
#include <QJsonObject>
#include "../modello_logico/Libro.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/Dvd.h"
#include "../modello_logico/Vinile.h"

class JsonVisitor : public Visitor{
    private :
        QJsonObject json;

    public:
        virtual void visit(Libro* libro) override;
        virtual void visit(Rivista* rivista) override;
        virtual void visit(Dvd* film) override;
        virtual void visit(Vinile* vin) override;
        QJsonObject getJson() const;

};

#endif