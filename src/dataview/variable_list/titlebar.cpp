#include "dataview/variable_list/titlebar.h"
#include "dataview/variable_list/dock.h"
#include <QTimer>

#include <QDebug>

namespace dataview{

TitleBar::TitleBar(QWidget* parent, Qt::Orientation orientation):
    QFrame(parent),
    ObjectFromSettings(this),
    orientation_(orientation)
{
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    setPalette(Themes::Palette::get());
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
}

void TitleBar::__init__(){
    QBoxLayout* layout_=new QBoxLayout(orientation_&Qt::Horizontal?QBoxLayout::LeftToRight:QBoxLayout::BottomToTop,this);
    layout_->setSpacing(0);
    layout_->setContentsMargins(0,0,0,0);
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

}
void TitleBar::__upload_language__(){

}

void TitleBar::collapse(){
    assert(parent());
    QBoxLayout* l = qobject_cast<QBoxLayout*>(layout());
    assert(l);

    auto dir = l->direction();
    if(l->direction()==QBoxLayout::LeftToRight){
//        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);

        label_var_list->set_orientation(Qt::Vertical);
        orientation_=Qt::Vertical;
        l->setDirection(QBoxLayout::BottomToTop);
    }
    else{
//        setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
        orientation_=Qt::Horizontal;
        label_var_list->set_orientation(Qt::Horizontal);
        l->setDirection(QBoxLayout::LeftToRight);
    }
    qobject_cast<DockWidget*>(parent())->collapse();
}

TitleBarLabel::TitleBarLabel(QWidget* parent):QLabel(parent){
    setContentsMargins(0,0,0,0);
    setObjectName(QString::fromUtf8("varlisttitlebar_label"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setSizePolicy(sizePolicy);

    QFont font;
    font.setFamily("Sans");
    font.setPointSize(10);
    font.setBold(true);
    font.setWeight(100);
    setFont(font);
}

TitleBarLabel::~TitleBarLabel(){
}

void TitleBarLabel::paintEvent(QPaintEvent* event) {
    (void)event;
    QPainter painter(this);
    painter.setPen(painter.pen());
    painter.setBrush(painter.brush());

    if (orientation_ & Qt::Vertical) {
        qDebug()<<"Label geometry before"<<geometry();
        qDebug()<<"Titlebar geometry before"<<parentWidget()->geometry();
        // Поворачиваем контекст рисования на 90 градусов по часовой стрелке
        painter.setRenderHints(QPainter::TextAntialiasing);
        painter.translate(0,y()+QFontMetrics(font()).horizontalAdvance(text()));
        painter.rotate(-90);
        // Рисуем текст с учетом новой системы координат
        painter.drawText(2,0,height(),width(), alignment(), text());
        qDebug()<<"Label geometry after"<<geometry();
        qDebug()<<"Titlebar geometry after"<<parentWidget()->geometry();

    } else {
        painter.drawText(geometry(), alignment(), text());

    }
    updateGeometry();
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
        return s;
    }
    else
        return {s.height(),s.width()};
}
QSize TitleBarLabel::minimumSizeHint() const{
    QFontMetrics metrics(font());
    QSize s{metrics.size(Qt::TextSingleLine,text())};
    if(orientation_&Qt::Horizontal){
        return s;
    }
    else
        return {s.height(),s.width()};
}

//void TitleBar::Label::__load_settings__(){
//    QSettings* sets_ = kernel::settings::Program::get_settings();
//    sets_->beginGroup("varlist/dockwidget/titlebar/label");
//    setGeometry(sets_->value("geometry").toRect());
//    setVisible(!sets_->value("hidden").toBool());
//    sets_->endGroup();
//}

//void TitleBar::Label::__save_settings__(){
//    QSettings* sets_ = kernel::settings::Program::get_settings();
//    sets_->beginGroup("varlist/dockwidget/titlebar/label");
//    sets_->setValue("geometry",geometry());
//    sets_->setValue("hidden",isHidden());
//    sets_->endGroup();
//}

//void TitleBar::Label::upload_style(){
//    if(kernel::settings::Program::get_theme() == Themes::Dark)
//        setPalette(Themes::Palette::get());
//    else setPalette(Themes::LightStyle().palette());
//}
//void TitleBar::Label::upload_fonts(){

//}
//void TitleBar::Label::upload_language(){

//}
}
