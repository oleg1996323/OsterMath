//#include "ToolButton.h"
//#include "paths.h"

//ToolButton::ToolButton(const QString& res_path,QWidget* parent):PushButton(parent){
//    setIcon(QIcon(res_path));
//}
///*
//#include "utilities/custom_widgets/buttons.h"
//#include <QPainterPath>
//#include "styles/styles.h"
//#include "utilities/paths.h"
//#include <QStylePainter>
//#include <QStyleOptionButton>

////TODO add namespace utilities and make refactoring
////TODO make individual library for these buttons
//IconedButton::IconedButton(const QString& res_path,QWidget* parent):QPushButton(parent){
//    setIcon(QIcon(res_path));
//}
//IconedButton::IconedButton(const QIcon& icon,QWidget* parent):QPushButton(icon,"",parent){
//}
//IconedButton::IconedButton(QIcon&& icon,QWidget* parent):QPushButton(icon,"",parent){
//}
//IconedButton::IconedButton(QWidget* parent):QPushButton(parent){}
//void IconedButton::paintEvent(QPaintEvent *event){
//    QPushButton::paintEvent(event);
//}
//ToolButton::ToolButton(const QString& res_path,QWidget* parent):QPushButton(parent){
//    setContentsMargins(0,0,0,0);
//    setFixedSize(35,35);
//    QPainterPath path;
//    path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
//    setIcon(paths::iconFromPath(path,QPixmap(res_path),size(),Qt::transparent));
//    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
//}
//CloseButton::CloseButton(const QString& res_path,QWidget* parent):QPushButton(parent){
//    setContentsMargins(0,0,0,0);
//    setFixedSize(20,20);
//    QPainterPath path;
//    path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
//    setIcon(paths::iconFromPath(path,QPixmap(res_path),size(),Qt::transparent));
//    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
//}
//void CloseButton::paintEvent(QPaintEvent* event){
//    QPushButton::paintEvent(event);
//}
//CollapseButton::CollapseButton(button_states::COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent):
//MultiStateIconedButton(
//        default_val, \
//{{button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,QIcon(collapsed_icon)}, \
//{button_states::COLLAPSE_EXPAND_STATE::EXPANDED,QIcon(expanded_icon)}}, \
//        parent)
//{
//    setContentsMargins(0,0,0,0);
//    setFixedSize(20,20);
//}
//void CollapseButton::changeState(){
//    using namespace button_states;
//    switch(current_state_){
//    case(COLLAPSE_EXPAND_STATE::COLLAPSED):{
//        current_state_ = COLLAPSE_EXPAND_STATE::EXPANDED;
//        QPainterPath path;
//        path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
//        setIcon(paths::iconFromPath(path,icons_.value(COLLAPSE_EXPAND_STATE::EXPANDED),size(),Qt::transparent));
//        break;
//    }
//    case(button_states::COLLAPSE_EXPAND_STATE::EXPANDED):{
//        current_state_ = COLLAPSE_EXPAND_STATE::COLLAPSED;
//        QPainterPath path;
//        path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
//        setIcon(paths::iconFromPath(path,icons_.value(COLLAPSE_EXPAND_STATE::COLLAPSED),size(),Qt::transparent));
//        break;
//    }
//    default:
//        break;
//    }
//}
//void CollapseButton::paintEvent(QPaintEvent* event){
//    MultiStateIconedButton::paintEvent(event);
//}
// */
