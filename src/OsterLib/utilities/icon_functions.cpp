#include "utilities/icon_functions.h"
#include <QWidget>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QRgb>

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

QIcon iconFromPath(const QPainterPath& path, const QIcon& original, QSize size, const QColor& filling = Qt::transparent){
    QPixmap pixmap(size);
    pixmap.fill(filling);
    QPainter painter(&pixmap);
    painter.setClipPath(path);
    qDebug()<<original.availableSizes(QIcon::Active);
    painter.fillRect(pixmap.rect(),filling);
    if (!original.isNull()) {
        painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки
        painter.drawPixmap(0, 0, size.width(), size.height(), original.pixmap(size));
    }
    return QIcon(pixmap);
}

QIcon iconFromPath(const QPainterPath& path, const QPixmap& original, QSize size, const QColor& filling = Qt::transparent){
    QPixmap pixmap(size);
    pixmap.fill(filling);
    QPainter painter(&pixmap);
    painter.setClipPath(path);
    painter.fillRect(pixmap.rect(),filling);
    if (!original.isNull()) {
        painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки
        painter.drawPixmap(QRect(0, 0, size.width(), size.height()), original, original.rect());
    }
    QIcon icon;
    icon.addPixmap(pixmap);
    qDebug()<<icon.actualSize(size);
    return icon;
}
