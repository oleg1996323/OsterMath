#include <QSettings>
#include <QString>

class UserSettings:public QSettings{
    UserSettings(QWidget* parent,const QString& organization):QSettings(QSettings::UserScope,organization,"OsterMath",parent){

    }
};

class GlobalSettings:public QSettings{
    GlobalSettings(QWidget* parent,const QString& organization):QSettings(QSettings::SystemScope,organization,"OsterMath",parent){

    }
};
