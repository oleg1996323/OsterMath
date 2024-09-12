#include "PushButton.h"

IconedButton::IconedButton(const QString& res_path,QWidget* parent):PushButton(parent){
    setIcon(QIcon(res_path));
}
IconedButton::IconedButton(const QIcon& icon,QWidget* parent):PushButton(icon,"",parent){
}
IconedButton::IconedButton(QIcon&& icon,QWidget* parent):PushButton(icon,"",parent){
}
IconedButton::IconedButton(QWidget* parent):PushButton(parent){}
void IconedButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
}
