#ifndef FILTROVISITOR_H
#define FILTROVISITOR_H
#include "../Visitor.h"
#include <QString>
#include "Libro.h"
#include "Rivista.h"
#include "Dvd.h"
#include "Vinile.h"

class FiltroVisitor : public Visitor{
    QString testo;
    QString tipo;
    int anno_min;
    int anno_max;
    bool disponibile;
    bool accepted;

    public:
         FiltroVisitor(const QString& txt, const QString& typ, int aMin, int aMax, bool disp); 
         ~FiltroVisitor() = default;

         void visit(Libro* l)override;
         void visit(Rivista* r)override;
         void visit(Dvd* d)override;
         void visit(Vinile* v)override;

         bool accetta() const;

    private:
        void controlla(const QString& txt, const QString& typ, int annoPubb, int disp);


}; //FiltroVisitor

#endif //FILTROVISITOR_H