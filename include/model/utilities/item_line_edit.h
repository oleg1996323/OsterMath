#pragma once
#include "types.h"
#include "arithmetic_types.h"
#include "format.h"
#include <QLineEdit>

class ItemLineEdit:public QLineEdit{
    Q_OBJECT
public:
    ItemLineEdit(QWidget* parent, Node* node):QLineEdit(parent){
        std::string text;
        std::stringstream stream(text);

        //setText((get_stream()).str());
    }

private:

};
