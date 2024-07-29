#pragma once
#include <QGroupBox>
#include <QGridLayout>

class Group:public QGroupBox{
public:
    Group(const QString& title,QWidget* parent);
    QGridLayout* grid_layout();
private:
    QGridLayout* layout_;
};
