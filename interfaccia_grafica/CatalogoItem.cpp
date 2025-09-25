#include "CatalogoItem.h"

CatalogoItem::CatalogoItem(const QString& copertina, const QString& titolo, QWidget* parent)
    : QWidget(parent) {

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(10);

    //immagine di copertina
    QLabel* cop = new QLabel;
    QPixmap pix(copertina);
    cop->setPixmap(pix.scaled(60, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(cop);

    //titolo
    QLabel* tit = new QLabel(titolo);
    tit->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    tit->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(tit, 1);
}
