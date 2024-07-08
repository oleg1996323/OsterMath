#include "dataview/sheets.h"
#include "kernel/application.h"

namespace dataview{

Sheets::Sheets(QWidget* parent):
    QTabWidget(parent)
{
    __load_settings__();
    for(int i=0;i<3;++i)
        add_default_sheet();
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
#include "model/dataviewmodel.h"

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
    QString new_name = tr("Лист"+QString::number(kernel::Application::get_active_pool()->size()).toUtf8());
    sheets_.push_back(new QTableView(this));
    int id = this->addTab(sheets_.back(),new_name);
    sheets_.back()->setModel(new model::DataView(sheets_.back()));
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

void DataViewSplit::__define_view__(){
    expression_view_ = new VarExpressionView(this);
    data_ = new Sheets(this);
    addWidget(expression_view_);
    addWidget(data_);
    setCollapsible(0,false);
    setCollapsible(1,false);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    data_->setObjectName("data_view");
    this->setSizes({20,data_->maximumHeight()});
}
}
