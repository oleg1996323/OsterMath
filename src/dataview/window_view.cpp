#include "dataview/window_view.h"
#include <QWidget>
#include <QDebug>
#include "data.h"
#include "dataview/variable_list/dock.h"
#include "dataview/model_data/nodedataview.h"
#include "dataview/link_viewed_nodes.h"
#include <QVBoxLayout>

namespace dataview{
WindowView::WindowView(QWidget* parent, BaseData* data):QMainWindow(parent, Qt::Widget|Qt::WindowTitleHint), ObjectFromSettings(this){
    setObjectName("sheet_window");
    load_settings();
    QWidget* central = new QWidget(this);
    QVBoxLayout* central_layout = new QVBoxLayout(central);
    link_viewed_nodes_ = new LinkViewedNodes(this);
    data_view_ = new NodeData(this);
    central_layout->addWidget(link_viewed_nodes_);
    central_layout->addWidget(data_view_);
    central_layout->setContentsMargins(0,0,0,0);
    central->setLayout(central_layout);
    central->setContentsMargins(0,0,0,0);
    setCentralWidget(central);
    //TODO connect signals between data_view model and link_viewed_nodes_;
}
WindowView::~WindowView(){
    save_settings();
}
void WindowView::show_variable(Node* parent, int id) const{
    //TODO add arrows with link buttons without frame and panel
    qobject_cast<model::NodeView*>(data_view_->model())->set_representable_variable(parent,id);
    link_viewed_nodes_->reset();
    link_viewed_nodes_->add_button(INFO_NODE({parent,id}));
}
QAbstractProxyModel* WindowView::search_var(const QString&){
    //TODO
    return nullptr;
}
void WindowView::set_model(QAbstractItemModel* model){
    assert(model);
    data_view_->setModel(model);
    data_view_->setRootIndex(QModelIndex());
    data_view_->horizontalHeader()->setModel(model);
    if(model::NodeView* m = qobject_cast<model::NodeView*>(data_view_->model()))
        connect(m,&model::NodeView::add_link,link_viewed_nodes_,&LinkViewedNodes::add_button);
    else
        assert(true);
    connect(link_viewed_nodes_,&LinkViewedNodes::update_sequence,[this](const std::vector<INFO_NODE>& sequence_info){
        assert(data_view_->model());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(data_view_->model())){
            m->set_sequence(sequence_info);
        }
        else assert(true);
    });
}
void WindowView::set_selection(QItemSelectionModel* sel){
    if(data_view_->model())
        data_view_->setSelectionModel(sel);
}
NodeData* WindowView::data_viewer() const{
    return data_view_;
}
void WindowView::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    sets_->endGroup();
}
void WindowView::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->endGroup();
}
void WindowView::__upload_fonts__(){

}
void WindowView::__upload_style__(){

}
void WindowView::__upload_language__(){

}
void WindowView::__retranslate__(){

}
}
