#include "dataview/model_data/aux_windows/insert_rows.h"
#include <QLabel>

namespace dataview{
InsertRows::InsertRows(QModelIndex first_index, QWidget* parent):RowColumnInsertInterface(parent){
    spin_label_->setText(QObject::tr("Number inserted columns:"));
    combo_label_->setText(QObject::tr("Before/after:"));
}
}
