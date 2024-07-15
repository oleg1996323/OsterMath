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
    if(sets_->contains("winstate"))
        win_state_ = sets_->value("winstate").toByteArray();
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
    if(window_owner_)
        save_last_window_state(window_owner_->saveState());
    sets_->setValue("winstate",win_state_);
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
    return window_owner_;
}

void DockWidget::save_last_window_state(QByteArray&& state){
    win_state_ = state;
}

void DockWidget::set_window_attached(View * window){
    if (window) {
        // Сохранение состояния var_list_
        qDebug()<<"Before Dockwidget geometry attached: "<<this->geometry();
        bool floating = isFloating();
        QSize size{width(),height()};
        Qt::DockWidgetArea area;
        QByteArray state;

        QRect floatGeometry;
        if (floating) {
            floatGeometry = this->geometry();
        }

        if(window_owner_)
            win_state_ = window_owner_->saveState();

        if(win_state_.isEmpty()){
            window->addDockWidget(Qt::LeftDockWidgetArea,this);
        }
        else{
            window->restoreState(win_state_);
            window->addDockWidget(Qt::LeftDockWidgetArea,this);
            qDebug()<<this->size();
            if (floating) {
                setFloating(true);
                setGeometry(floatGeometry);
                qDebug() << "Restored floating geometry:" << this->geometry();
            }
            else resize(size);

            if(closed)
                close();
            this->setParent(window);
        }

        qDebug() << "Restored geometry:" << this->geometry();
    }
    window_owner_ = window;
    qDebug()<<"After Dockwidget geometry attached: "<<this->geometry();
}

void DockWidget::closeEvent(QCloseEvent *event){
    (void)event;
    closed = true;
//    if(window_owner_)
//        window_owner_->removeDockWidget(this);
}

void DockWidget::showEvent(QShowEvent *event){
    (void)event;
    closed = false;

//    if(window_owner_)
//        window_owner_->addDockWidget(Qt::LeftDockWidgetArea,this);
}

void DockWidget::set_model(const model::Data& data){
    if(data.var_model)
        var_list_->setModel(data.var_model.get());
}
}
