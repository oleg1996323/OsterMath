#include "dataview/tabwidgetdataview.h"
#include <QWidget>
#include <QDebug>
#include "data.h"
#include "dataview/variable_list/dock.h"
#include "dataview/model_data/nodedataview.h"
#include "dataview/link_viewed_nodes.h"
#include <QVBoxLayout>

namespace dataview{
View::View(QWidget* parent, BaseData* data):QMainWindow(parent, Qt::Widget|Qt::WindowTitleHint), ObjectFromSettings(this){
    setObjectName("sheet_window");
    load_settings();
    QWidget* central = new QWidget(this);
    QVBoxLayout* central_layout = new QVBoxLayout(this);
    link_viewed_nodes_ = new LinkViewedNodes(this);
    data_view_ = new NodeData(parent);
    central_layout->addWidget(link_viewed_nodes_);
    central_layout->addWidget(data_view_);
    central->setLayout(central_layout);
    setCentralWidget(data_view_);
    //TODO connect signals between data_view model and link_viewed_nodes_;
}
View::~View(){
    save_settings();
}
void View::show_variable(Node* parent, size_t id) const{
    //TODO add arrows with link buttons without frame and panel
    qobject_cast<model::NodeView*>(data_view_->model())->set_representable_variable(parent,id);
}
QAbstractProxyModel* View::search_var(const QString&){
    //TODO
    return nullptr;
}
void View::set_model(QAbstractItemModel* model){
    data_view_->setModel(model);
    data_view_->setRootIndex(QModelIndex());
    data_view_->horizontalHeader()->setModel(model);
}
void View::set_selection(QItemSelectionModel* sel){
    if(data_view_->model())
        data_view_->setSelectionModel(sel);
}
NodeData* View::data_viewer() const{
    return data_view_;
}
void View::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
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
