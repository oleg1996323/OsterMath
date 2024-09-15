#include "kernel/def.h"
#include "kernel/application.h"

ObjectFromSettings::ObjectFromSettings(QObject* object){
    kernel::Application* app = qobject_cast<kernel::Application*>(kernel::Application::instance());
    object->connect(app, &kernel::Application::language_changed, [this](){
        upload_language();
    });
    object->connect(app, &kernel::Application::font_inc_changed, [this](){
        upload_fonts();
    });
    object->connect(app, &kernel::Application::style_changed, [this](){
        upload_style();
    });
}

void ObjectFromSettings::upload_fonts(){
    __upload_fonts__();
}
void ObjectFromSettings::upload_style(){
    __upload_style__();
}
void ObjectFromSettings::upload_language(){
    __upload_language__();
}
void ObjectFromSettings::load_settings(){
    __load_settings__();
}
void ObjectFromSettings::save_settings(){
    __save_settings__();
}

void Retranslatable::retranslate(){
    __retranslate__();
}
