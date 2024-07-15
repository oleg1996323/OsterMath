#include "dataview/tabwidgetdataview.h"
#include <QWidget>
#include <QDebug>
#include "data.h"
#include "dataview/variable_list/dock.h"
#include "dataview/model_data/nodedataview.h"

namespace dataview{

View::View(QWidget* parent, BaseData* data):QMainWindow(parent, Qt::Widget|Qt::WindowTitleHint), ObjectFromSettings(this){
    setObjectName("sheet_window");
    load_settings();
    data_view_ = new NodeData(parent);
    setCentralWidget(data_view_);
}

View::~View(){
    save_settings();
}

void View::show_variable_list(QModelIndex index) const{

}

QAbstractProxyModel* View::search_var(const QString&){

}

void View::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void View::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->endGroup();
}
void View::__upload_fonts__(){

}
void View::__upload_style__(){

}
void View::__upload_language__(){

}

void View::__retranslate__(){

}
}
