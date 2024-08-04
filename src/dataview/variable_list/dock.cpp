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
#include <QPainterPath>
#include <QDebug>
#include <QStyleOptionDockWidget>
#include <QStylePainter>

namespace dataview{
DockWidget::DockWidget(QWidget* parent):QDockWidget(parent), ObjectFromSettings(this){
    setObjectName("dockwidget_var_list");
    setAutoFillBackground(true);
    titlebar_ = new TitleBar(this, Qt::Horizontal);
    QWidget* w = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(w);
    search_line_ = new SearchLine(this);
    var_list_ = new Table(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(search_line_);
    layout->addWidget(var_list_);
    this->setContentsMargins(Themes::border_round_common/2,Themes::border_round_common/2,Themes::border_round_common/2,Themes::border_round_common/2);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea);
    QSizePolicy sizepolicy;
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
    w->setSizePolicy(sizepolicy);
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    w->setLayout(layout);
    setWidget(w);
    upload_style();
    load_settings();
    retranslate();
}

void DockWidget::__retranslate__(){
    search_line_->retranslate();
    titlebar_->retranslate();
}

DockWidget::~DockWidget(){
    save_settings();
}

void DockWidget::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    if(sets_->contains("geometry"))
        restoreGeometry(sets_->value("geometry").toByteArray());
    if(sets_->value("hidden").toBool())
        collapse();
    if(sets_->contains("closed"))
        closed = sets_->value("closed").toBool();
    if(sets_->contains("floating"))
        setFloating(sets_->value("floating").toBool());
    //qDebug()<<"DockWidget init geometry"<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void DockWidget::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->setValue("hidden",!isHidden() && widget()->isHidden());
    sets_->setValue("closed",closed);
    sets_->setValue("floating", isFloating());

    //qDebug()<<"DockWidget save geometry"<<geometry();
    sets_->endGroup();
}

void DockWidget::__upload_fonts__(){

}
void DockWidget::__upload_style__(){

}
void DockWidget::__upload_language__(){

}

void DockWidget::collapse() {
    titlebar_->updateGeometry();
    if (widget()->isHidden()) {
        // Отображение виджета
        widget()->setHidden(false);
        qApp->processEvents();
        resize(dock_size_before_hidding);

        // Принудительное обновление размеров виджета и его layout

        //widget()->adjustSize();
        //widget()->updateGeometry();

//        // Принудительное обновление layout родительского виджета
//        if (widget()->layout()) {
//            widget()->layout()->invalidate();
//            widget()->layout()->activate();
//        }

        setFeatures(features() ^ QDockWidget::DockWidgetVerticalTitleBar);
        titlebar_->updateGeometry();
    } else {
        // Сохранение текущего размера перед скрытием
        dock_size_before_hidding = size();

        // Скрытие виджета
        widget()->setHidden(true);

        setFeatures(QDockWidget::DockWidgetVerticalTitleBar | features());
    }
}


bool DockWidget::closed_by_titlebar() const{
    return closed;
}

void DockWidget::close_from_titlebar(){
    closed = true;
    close();
}

void DockWidget::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
}

void DockWidget::showEvent(QShowEvent *event){
    Q_UNUSED(event);
}

void DockWidget::setData(model::Data* data){
    if(data->var_model)
        var_list_->setModel(data->var_model.get());
}

QSize DockWidget::sizeHint() const{
    if(widget()->isHidden())
        return titlebar_->size();
    else return {var_list_->width(),var_list_->height()+search_line_->height()};
}

void DockWidget::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QStylePainter p(this);
    QStyleOptionDockWidget opt;
    opt.initFrom(this);
    p.drawPrimitive(QStyle::PE_FrameDockWidget,opt);
    return;
}
}
