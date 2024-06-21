#pragma once
#include <QComboBox>
#include <QAction>
#include <QGridLayout>
#include "windef.h"
#include "kernel/settings.h"
#include "utilities/layouts/primitive_layouts.h"

class Settings:public QMainWindow,public AbstractSubWindowInterface{
    Q_OBJECT
public:
    Settings(QWidget* parent):QMainWindow(parent,Qt::Dialog){
        layout_ = new QGridLayout(this);

        layout_->addLayout(new layouts::LanguageChoose(this),1,1,1,1,Qt::AlignLeft);
        this->setLayout(layout_);
    }

private:
    QComboBox* langs_;
    QGridLayout* layout_;
};
