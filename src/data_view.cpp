#include "data_view.h"
#include "kernel/settings.h"

void Sheets::__load_settings__(){
    QSettings* sets_ = kernel::ProgramSettings::get_settings();
    sets_->beginGroup("sheetstab");
        this->setGeometry(sets_->value("geometry").toRect());
        Themes::TYPE theme = sets_->value("theme",Themes::Dark).value<Themes::TYPE>();
        if(theme == Themes::Dark)
            setPalette(Themes::DarkStyle().palette());
        else setPalette(Themes::LightStyle().palette());
    sets_->endGroup();
}

void Sheets::__save_settings__(){
    QSettings* sets_ = kernel::ProgramSettings::get_settings();
    sets_->beginGroup("sheetstab");
        sets_->setValue("geometry",geometry());
        Themes::TYPE theme = sets_->value("theme",Themes::Dark).value<Themes::TYPE>();
        if(theme == Themes::Dark)
            setPalette(Themes::DarkStyle().palette());
        else setPalette(Themes::LightStyle().palette());
    sets_->endGroup();
}
