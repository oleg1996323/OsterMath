#include "utilities/custom_widgets/buttons.h"

IconedButton::IconedButton(const QString& res_path,QWidget* parent):QPushButton(parent){
    setIcon(QIcon(res_path));
}

IconedButton::IconedButton(const QIcon& icon,QWidget* parent):QPushButton(parent){
    setIcon(icon);
}

IconedButton::IconedButton(QIcon&& icon,QWidget* parent):QPushButton(icon,"",parent){
    setIcon(icon);
}

IconedButton::IconedButton(QWidget* parent):QPushButton(parent){}

void IconedButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event); // Вызываем реализацию по умолчанию для отображения фона и текста
    QPainter painter(this);
    if (!icon().isNull()) {
        painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки
        setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
    }
}

ToolButton::ToolButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){
    setContentsMargins(0,0,0,0);
    setFixedSize(35,35);
}

CloseButton::CloseButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){
    setContentsMargins(0,0,0,0);
    setFixedSize(20,20);
}

CollapseButton::CollapseButton(button_states::COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent):
MultiStateIconedButton(
        default_val, \
{{button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,collapsed_icon}, \
{button_states::COLLAPSE_EXPAND_STATE::EXPANDED,expanded_icon}}, \
        parent)
{
    setContentsMargins(0,0,0,0);
    setFixedSize(20,20);
}

void CollapseButton::changeState(){
    using namespace button_states;
    switch(current_state_){
    case(COLLAPSE_EXPAND_STATE::COLLAPSED):
        current_state_ = COLLAPSE_EXPAND_STATE::EXPANDED;
        setIcon(icons_.value(COLLAPSE_EXPAND_STATE::EXPANDED));
        break;
    case(button_states::COLLAPSE_EXPAND_STATE::EXPANDED):
        current_state_ = COLLAPSE_EXPAND_STATE::COLLAPSED;
        setIcon(icons_.value(COLLAPSE_EXPAND_STATE::COLLAPSED));
        break;
    default:
        break;
    }
}
