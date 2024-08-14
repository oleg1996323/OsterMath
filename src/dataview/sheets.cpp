#include "dataview/sheets.h"
#include "kernel/application.h"
#include "dataview/variable_list/dock.h"
#include <QTimer>

namespace dataview{

Sheets::Sheets(QWidget* parent):
    QTabWidget(parent),
    ObjectFromSettings(this)
{
    setObjectName("sheets_view");
    load_settings();
    __init__();

    connect(this,&Sheets::tabBarClicked,[this](int id){
        int current = currentIndex();
        __change_dock_to__(qobject_cast<View*>(widget(id)));
        __change_model__(id);
        setCurrentIndex(id);
    });

    for(int i=0;i<4;++i)
        add_default_sheet(i);
    connect(findChild<::model::VariablesDelegate*>("var_list_delegate"), &::model::VariablesDelegate::show_node,[this](Node* node){
        qobject_cast<View*>(currentWidget())->show_node(node);
    });
}

Sheets::Sheets(QWidget* parent, const QString& data_name):
    QTabWidget(parent),
    ObjectFromSettings(this)
{
    load_settings();
}

Sheets::~Sheets(){
    save_settings();
    delete var_list_; //for saving state of window
}

#include "data.h"
#include "model/nodeview_model.h"

void Sheets::init_new_pool(){
    if(kernel::Application::get_active_pool())
        manager_.clear();
}

void Sheets::rename(const QString& name){
    kernel::Application::get_active_pool()->set_name(name.toStdString());
}

void Sheets::erase_sheet(const QString& name) noexcept{
    kernel::Application::get_active_pool()->erase(name.toStdString());
}

void Sheets::tabRemoved(int index){
    //sheets_.removeAt(index);
}

void Sheets::change_sheet_name(QString&& name, int tab_id){
    for(int id = 0; id<count();++id){
        if(tab_id!=id){
            if(tabText(id)==name)
                QMessageBox(QMessageBox::Icon::Critical,QObject::tr("Невозможно создать лист"), tr("Лист с таким названием уже существует"),QMessageBox::Ok,this);
            else{
                kernel::Application::get_active_pool()->get(tabText(tab_id).toStdString())->set_name(name.toStdString());
                setTabText(tab_id,name);
            }
        }
    }
}

View* Sheets::__create_default_tab__(QString& name){
    name = tr("Sheet")+QString::number(kernel::Application::get_active_pool()->size()).toUtf8();
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(name.toStdString());
    manager_.add_data(this,data); //check the parent object
    kernel::Application::set_active_data(data);
    return new View(this,data);
}

void Sheets::add_default_sheet(int id){
    QString name;
    View* view = __create_default_tab__(name);
    //qDebug()<<"Before inserting"<<id;
    insertTab(id,view,name);
    //qDebug()<<"After inserting"<<id;
    __change_dock_to__(view);
    __change_model__(id);
    setCurrentIndex(id);
}

void Sheets::add_default_sheet(){
    QString name;
    View* view = __create_default_tab__(name);
    int new_id = addTab(view,name);
    __change_dock_to__(view);
    __change_model__(new_id);
    setCurrentIndex(new_id);
}

void Sheets::tabInserted(int id){
}

void Sheets::__change_model__(int id){
    std::string str = tabText(id).toStdString();
    BaseData* data = kernel::Application::get_active_pool()->get(tabText(id).toStdString());
    var_list_->setData(manager_.get_data(data));
    qobject_cast<View*>(widget(id))->set_model(manager_.get_data(data)->data_model.get());
}

void Sheets::__change_dock_to__(View* tab_window) {
    if (tab_window) {

        //initialization
        if(!var_list_){
            var_list_ = new DockWidget(tab_window);

            if(win_state_.isEmpty()){
                tab_window->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
                if(var_list_->closed_by_titlebar())
                    var_list_->close_from_titlebar();
            }
            else{
                if(!var_list_->isFloating()){
                    assert(tab_window->restoreState(win_state_));
                    tab_window->restoreDockWidget(var_list_);
                }
                else
                    tab_window->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
            }
        }
        else{
            if(var_list_->parent()){
                save_last_window_state(qobject_cast<View*>(var_list_->parent())->saveState());
                //qobject_cast<View*>(var_list_->parent())->removeDockWidget(var_list_);
            }
            if(!win_state_.isEmpty()){
                QTimer::singleShot(0,[this, tab_window]{
                    var_list_->setParent(tab_window);
                    assert(tab_window->restoreState(win_state_));
                    tab_window->restoreDockWidget(var_list_);
                });
            }
            else{
                var_list_->setParent(tab_window);
                tab_window->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
            }
        }

        if(var_list_->closed_by_titlebar())
            var_list_->close_from_titlebar();
    }
}

void Sheets::save_last_window_state(QByteArray&& state){
    win_state_ = state;
}

const QByteArray& Sheets::get_last_window_state() const{
    return win_state_;
}

void Sheets::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //TODO
//    if(sets_->contains("curId")){
//        int current = sets_->value("curId").toInt();
//        tabBarClicked(current);
//        setCurrentIndex(current);
//    }
    if(sets_->contains("winstate"))
        win_state_ = sets_->value("winstate").toByteArray();
    sets_->endGroup();
    //add loading settings from project
}

void Sheets::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    if(var_list_ && var_list_->parent())
        sets_->setValue("winstate",qobject_cast<View*>(var_list_->parent())->saveState());
    sets_->endGroup();
}

void Sheets::__upload_fonts__(){

}
void Sheets::__upload_style__(){

}
void Sheets::__upload_language__(){

}
void Sheets::__retranslate__(){

}

}
