#include "MultiStatePushButton.h"
#include "styles/styles.h"
#include <QMouseEvent>
#include <QEvent>
#include <QPainterPath>

CollapseButton::CollapseButton(COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent):
MultiStateIconedButton(
        default_val, \
{{COLLAPSE_EXPAND_STATE::COLLAPSED,QIcon(collapsed_icon)}, \
{COLLAPSE_EXPAND_STATE::EXPANDED,QIcon(expanded_icon)}}, \
        parent)
{
    setContentsMargins(0,0,0,0);
    setFixedSize(20,20);
}
void CollapseButton::changeState(){
    switch(current_state_){
    case(COLLAPSE_EXPAND_STATE::COLLAPSED):{
        current_state_ = COLLAPSE_EXPAND_STATE::EXPANDED;
        QPainterPath path;
        path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
        setIcon(paths::iconFromPath(path,icons_.value(COLLAPSE_EXPAND_STATE::EXPANDED),size(),Qt::transparent)); //TODO add to style definition (repaint)
        break;
    }
    case(COLLAPSE_EXPAND_STATE::EXPANDED):{
        current_state_ = COLLAPSE_EXPAND_STATE::COLLAPSED;
        QPainterPath path;
        path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
        setIcon(paths::iconFromPath(path,icons_.value(COLLAPSE_EXPAND_STATE::COLLAPSED),size(),Qt::transparent)); //TODO add to style definition (repaint)
        break;
    }
    default:
        break;
    }
}
void CollapseButton::paintEvent(QPaintEvent* event){
    MultiStateIconedButton::paintEvent(event);
}
