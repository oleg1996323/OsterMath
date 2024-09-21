#pragma once
#include <QLabel>

class PushLabel:public QLabel{
    Q_OBJECT
public:
    PushLabel(QString text, QWidget* parent);
    PushLabel(QWidget* parent);
signals:
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
};
