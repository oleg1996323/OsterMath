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
    node_view_delegate_ = new model::NodeViewDelegate(this);
    node_view_header_ = new model::NodeViewHeader(this);
    data_view_ = new NodeData(parent);
    setCentralWidget(data_view_);
}

View::~View(){
    save_settings();
}

void View::show_variable_list(){
    if(!var_list_->isVisible()){
        var_list_->show();
    }
}

QAbstractProxyModel* View::search_var(const QString&){

}

void View::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());

    restoreGeometry(sets_->value("geometry").toByteArray());
    restoreState(sets_->value("state").toByteArray());
    setVisible(!sets_->value("hidden").toBool());

    qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void View::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("state",saveState());
    sets_->setValue("geometry",saveGeometry());
    sets_->setValue("hidden",isHidden());
    sets_->endGroup();
}
void View::upload_fonts(){

}
void View::upload_style(){

}
void View::upload_language(){

}

void View::retranslate(){

}
}
