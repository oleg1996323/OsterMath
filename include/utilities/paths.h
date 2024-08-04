#pragma once
#include <QPainterPath>
#include <QIcon>

namespace paths{

enum RectSide{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

QPainterPath semiRoundedRect(RectSide, const QRect&, int);
QPainterPath semiRoundedRect(RectSide, const QRectF&, int);

QIcon iconFromPath(const QPainterPath&, const QIcon&, QSize, const QColor& filling= Qt::transparent);
QIcon iconFromPath(const QPainterPath&, const QPixmap&, QSize, const QColor& filling= Qt::transparent);
}
