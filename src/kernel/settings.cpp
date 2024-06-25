#include "kernel/settings.h"

namespace kernel{
    namespace settings{

    bool operator<(const QLocale::Language& lhs,const QLocale::Language& rhs){
        return (int)lhs<(int)rhs;
    }

    void initSettings(){
        QCoreApplication::setApplicationName("OsterMath");
        QCoreApplication::setOrganizationName("Oster-Industries");
    }

    QSettings Program::sets_ = QSettings("Oster-Industries","OsterMath");
    std::map<QLocale::Language,LANG_DATA> Program::langs_map=[]()->std::map<QLocale::Language,LANG_DATA>{std::map<QLocale::Language,LANG_DATA> res;
        for(auto& lang:resource_langs)
            res.insert({lang.lang_,lang});
        return res;
    }();
    Themes::TYPE Program::style_theme = Themes::TYPE::Light;
    QLocale::Language Program::lang_ = QLocale::Language::English;

    Themes::TYPE Program::get_theme(){
        return style_theme;
    }

    QSettings* Program::get_settings(){
        return &sets_;
    }

    const LANG_DATA& Program::get_language_properties(){
        return langs_map[lang_];
    }

    void Program::__save_settings__(){
        sets_.beginGroup("common");
            sets_.setValue("style",style_theme);
            sets_.setValue("language", lang_);
        sets_.endGroup();
    }

    void Program::__load_settings__(){
        sets_.beginGroup("common");
            style_theme = sets_.value("style",Themes::Dark).value<Themes::TYPE>();
            lang_ = sets_.value("language",QLocale::English).value<QLocale::Language>();
        sets_.endGroup();
    }

    void Program::set_language(QLocale::Language lang){
        lang_ = lang;
    }

    QLocale Program::get_language(){
        return lang_;
    }

    QSettings* Project::sets_ = nullptr;

    void Project::__open_settings__(const QString& path, QObject* parent){
        sets_ = new QSettings(path,QSettings::Format::NativeFormat,parent);
    }

    QSettings* Project::get_settings(){
        return sets_;
    }
    }
}
