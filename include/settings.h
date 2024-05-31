#pragma once
#include <QSettings>
#include <QString>
#include <QCoreApplication>

namespace settings{
    Q_NAMESPACE
    void initSettings();

    class GlobalSettings:public QSettings{

    public:
        GlobalSettings():QSettings(QCoreApplication::organizationName(),QCoreApplication::applicationName(),nullptr){ }


    };
}
