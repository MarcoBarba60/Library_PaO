#ifndef CATALOGOITEM_H
#define CATALOGOITEM_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

//Crea gli item della lista-catalogo con immagine e titolo
class CatalogoItem : public QWidget{
    Q_OBJECT

    public:
        CatalogoItem(const QString& copertina, const QString& titolo, QWidget* parent = nullptr);

};//CatalogoItem

#endif //CATALOGOITEM_H