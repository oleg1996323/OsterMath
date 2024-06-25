#include "kernel/def.h"

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
