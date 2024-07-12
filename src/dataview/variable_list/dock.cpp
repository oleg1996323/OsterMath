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
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    QVBoxLayout* layout = new QVBoxLayout(this);
    frame_ = new Frame(this);
    layout->addWidget(frame_);
    var_list_ = new Table(this);
    layout->addWidget(var_list_);
    this->setLayout(layout);
    retranslate();
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
    restoreGeometry(sets_->value("geometry").toByteArray());
    setVisible(!sets_->value("hidden").toBool());
    setFloating(sets_->value("floating").toBool());
    qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}

void DockWidget::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->setValue("hidden",isHidden());
    sets_->setValue("floating", isFloating());
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



void DockWidget::set_window_attached(QMainWindow * window){
    if (window) {
        // Сохранение состояния var_list_
        QByteArray geometry = saveGeometry();
        bool floating = isFloating();
        Qt::DockWidgetArea area;
        QByteArray state;
        QRect floatGeometry;
        if (floating) {
            floatGeometry = this->geometry();
        }

        // Отсоединяем var_list_ от текущего виджета
        if(window_owner_){
            state = window_owner_->saveState();
            area = window_owner_->dockWidgetArea(this);
            window_owner_->removeDockWidget(this);
            window->restoreDockWidget(this);
        }
        else {
            window->restoreDockWidget(this);
        }

        // Восстанавливаем состояние и геометрию var_list_ после полной инициализации
        QTimer::singleShot(0, [this, window,area, state, geometry, floating, floatGeometry]() {
            bool restoreGeometrySuccess = restoreGeometry(geometry);
            qDebug() << "Restore geometry success:" << restoreGeometrySuccess;

            if (floating) {
                setFloating(true);
                setGeometry(floatGeometry);
                qDebug() << "Restored floating geometry:" << this->geometry();
            }

            if(window_owner_)
                window->restoreState(state);
        });
        //bool restoreStateSuccess = tab_window->restoreState(state);
        //qDebug() << "Restore state success:" << restoreStateSuccess;
    }
    window_owner_ = window;
}

void DockWidget::closeEvent(QCloseEvent *event){
    (void)event;
    if(window_owner_ && window_owner_->dockWidgetArea(this)!=Qt::NoDockWidgetArea)
        window_owner_->removeDockWidget(this);
}

void DockWidget::showEvent(QShowEvent *event){
    (void)event;
    if(window_owner_ && window_owner_->dockWidgetArea(this)!=Qt::LeftDockWidgetArea)
        window_owner_->addDockWidget(Qt::LeftDockWidgetArea,this);
}

void DockWidget::set_model(const model::Data& data){
    if(data.var_model)
        var_list_->setModel(data.var_model.get());
}
}
