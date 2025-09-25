#ifndef INFOVISITOR_H
#define INFOVISITOR_H
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QStringList>
#include <QPushButton>
#include "../Visitor.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/Dvd.h"
#include "../modello_logico/Vinile.h"

//Sfrutta i visitor per creare i pannelli di informazioni per ogni tipo di risorsa
class InfoVisitor : public QObject, public Visitor{
    Q_OBJECT

    private:
        QWidget* widget;
        QWidget* layoutComune(const QString& path_img, const QStringList& info, Risorsa* r);

    public:
        InfoVisitor(QObject* parent = nullptr);
        ~InfoVisitor() = default;

        virtual void visit(Libro* libro) override;
        virtual void visit(Rivista* rivista) override;
        virtual void visit(Dvd* film) override;
        virtual void visit(Vinile* vin) override;

        QWidget* getWidget() const;
    signals:
        void prestitoSig(Risorsa* r);
        void restituzioneSig(Risorsa* r);
        void rimozioneSig(Risorsa* r);
        void modificaSig(Risorsa* r);



};//InfoVisitor

#endif//INFOVISITOR_H