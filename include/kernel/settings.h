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
        static Themes::TYPE get_theme();

        static QSettings* get_settings();

        static void __save_settings__();

        static void __load_settings__();
    };

    class ProjectSettings{
        static QSettings* sets_;
    public:
        static void __open_settings__(const QString& path, QObject* parent);

        static QSettings* get_settings();

    };
}
