#include "dataview/variable_list/table.h"
#include "kernel/application.h"
#include "model/varlist_model.h"
#include "model/varlist_header.h"
#include "model/varlist_delegate.h"
#include <QDebug>

namespace dataview{
Table::Table(QWidget* parent):ObjectFromSettings(this){
    setObjectName("tableview_var_list");
    QSizePolicy size_policy;
    size_policy.setRetainSizeWhenHidden(true);
    size_policy.setHorizontalPolicy(QSizePolicy::Expanding);
    size_policy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    setSizePolicy(size_policy);
    load_settings();
    setItemDelegate(new model::VariablesDelegate(this));
    setHorizontalHeader(new model::VariablesHeader(this));
    setAlternatingRowColors(true);
}

Table::~Table(){
    save_settings();
}

void Table::change_model(QAbstractItemModel* model){
    this->setModel(model);
}

void Table::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void Table::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->endGroup();
}
void Table::__upload_fonts__(){

}
void Table::__upload_style__(){

}
void Table::__upload_language__(){
    retranslate();
}
void Table::__retranslate__(){

}

QSize Table::sizeHint() const{
    QSize sz = size();
    return sz;
}
}
