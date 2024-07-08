#include "model/varlistmodel_header.h"
#include "model/varlistmodel.h"

namespace model{
ListHeader::ListHeader(QWidget* parent):QHeaderView(Qt::Horizontal,parent){
    setFirstSectionMovable(false);
    setStretchLastSection(true);
    QFont font;
    font.setFamily(QString::fromUtf8("Sans Serif"));
    font.setPointSize(8);
    font.setBold(true);
    font.setWeight(75);
    setFont(font);
}
}
