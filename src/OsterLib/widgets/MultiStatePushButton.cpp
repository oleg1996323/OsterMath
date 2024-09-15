#include "MultiStatePushButton.h"
#include "styles.h"
#include "icon_functions.h"
#include <QMouseEvent>
#include <QEvent>
#include <QPainterPath>

CollapseButton::CollapseButton(CollapseButtonState default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent):
MultiStateIconedButton(
        default_val, \
{{CollapseButtonState::COLLAPSED,QIcon(collapsed_icon)}, \
{CollapseButtonState::EXPANDED,QIcon(expanded_icon)}}, \
        parent)
{
    setContentsMargins(0,0,0,0);
}
void CollapseButton::changeState(){
    switch(current_state_){
    case(CollapseButtonState::COLLAPSED):{
        current_state_ = CollapseButtonState::EXPANDED;
        setIcon(icons_.value(CollapseButtonState::EXPANDED)); //TODO add to style definition (repaint)
        break;
    }
    case(CollapseButtonState::EXPANDED):{
        current_state_ = CollapseButtonState::COLLAPSED;
        setIcon(icons_.value(CollapseButtonState::COLLAPSED)); //TODO add to style definition (repaint)
        break;
    }
    default:
        break;
    }
}
void CollapseButton::paintEvent(QPaintEvent* event){
    MultiStateIconedButton::paintEvent(event);
}
