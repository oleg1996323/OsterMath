#include <QSettings>
#include <QString>

class UserSettings:public QSettings{
    UserSettings(QObject* parent,const QString& organization):QSettings(QSettings::UserScope,organization,"OsterMath",parent){

    }
};

class GlobalSettings:public QSettings{
    GlobalSettings(QObject* parent,const QString& organization):QSettings(QSettings::SystemScope,organization,"OsterMath",parent){

    }
};
