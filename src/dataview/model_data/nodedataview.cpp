#include "dataview/model_data/nodedataview.h"
#include <QDebug>

namespace dataview{
NodeData::NodeData(QWidget* parent):
    QTableView(parent),
    ObjectFromSettings(this)
{
    setObjectName("nodedataview");
    load_settings();
    setItemDelegate(new model::NodeViewDelegate(this));
    setHorizontalHeader(new model::NodeViewHeader(this));
    setContentsMargins(5,0,5,0);
}

NodeData::~NodeData(){
    save_settings();
}

void NodeData::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //qDebug()<<"NodeData init geometry"<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void NodeData::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    //qDebug()<<"NodeData save geometry"<<geometry();
    sets_->endGroup();
}
void NodeData::__upload_fonts__(){

}
void NodeData::__upload_style__(){

}
void NodeData::__upload_language__(){

}

}
