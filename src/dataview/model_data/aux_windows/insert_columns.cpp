#include "dataview/model_data/aux_windows/insert_columns.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QStringList>
#include <QPushButton>

namespace dataview{
InsertColumns::InsertColumns(QModelIndex first_index, QWidget* parent):RowColumnInsertInterface(parent){
    spin_label_->setText(QObject::tr("Number inserted columns:"));
}
}
