#include "dataview/expr_view_splitter.h"
#include "QStylePainter"
#include <QPainterPath>

namespace dataview{

void SplitterHandle::set_effects(OverlayHandleVisualEffect* effects){
    effects_.reset(effects);
}

OverlayHandleVisualEffect::OverlayHandleVisualEffect(QWidget* parent_drawed_on, QWidget* eff_parent, QSize size, Qt::Orientation orientation):
    QWidget(parent_drawed_on),
    orientation_(orientation),
    effect_parent(eff_parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setFixedSize(size);
    setHidden(true);
}

void OverlayHandleVisualEffect::paintEvent(QPaintEvent *event){
    if(!isHidden()){
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.save();
        QLinearGradient grad;
        QColor color = kernel::settings::Program::get_theme()&Themes::Dark?palette().midlight().color():palette().dark().color();
        grad.setColorAt(0,color);
        color.setAlpha(125);
        grad.setColorAt(0.5,color);
        grad.setColorAt(1,Qt::transparent);
        if(orientation_&Qt::Horizontal){
            grad.setStart(0,height());
            grad.setFinalStop(width(),height());
        }
        else{
            grad.setStart(width(),0);
            grad.setFinalStop(width(),height());
        }
        p.fillRect(QRect(0,0,width(),height()),grad);
        p.restore();
    }
}

void SplitterHandle::moveEvent(QMoveEvent* event){
    QSplitterHandle::moveEvent(event);
    if(effects_){
        effects_->move(geometry().bottomLeft());
    }
}

void SplitterHandle::paintEvent(QPaintEvent* event){
    QSplitterHandle::paintEvent(event);
}

void SplitterHandle::enterEvent(QEnterEvent* event){
    Q_UNUSED(event);
    if(effects_)
        effects_->setHidden(false);
}

void SplitterHandle::leaveEvent(QEvent* event){
    Q_UNUSED(event);
    if(effects_)
        effects_->setHidden(true);
}

void SplitterHandle::showEvent(QShowEvent* event){
    QSplitterHandle::showEvent(event);
    raise();
}

void SplitterHandle::resizeEvent(QResizeEvent* event){
    QSplitterHandle::resizeEvent(event);
    if(effects_){
        if(effects_->orientation()&Qt::Horizontal)
            effects_->setFixedSize(width()*5,height());
        else effects_->setFixedSize(width(),height()*5);
    }
}

DataViewSplit::DataViewSplit(QWidget* parent):
    QSplitter(Qt::Vertical,parent),
    ObjectFromSettings(this){
    setObjectName("MainDataView");
    __define_view__();
}

void DataViewSplit::__define_view__(){
    expression_view_ = new VarExpressionView(this);
    sheets_ = new Sheets(this);
    addWidget(expression_view_);
    addWidget(sheets_);
    setCollapsible(0,false);
    setCollapsible(1,false);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setSizes({20,sheets_->maximumHeight()});
}

Sheets* DataViewSplit::sheets() const{
    return sheets_;
}

void DataViewSplit::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
}
void DataViewSplit::__save_settings__(){

}
void DataViewSplit::__upload_fonts__(){

}
void DataViewSplit::__upload_style__(){

}
void DataViewSplit::__upload_language__(){

}
QSplitterHandle* DataViewSplit::createHandle(){
    return new SplitterHandle(orientation(),this);
}

void DataViewSplit::paintEvent(QPaintEvent *event){
    QSplitter::paintEvent(event);
//    foreach (QObject* obj, children()) {
//    SplitterHandle* handle = qobject_cast<SplitterHandle*>(obj);
//        if (handle && handle->hovered()) {
//            QPainter p(this);
//            p.setRenderHint(QPainter::Antialiasing);
//            QStyleOption opt;
//            opt.initFrom(handle);
//            p.save();
//            QLinearGradient grad;
//            grad.setColorAt(0,Qt::transparent);
//            QColor color = kernel::settings::Program::get_theme()&Themes::Dark?palette().light().color():palette().dark().color();
//            grad.setColorAt(0.5,color);
//            color.setAlpha(255);
//            grad.setColorAt(0.2,color);
//            grad.setColorAt(0.8,color);
//            grad.setColorAt(1,Qt::transparent);
//            if(orientation()&Qt::Horizontal){
//                grad.setStart(-handle->width(),handle->height()/2);
//                grad.setFinalStop(handle->width(),handle->height()/2);
//                p.fillRect(QRect(0,0,handle->width(),handle->height()),grad);
//            }
//            else{
//                grad.setStart(handle->width()/2+handle->x(),-handle->height()*10+handle->y());
//                grad.setFinalStop(handle->width()/2+handle->x(),handle->height()*10+handle->y());
//                QRect rect = QRect(handle->x(),-handle->height()*10+handle->y(),handle->width()+handle->x(),handle->height()*20+handle->y());
//                p.fillRect(rect,grad);
//            }
//            p.restore();
//        }
//    }
}
}
