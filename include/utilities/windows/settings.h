#pragma once
#include <QComboBox>
#include <QAction>
#include "kernel/settings.h"

class Settings:public QObject{
    Q_OBJECT
public:
    Settings(QWidget* parent){
//        setObjectName("main_settings_window");
//        langs_ = new QComboBox(this);
//        QAction* rus_ = QAction("Русский",langs_);

//        langs_->addAction();
    }

private:
    QComboBox* langs_;

};
