#include "dataview/variable_list/dock.h"
#include "dataview/variable_list/table.h"
#include "dataview/variable_list/titlebar.h"
#include "dataview/variable_list/search_line.h"
#include "model/varlist_model.h"
#include <QMainWindow>
#include <QDebug>

namespace dataview{
DockWidget::DockWidget(QWidget* parent):QDockWidget(parent){
    setObjectName("dockwidget_var_list");
    __load_styles__();
    __load_settings__();
    //QBrush brush_1(QColor(190,220,255,255));
    //palette->setBrush(QPalette::ColorRole::Window, brush_1);

    titlebar_ = new TitleBar(this);
    this->setContentsMargins(0,0,0,0);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea);
    QSizePolicy sizepolicy;
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setVerticalPolicy(QSizePolicy::Preferred);
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    frame_ = new Frame(this);
    frame_->setPalette(Themes::Palette::get());
    setWidget(frame_);

    retranslate();
    last_size = size();
}

void DockWidget::retranslate(){
    frame_->retranslate();
    titlebar_->retranslate();
}

DockWidget::~DockWidget(){
    __save_settings__();
}

void DockWidget::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    setGeometry(sets_->value("geometry").toRect());
    setVisible(!sets_->value("hidden").toBool());
    qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void DockWidget::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",geometry());
    sets_->setValue("hidden",isHidden());
    sets_->endGroup();
}

void DockWidget::__load_styles__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    if(kernel::settings::Program::get_theme() == Themes::Dark)
        setPalette(Themes::Palette::get());
    else setPalette(Themes::LightStyle().palette());
}

void DockWidget::collapse(){
    if(frame_->isHidden()){
        //setFeatures(features()^QDockWidget::DockWidgetVerticalTitleBar);
        //titlebar_->setHorizontal();
        frame_->show();
        resize(last_size);
        //titlebar_->repaint();
    }
    else{
        last_size = size();
        //setFeatures(QDockWidget::DockWidgetVerticalTitleBar | features() );
        //titlebar_->setVertical();
        frame_->hide();
        //titlebar_->repaint();
    }
}

//void DockWidget::closeEvent(QCloseEvent *event){
//    (void)event;
//    if(qobject_cast<QMainWindow*>(parentWidget())->dockWidgetArea(this)!=Qt::NoDockWidgetArea)
//        qobject_cast<QMainWindow*>(parentWidget())->removeDockWidget(this);
//}

//void DockWidget::showEvent(QShowEvent *event){
//    (void)event;
//    if(parentWidget() && qobject_cast<QMainWindow*>(parentWidget())->dockWidgetArea(this)!=Qt::LeftDockWidgetArea)
//        qobject_cast<QMainWindow*>(parentWidget())->addDockWidget(Qt::LeftDockWidgetArea,this);
//}

void DockWidget::set_model(const model::Data& data){
    if(data.var_model)
        var_list_->setModel(data.var_model.get());
}
}
