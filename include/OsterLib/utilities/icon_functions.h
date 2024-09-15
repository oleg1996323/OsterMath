#pragma once
#include <qnamespace.h>

class QIcon;
class QSize;
class QColor;
class QPainterPath;
class QPixmap;

QIcon negativeIcon(const QIcon &icon);
QIcon iconFromPath(const QPainterPath&, const QIcon&, QSize, const QColor& filling);
QIcon iconFromPath(const QPainterPath&, const QPixmap&, QSize, const QColor& filling);
