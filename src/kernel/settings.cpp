#include "kernel/settings.h"
#include "kernel/application.h"

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
    uint8_t Program::font_size_inc = 0;
    Themes::TYPE Program::style_theme = Themes::TYPE::Dark;
    QLocale::Language Program::lang_ = QLocale::Language::English;
    bool Program::var_list_showed_ = true;

    std::map<QLocale::Language,LANG_DATA> Program::langs_map=[]()->std::map<QLocale::Language,LANG_DATA>{std::map<QLocale::Language,LANG_DATA> res;
        for(auto& lang:resource_langs)
            res.insert({lang.lang_,lang});
        return res;
    }();

    void Program::set_theme(Themes::TYPE theme){
        style_theme = theme;
        qobject_cast<kernel::Application*>(QApplication::instance())->setPalette(Themes::Palette::get());
        emit qobject_cast<kernel::Application*>(kernel::Application::instance())->style_changed();
    }

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
            sets_.setValue("font_size_inc", font_size_inc);
        sets_.endGroup();
    }

    void Program::__load_settings__(){
        sets_.beginGroup("common");
            style_theme = (Themes::TYPE)sets_.value("style",Themes::Dark).value<int>();
            lang_ = (QLocale::Language)sets_.value("language",QLocale::English).value<int>();
            font_size_inc = sets_.value("font_size_inc",0).value<uint8_t>();
        sets_.endGroup();
    }

    void Program::set_language(QLocale::Language lang){
        lang_ = lang;
        emit qobject_cast<kernel::Application*>(kernel::Application::instance())->language_changed();
    }

    QLocale Program::get_language(){
        return lang_;
    }

    bool Program::variable_list_showed(){
        return Program::var_list_showed_;
    }

    void Program::set_variable_list_showed(bool b){
        Program::var_list_showed_ = b;
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
