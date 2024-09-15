#pragma once
#include <QPushButton>
#include "aux/__borders_interface__.h"

class PushButton:public QPushButton, public oster::utilities::__interfaces__::BordersInterface{
    Q_OBJECT
public:
    PushButton(QString text,QWidget* parent):QPushButton(text,parent){}
    PushButton(QWidget* parent):QPushButton(parent){}
    PushButton(const QIcon& icon,QWidget* parent):QPushButton(icon,"",parent){}
    PushButton(const QIcon& icon,QString text,QWidget* parent):QPushButton(icon,text,parent){}
    PushButton(const QString& icon_path,QString text,QWidget* parent):QPushButton(QIcon(icon_path),text,parent){}
};

class IconedButton:public PushButton{
    Q_OBJECT
public:
    IconedButton(const QString& icon_path,QWidget* parent);
    IconedButton(const QIcon& icon,QWidget* parent);
    IconedButton(QIcon&& icon,QWidget* parent);
    IconedButton(QWidget* parent);

    void set_size(QSize);
};
