#pragma once
#include <QSettings>
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include "styles.h"

namespace kernel{
    Q_NAMESPACE
    class ProgramSettings{
        static QSettings* sets_;
        static Themes::TYPE style_theme;
    public:
        static Themes::TYPE get_theme(){
            return style_theme;
        }

        static QSettings* get_settings(){
            return sets_;
        }

        static void __save_settings__(){
            sets_->beginGroup("global");
                sets_->setValue("theme",style_theme);
            sets_->endGroup();
        }

        static void __load_settings__(){
            sets_->beginGroup("global");
                style_theme = sets_->value("theme",Themes::Dark).value<Themes::TYPE>();
            sets_->endGroup();
        }
    };

    class ProjectSettings{
        static QSettings* sets_;
    public:
        static void __open_settings__(const QString& path, QObject* parent){
            sets_ = new QSettings(path,QSettings::Format::NativeFormat,parent);
        }

        static QSettings* get_settings(){
            return sets_;
        }

    };
}
