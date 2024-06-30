#pragma once
#include <QSettings>
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include <QTranslator>
#include <QLocale>
#include <map>
#include <array>
#include "styles.h"

namespace kernel{
    namespace settings{

    struct LANG_DATA{
        const char* path;
        const char* text;
        QLocale::Language lang_;
        bool operator<(const LANG_DATA& other){
            return (int)lang_<(int)other.lang_;
        }
    };

    constexpr std::array<LANG_DATA, 2> resource_langs = {
        ":lang_icon/rus","Русский", QLocale::Russian,
        ":lang_icon/eng","English", QLocale::English
    };

        class Program{
            static QSettings sets_;
            static std::map<QLocale::Language,LANG_DATA> langs_map;
            static Themes::TYPE style_theme;
            static QLocale::Language lang_;
            static uint8_t font_size_inc;
        public:
            static void init_settings();

            static Themes::TYPE get_theme();

            static QSettings* get_settings();

            static void set_language(QLocale::Language);

            static QLocale get_language();

            static const LANG_DATA& get_language_properties();

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
