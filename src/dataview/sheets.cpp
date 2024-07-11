#include "dataview/sheets.h"
#include "kernel/application.h"
#include "dataview/variable_list/dock.h"
#include <QTimer>

namespace dataview{

Sheets::Sheets(QWidget* parent):
    QTabWidget(parent)
{
    var_list_ = new DockWidget(this);
    __init__();
    __load_settings__();
    connect(this,&Sheets::tabBarClicked,[this](int id){__change_dock_to__(qobject_cast<QMainWindow*>(widget(id)));});
    for(int i=0;i<3;++i)
        add_default_sheet(i);
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

void Sheets::add_default_sheet(int id){
    assert(var_list_);
    QString new_name = tr("Лист"+QString::number(kernel::Application::get_active_pool()->size()).toUtf8());
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(QString("Data base %1").arg(pool->data_bases().size()+1).toStdString());
    kernel::Application::set_active_data(data);
    View* view = new View(this,data);
    if(!qobject_cast<View*>(this->currentWidget()))
        view->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
    else __change_dock_to__(view);
    insertTab(id,view,new_name);
    setCurrentIndex(id);
}

void Sheets::add_default_sheet(){
    assert(var_list_);
    QString new_name = tr("Лист"+QString::number(kernel::Application::get_active_pool()->size()).toUtf8());
    DataPool* pool = kernel::Application::get_active_pool();
    ::BaseData* data = pool->add_data(QString("Data base %1").arg(pool->data_bases().size()+1).toStdString());
    kernel::Application::set_active_data(data);
    View* view = new View(this,data);
    if(!qobject_cast<View*>(this->currentWidget()))
        view->addDockWidget(Qt::LeftDockWidgetArea,var_list_);
    else __change_dock_to__(view);
    int new_id = addTab(view,new_name);
    setCurrentIndex(new_id);
}

void Sheets::tabInserted(int id){
    assert(var_list_);
    View* view = qobject_cast<View*>(this->widget(id));
    View* current = qobject_cast<View*>(this->currentWidget());
}

void Sheets::__change_dock_to__(QMainWindow* tab_window) {
    if (tab_window && var_list_) {
        View* current = qobject_cast<View*>(this->currentWidget());
        if (!current) return;

        // Сохранение состояния var_list_
        QByteArray state = current->saveState();
        QByteArray geometry = var_list_->saveGeometry();
        bool floating = var_list_->isFloating();
        QRect floatGeometry;
        if (floating) {
            floatGeometry = var_list_->geometry();
        }

        // Отсоединяем var_list_ от текущего виджета
        current->removeDockWidget(var_list_);

        // Добавляем var_list_ в новый tab_window
        tab_window->addDockWidget(Qt::LeftDockWidgetArea, var_list_);

        // Восстанавливаем состояние и геометрию var_list_ после полной инициализации
        QTimer::singleShot(0, [this, tab_window, state, geometry, floating, floatGeometry]() {
            bool restoreGeometrySuccess = var_list_->restoreGeometry(geometry);
            qDebug() << "Restore geometry success:" << restoreGeometrySuccess;

            if (floating) {
                var_list_->setFloating(true);
                var_list_->setGeometry(floatGeometry);
                qDebug() << "Restored floating geometry:" << var_list_->geometry();
            }

            bool restoreStateSuccess = tab_window->restoreState(state);
            qDebug() << "Restore state success:" << restoreStateSuccess;

            var_list_->show();
            tab_window->updateGeometry();
        });
    }
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
