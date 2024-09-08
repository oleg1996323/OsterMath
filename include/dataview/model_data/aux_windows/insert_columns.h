#pragma once
#include <QSpinBox>
#include <QComboBox>
#include "RowColumnInsertInterface.h"

class QGridLayout;
class QLabel;
namespace dataview{
    class InsertColumns:public RowColumnInsertInterface{
        Q_OBJECT
    public:
        InsertColumns(QModelIndexList&& first_index, QWidget* parent);
    };
}
