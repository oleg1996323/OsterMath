#include "dataview/sheets.h"
#include "kernel/application.h"
#include "dataview/variable_list/dock.h"

namespace dataview{

Sheets::Sheets(QWidget* parent):
    QTabWidget(parent)
{
    var_list_ = new DockWidget(nullptr);
    __load_settings__();
    connect(this,&Sheets::tabBarClicked,this,&Sheets::__change_widget__);
    for(int i=0;i<3;++i)
        add_default_sheet();
}

void Sheets::__change_widget__(int index){
    qobject_cast<View*>(widget(index))->addDockWidget(qobject_cast<View*>(this->currentWidget())->dockWidgetArea(var_list_),var_list_);
    //add resize
    //add last position
    //add attached if possible
}

Sheets::Sheets(QWidget* parent, const QString& data_name):
    QTabWidget(parent)
{
    __load_settings__();
}

Sheets::~Sheets(){
    __save_settings__();
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
            else
                setTabText(tab_id,name);
        }
    }
}

void Sheets::add_default_sheet(){
    assert(var_list_);
    QString new_name = tr("Лист"+QString::number(kernel::Application::get_active_pool()->size()).toUtf8());
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(QString("Data base %1").arg(pool->data_bases().size()+1).toStdString());
    kernel::Application::set_active_data(data);
    View* view = new View(this,data);
    View* current = qobject_cast<View*>(this->currentWidget());
    if(current)
        view->addDockWidget(current->dockWidgetArea(var_list_),var_list_);
    else view->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
    int id = this->addTab(view,new_name);
    setCurrentIndex(id);
}

void Sheets::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("widget/sheetstab");
    this->setGeometry(sets_->value("geometry").toRect());
    setPalette(Themes::Palette::get());
    sets_->endGroup();
}

void Sheets::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("sheetstab");
    sets_->setValue("geometry",geometry());
    setPalette(Themes::Palette::get());
    sets_->endGroup();
}
}
