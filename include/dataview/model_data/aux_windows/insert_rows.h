#pragma once
#include <QSpinBox>
#include <QComboBox>
#include "RowColumnInsertInterface.h"

class QGridLayout;
class QLabel;
namespace dataview{
    class InsertRows:public RowColumnInsertInterface{
        Q_OBJECT
    public:
        InsertRows(QModelIndex first_index, QWidget* parent);
    };
}
