#include "PushButton.h"
#include "styles.h"
#include "icon_functions.h"
#include <QPainterPath>

IconedButton::IconedButton(const QString& icon_path,QWidget* parent):PushButton(QIcon(icon_path),parent){
    setContentsMargins(0,0,0,0);
}
IconedButton::IconedButton(const QIcon& icon,QWidget* parent):PushButton(icon,"",parent){
}
IconedButton::IconedButton(QIcon&& icon,QWidget* parent):PushButton(icon,"",parent){
}
IconedButton::IconedButton(QWidget* parent):PushButton(parent){}

void IconedButton::set_size(QSize size){
    setFixedSize(size);
    setIconSize(size);
}
