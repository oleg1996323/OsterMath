#include "dataview/variable_list/dock.h"
#include "dataview/variable_list/table.h"
#include "dataview/variable_list/titlebar.h"
#include "dataview/variable_list/search_line.h"
#include "model/varlist_model.h"
#include "dataview/sheets.h"
#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>

namespace dataview{
DockWidget::DockWidget(QWidget* parent):QDockWidget(parent), ObjectFromSettings(this){
    setObjectName("dockwidget_var_list");

    titlebar_ = new TitleBar(this);
    QWidget* w = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(w);
    frame_ = new Frame(this);
    var_list_ = new Table(this);
    upload_style();
    load_settings();
    this->setContentsMargins(0,0,0,0);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea);
    QSizePolicy sizepolicy;
    sizepolicy.setHorizontalPolicy(QSizePolicy::Ignored);
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(frame_);
    layout->addWidget(var_list_);
    w->setLayout(layout);
    setWidget(w);
    retranslate();
}

void DockWidget::__retranslate__(){
    frame_->retranslate();
    titlebar_->retranslate();
}

DockWidget::~DockWidget(){
    save_settings();
}

void DockWidget::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    if(sets_->value("hidden").toBool())
        collapse();
    closed = sets_->value("closed").toBool();
    setFloating(sets_->value("floating").toBool());
    qDebug()<<"DockWidget init geometry"<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void DockWidget::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->setValue("hidden",!isHidden() && frame_->isHidden() && var_list_->isHidden());
    sets_->setValue("closed",closed);
    sets_->setValue("floating", isFloating());

    qDebug()<<"DockWidget save geometry"<<geometry();
    sets_->endGroup();
}

void DockWidget::__upload_fonts__(){

}
void DockWidget::__upload_style__(){
    setPalette(Themes::Palette::get());
}
void DockWidget::__upload_language__(){

}

void DockWidget::collapse(){
    if(frame_->isHidden()){
        //setFeatures(features()^QDockWidget::DockWidgetVerticalTitleBar);
        //titlebar_->setHorizontal();
        frame_->show();
        var_list_->show();
        //titlebar_->repaint();
    }
    else{
        //setFeatures(QDockWidget::DockWidgetVerticalTitleBar | features() );
        //titlebar_->setVertical();
        frame_->hide();
        var_list_->hide();
        //titlebar_->repaint();
    }
}

QMainWindow* DockWidget::window_attached() const{
    return nullptr;//window_owner_;
}

bool DockWidget::closed_by_titlebar() const{
    return closed;
}

void DockWidget::set_window_attached(View * window){

}

void DockWidget::close_from_titlebar(){
    closed = true;
    close();
}

void DockWidget::closeEvent(QCloseEvent *event){
    (void)event;
}

void DockWidget::showEvent(QShowEvent *event){
    (void)event;
}

void DockWidget::setData(model::Data* data){
    if(data->var_model)
        var_list_->setModel(data->var_model.get());
}
}
