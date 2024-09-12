#pragma once
#include <QPushButton>
#include "__borders_interface__.h"

class PushButton:public QPushButton, public oster::utilities::__interfaces__::BordersInterface{
    Q_OBJECT
public:
    PushButton(QString text,QWidget* parent):QPushButton(text,parent){}
    PushButton(QWidget* parent):QPushButton(parent){}
};

class CloseButton:public PushButton{
    Q_OBJECT
public:
    CloseButton(const QString& res_path,QWidget* parent);
    virtual void paintEvent(QPaintEvent*) override;
};

class IconedButton:public PushButton{
    Q_OBJECT
public:
    IconedButton(const QString& res_path,QWidget* parent);
    IconedButton(const QIcon& icon,QWidget* parent);
    IconedButton(QIcon&& icon,QWidget* parent);
    IconedButton(QWidget* parent);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    bool icon_set_ = false;
};
