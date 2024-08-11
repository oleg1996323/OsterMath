#include "dataview/variable_list/titlebar.h"
#include "dataview/variable_list/dock.h"
#include <QTimer>
#include <utilities/paths.h>
#include <QStylePainter>

#include <QDebug>

namespace dataview{

TitleBar::TitleBar(QWidget* parent, Qt::Orientation orientation):
    QWidget(parent),
    ObjectFromSettings(this),
    orientation_(orientation)
{
    setContentsMargins(0,0,0,0);
    label_var_list = new TitleBarLabel(this);
    collapse_var_list = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::EXPANDED,
                                           ":common/common/expand.png",
                                            ":common/common/collapse.png",
                                            this);
    collapse_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_collapse"));
    close_var_list = new CloseButton(":common/common/close.png",this);
    close_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_close"));
    connect(close_var_list,&CloseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::close_from_titlebar);
    connect(collapse_var_list,&CollapseButton::clicked,this,&TitleBar::collapse);
    __init__();
    retranslate();
}

void TitleBar::__init__(){
    QBoxLayout* layout_=new QBoxLayout(orientation_&Qt::Horizontal?QBoxLayout::LeftToRight:QBoxLayout::BottomToTop,this);
    layout_->setContentsMargins(Themes::frame_line_width_back/2,Themes::frame_line_width_back/2,Themes::frame_line_width_back/2,Themes::frame_line_width_back/2);
    layout_->setAlignment(Qt::AlignVCenter);
    layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
    layout_->addWidget(label_var_list);
    layout_->setSpacing(2);
    label_var_list->set_orientation(orientation_);
    layout_->addWidget(collapse_var_list);
    layout_->addWidget(close_var_list);

    setLayout(layout_);
}

void TitleBar::__retranslate__(){
    label_var_list->setText(QCoreApplication::translate("Form", "Variables", nullptr));
}

void TitleBar::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->endGroup();
}
void TitleBar::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->endGroup();
}
void TitleBar::__upload_fonts__(){

}
void TitleBar::__upload_style__(){
    repaint();
}
void TitleBar::__upload_language__(){
    retranslate();
}

void TitleBar::collapse(){
    assert(parent());
    QBoxLayout* l = qobject_cast<QBoxLayout*>(layout());
    assert(l);
    if(l->direction()==QBoxLayout::LeftToRight){
        orientation_=Qt::Vertical;
        label_var_list->set_orientation(Qt::Vertical);
        l->setDirection(QBoxLayout::BottomToTop);
    }
    else{
        orientation_=Qt::Horizontal;
        label_var_list->set_orientation(Qt::Horizontal);
        l->setDirection(QBoxLayout::LeftToRight); 
    }
    qobject_cast<DockWidget*>(parent())->collapse();
    label_var_list->updateGeometry();

}

void TitleBar::paintEvent(QPaintEvent* event){
    QStylePainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    p.drawControl(QStyle::CE_DockWidgetTitle,opt);
}

QSize TitleBar::sizeHint() const{
//    int max_height = 0;
//    for(QObject* child:children()){
//        QWidget* child_widget = qobject_cast<QWidget*>(child);
//        if(child_widget){
//            max_height = qMax(max_height,child_widget->sizeHint().height());
//        }
//    }
//    if(max_height==0){
//        if(orientation_&Qt::Horizontal)
//            return QSize(width(),height()-contentsMargins().top()-contentsMargins().bottom());
//        else return QSize(height(),width());
//    }
//    else {
//        QSize s = {width(),max_height};
//        if(orientation_&Qt::Horizontal)
//            return QSize(width(),max_height);
//        else return QSize(max_height,width());
//    }
    return QWidget::sizeHint();
}

TitleBarLabel::TitleBarLabel(QWidget* parent):QLabel(parent){
    setContentsMargins(0,0,0,0);
    setBackgroundRole(QPalette::Window);
    setObjectName(QString::fromUtf8("varlisttitlebar_label"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setSizePolicy(sizePolicy);

    QFont font;
    font.setFamily("Sans");
    font.setPointSize(10);
    font.setWeight(QFont::DemiBold);
    setFont(font);
}

TitleBarLabel::~TitleBarLabel(){
}

void TitleBarLabel::paintEvent(QPaintEvent* event) {
    (void)event;
    QPainter painter(this);
    painter.save();
    if (orientation_ & Qt::Vertical) {
        painter.setRenderHints(QPainter::TextAntialiasing);
        painter.translate(0,height()-qobject_cast<QWidget*>(parent())->layout()->contentsMargins().bottom());
        painter.rotate(-90);
        const QTransform& tr = painter.transform();
        auto x = tr.dx();
        auto y = tr.dy();
        QRect g = geometry();
        painter.drawText(QRect(0,0,height(),width()), alignment(), text());

    } else {
        painter.setRenderHints(QPainter::TextAntialiasing);
        painter.drawText(geometry(), alignment(), text());
    }
    painter.restore();
}


void TitleBarLabel::TitleBarLabel::set_orientation(Qt::Orientation orientation){
    if(orientation_ ^ orientation){
        orientation_=orientation;
    }
}

QSize TitleBarLabel::sizeHint() const{
    QFontMetrics metrics(font());
    QSize s{metrics.size(Qt::TextSingleLine,text())};
    if(orientation_&Qt::Horizontal){
        return {s.width()+separation_between_btns_and_label_,s.height()};
    }
    else
        return {s.height(),s.width()+separation_between_btns_and_label_};
    return {width(),height()};
    //return QLabel::sizeHint();
}
QSize TitleBarLabel::minimumSizeHint() const{
    QFontMetrics metrics(font());
    QSize s{metrics.size(Qt::TextSingleLine,text())};
    if(orientation_&Qt::Horizontal){
        return {s.width()+separation_between_btns_and_label_,s.height()};
    }
    else
        return {s.height(),s.width()+separation_between_btns_and_label_};
}

bool TitleBar::event(QEvent* event){
    switch(event->type()){
    case QEvent::Polish:{
        setAttribute(Qt::WA_Hover,true);
    }
    default:{
        QWidget::event(event);
    }
    }
}
}
