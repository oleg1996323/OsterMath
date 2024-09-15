#pragma once
#include <QLineEdit>
#include "aux/__borders_interface__.h"

class LineEdit:public QLineEdit, public oster::utilities::__interfaces__::BordersInterface{
    Q_OBJECT
public:
    LineEdit(QWidget* parent):QLineEdit(parent){}
    LineEdit(QString text,QWidget* parent):QLineEdit(text,parent){}
};
