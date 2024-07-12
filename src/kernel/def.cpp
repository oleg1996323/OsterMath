#include "kernel/def.h"
#include "kernel/application.h"

QWidget* findParent(QWidget* widget, QString name)
{
    widget = widget->parentWidget();
    if (widget && widget->objectName() != name)
        return findParent(widget, name);
    return widget;
}

QIcon negativeIcon(const QIcon &icon) {
    QPixmap pixmap = icon.pixmap(icon.availableSizes().first());
    QImage image = pixmap.toImage();

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb color = image.pixel(x, y);
            image.setPixel(x, y, qRgb(255 - qRed(color), 255 - qGreen(color), 255 - qBlue(color)));
        }
    }

    return QIcon(QPixmap::fromImage(image));
}

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

void ObjectFromSettings::load_settings(){
    __load_settings__();
}
void ObjectFromSettings::save_settings(){
    __save_settings__();
}
