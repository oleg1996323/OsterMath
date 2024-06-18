#pragma once
#include <QSettings>
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include <QTranslator>
#include <QLocale>
#include <array>
#include "styles.h"

namespace kernel{
    namespace settings{

    struct LANG_DATA{
        const char* path;
        const char* text;
        QLocale::Language lang_;
    };

    constexpr std::array<LANG_DATA, 2> resource_langs = {
        ":lang_icon/rus","Русский",QLocale::Russian,
        ":lang_icon/eng","English",QLocale::English
    };

        class Program{
            static QSettings sets_;
            static Themes::TYPE style_theme;
            static QLocale::Language lang_;
        public:
            static Themes::TYPE get_theme();

            static QString get_lang_resource_path();

            static QSettings* get_settings();

            static void set_language(QLocale::Language);

            static void __save_settings__();

            static void __load_settings__();
        };

        class Project{
            static QSettings* sets_;
        public:
            static void __open_settings__(const QString& path, QObject* parent);

            static QSettings* get_settings();

        };
    }
}
