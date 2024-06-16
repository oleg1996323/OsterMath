#include "kernel/settings.h"

namespace settings{

void initSettings(){
    QCoreApplication::setApplicationName("OsterMath");
    QCoreApplication::setOrganizationName("Oster-Industries");
}
}

namespace kernel{
QSettings* ProgramSettings::sets_ = nullptr;
Themes::TYPE ProgramSettings::style_theme = Themes::TYPE::Light;

Themes::TYPE ProgramSettings::get_theme(){
    return style_theme;
}

QSettings* ProgramSettings::get_settings(){
    return sets_;
}

void ProgramSettings::__save_settings__(){
    sets_->beginGroup("global");
        sets_->setValue("theme",style_theme);
    sets_->endGroup();
}

void ProgramSettings::__load_settings__(){
    sets_->beginGroup("global");
        style_theme = sets_->value("theme",Themes::Dark).value<Themes::TYPE>();
    sets_->endGroup();
}

QSettings* ProjectSettings::sets_;

void ProjectSettings::__open_settings__(const QString& path, QObject* parent){
    sets_ = new QSettings(path,QSettings::Format::NativeFormat,parent);
}

QSettings* ProjectSettings::get_settings(){
    return sets_;
}
}
