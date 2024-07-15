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

    __init__();

    connect(this,&Sheets::tabBarClicked,[this](int id){
    __change_dock_to__(qobject_cast<View*>(widget(id)));
    std::string str = tabText(id).toStdString();
    BaseData* data = kernel::Application::get_active_pool()->get(tabText(id).toStdString());
    model::Variables* data_model = manager_.get_data(data)->var_model.get();
    emit set_model_to_var_list(data_model);});
    for(int i=0;i<4;++i)
        add_default_sheet(i);
    load_settings();
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

void Sheets::add_default_sheet(int id){
    QString new_name = tr("Sheet")+QString::number(kernel::Application::get_active_pool()->size()).toUtf8();
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(new_name.toStdString());
    manager_.add_data(this,data); //check the parent object
    kernel::Application::set_active_data(data);
    View* view = new View(this,data);
    __change_dock_to__(view);
    insertTab(id,view,new_name);
    setCurrentIndex(id);
}

void Sheets::add_default_sheet(){
    assert(var_list_);
    QString new_name = tr("Sheet")+QString::number(kernel::Application::get_active_pool()->size()).toUtf8();
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(new_name.toStdString());
    manager_.add_data(this,data); //check the parent object
    kernel::Application::set_active_data(data);
    View* view = new View(this,data);
    __change_dock_to__(view);

    int new_id = addTab(view,new_name);
    setCurrentIndex(new_id);
}

void Sheets::tabInserted(int id){
    assert(var_list_);
    View* view = qobject_cast<View*>(this->widget(id));
    View* current = qobject_cast<View*>(this->currentWidget());
}

void Sheets::__change_dock_to__(View* tab_window) {
    if (tab_window) {
        if(!var_list_)
            var_list_ = new DockWidget(tab_window);
        var_list_->set_window_attached(tab_window);
        //bool restoreStateSuccess = tab_window->restoreState(state);
        //qDebug() << "Restore state success:" << restoreStateSuccess;
        tab_window->updateGeometry();
    }
}

void Sheets::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
//    if(sets_->contains("curId")){
//        int current = sets_->value("curId").toInt();
//        tabBarClicked(current);
//        setCurrentIndex(current);
//    }
    setPalette(Themes::Palette::get());
    sets_->endGroup();
    //add loading settings from project
}

void Sheets::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    //sets_->setValue("curId",currentIndex());
    sets_->endGroup();
}

void Sheets::__upload_fonts__(){

}
void Sheets::__upload_style__(){
    setPalette(Themes::Palette::get());
}
void Sheets::__upload_language__(){

}
void Sheets::__retranslate__(){

}

}
