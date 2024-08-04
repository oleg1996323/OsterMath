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
    label_var_list = new TitleBarLabel(this);
    collapse_var_list = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::EXPANDED,
                                           ":common/common/expand.png",
                                            ":common/common/collapse.png",
                                            this);
    collapse_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_collapse"));

    if(!qobject_cast<QPushButton*>(collapse_var_list))
        assert(false);

    close_var_list = new CloseButton(":common/common/close.png",this);
    close_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_close"));
    connect(close_var_list,&CloseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::close_from_titlebar);
    connect(collapse_var_list,&CollapseButton::clicked,this,&TitleBar::collapse);
    __init__();
}

void TitleBar::__init__(){
    QBoxLayout* layout_=new QBoxLayout(orientation_&Qt::Horizontal?QBoxLayout::LeftToRight:QBoxLayout::BottomToTop,this);
    layout_->setSpacing(0);
    layout_->setContentsMargins(Themes::frame_line_width_back,0,Themes::frame_line_width_back,0);
    layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));

    layout_->addWidget(label_var_list);
    label_var_list->set_orientation(orientation_);
    layout_->addWidget(collapse_var_list);
    layout_->addWidget(close_var_list);

    setLayout(layout_);
}

void TitleBar::__retranslate__(){
    label_var_list->setText(QCoreApplication::translate("Form", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
    collapse_var_list->setText(QString());
    close_var_list->setText(QString());
}

void TitleBar::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void TitleBar::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    //sets_->setValue("geometry",saveGeometry());
    sets_->endGroup();
}
void TitleBar::__upload_fonts__(){

}
void TitleBar::__upload_style__(){
    repaint();
}
void TitleBar::__upload_language__(){

}

void TitleBar::collapse(){
    assert(parent());
    QBoxLayout* l = qobject_cast<QBoxLayout*>(layout());
    assert(l);

    if(l->direction()==QBoxLayout::LeftToRight){
        label_var_list->set_orientation(Qt::Vertical);
        orientation_=Qt::Vertical;
        l->setDirection(QBoxLayout::BottomToTop);
        label_var_list->updateGeometry();
    }
    else{
        orientation_=Qt::Horizontal;
        label_var_list->set_orientation(Qt::Horizontal);
        l->setDirection(QBoxLayout::LeftToRight);
        label_var_list->updateGeometry();
    }
    qobject_cast<DockWidget*>(parent())->collapse();
}

void TitleBar::paintEvent(QPaintEvent* event){
//    Q_UNUSED(event);
//    QPainter painter(this);
//    QRect adjusted = rect().adjusted(1,1,-1,-1);
//    QPainterPath path;
//    painter.save();
//    QBoxLayout* l = qobject_cast<QBoxLayout*>(layout());
//    if(l->direction()==QBoxLayout::LeftToRight)
//        path = paths::semiRoundedRect(paths::TOP, adjusted,Themes::border_round_common);
//    else path = paths::semiRoundedRect(paths::LEFT,adjusted,Themes::border_round_common);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setClipPath(path);
//    QPen middle = QPen(palette().dark().color());
//    QPen back = QPen(palette().light().color());
//    middle.setWidth(Themes::frame_line_width_mid);
//    back.setWidth(Themes::frame_line_width_back);
//    painter.fillPath(path,palette().window());
//    painter.setPen(back);
//    painter.drawPath(path);
//    painter.setPen(middle);
//    painter.drawPath(path);
//    painter.restore();
    QStylePainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    p.drawControl(QStyle::CE_DockWidgetTitle,opt);
}

QSize TitleBar::sizeHint() const{
    int max_height = 0;
    for(QObject* child:children()){
        QWidget* child_widget = qobject_cast<QWidget*>(child);
        if(child_widget){
            max_height = qMax(max_height,child_widget->sizeHint().height());
        }
    }
    if(max_height!=0)
        return QSize(width()+Themes::frame_line_width_back,max_height+Themes::frame_line_width_back);
    else return QSize(width()+Themes::frame_line_width_back,height()+Themes::frame_line_width_back);
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
    qDebug()<<palette().text().color();
    if (orientation_ & Qt::Vertical) {
        qDebug()<<"Label geometry before"<<geometry();
        qDebug()<<"Titlebar geometry before"<<parentWidget()->geometry();
        // Поворачиваем контекст рисования на 90 градусов по часовой стрелке
        painter.setRenderHints(QPainter::TextAntialiasing);
        painter.translate(0,QFontMetrics(font()).horizontalAdvance(text())+20);
        painter.rotate(-90);
        // Рисуем текст с учетом новой системы координат
        painter.drawText(0,0,height(),width(), alignment(), text());
        qDebug()<<"Label geometry after"<<geometry();
        qDebug()<<"Titlebar geometry after"<<parentWidget()->geometry();

    } else {
        QRect geom(0,0,width(),height());
        painter.drawText(geom, alignment(), text());
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
        return {s.width()+separation_between_btns_and_label_+Themes::frame_line_width_back*2,s.height()+Themes::frame_line_width_back*2};
    }
    else
        return {s.height()+Themes::frame_line_width_back*2,s.width()+separation_between_btns_and_label_+Themes::frame_line_width_back*2};
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
}
