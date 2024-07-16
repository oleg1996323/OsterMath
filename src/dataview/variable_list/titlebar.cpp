#include "dataview/variable_list/titlebar.h"
#include "dataview/variable_list/dock.h"

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
    layout_->setSizeConstraint(QLayout::SetMinimumSize);

    layout_->addWidget(label_var_list,Qt::AlignLeft);
    label_var_list->set_orientation(orientation_);
    QSpacerItem *spacer = new QSpacerItem(20, 20,QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout_->addSpacerItem(spacer);
    layout_->addWidget(collapse_var_list,Qt::AlignRight);
    layout_->addWidget(close_var_list,Qt::AlignRight);

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
    qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void TitleBar::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
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
        orientation_=Qt::Vertical;
        l->setDirection(QBoxLayout::BottomToTop);
        label_var_list->set_orientation(Qt::Vertical);
    }
    else{
        l->setDirection(QBoxLayout::LeftToRight);
        orientation_=Qt::Horizontal;
        label_var_list->set_orientation(Qt::Horizontal);
    }
    qobject_cast<DockWidget*>(parent())->collapse();
}

TitleBarLabel::TitleBarLabel(QWidget* parent):QLabel(parent){
    setContentsMargins(0,0,0,0);
    setObjectName(QString::fromUtf8("varlisttitlebar_label"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setSizePolicy(sizePolicy);
    setMaximumSize(QSize(2000, 20));
    QFont font;
    font.setFamily("Sans");
    font.setPointSize(10);
    font.setBold(true);
    font.setWeight(100);
    setFont(font);
}

TitleBarLabel::~TitleBarLabel(){
}

void TitleBarLabel::TitleBarLabel::paintEvent(QPaintEvent* event){
    (void)event;
    QPainter painter(this);
    painter.setPen(painter.pen());
    painter.setBrush(painter.brush());
    painter.setFont(this->font());
    if(orientation_&Qt::Vertical){
        painter.rotate(90);
        painter.drawText(width()/2,height(), text()); //incorrect point
    }
    else{
        painter.drawText(0,this->height()/2, text()); //incorrect point
    }

}

void TitleBarLabel::TitleBarLabel::set_orientation(Qt::Orientation orientation){
    if(orientation_ ^ orientation){
        orientation_=orientation;
    }
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
