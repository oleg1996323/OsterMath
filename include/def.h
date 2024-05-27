#pragma once
#include <QPushButton>
#include <QCommonStyle>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QStringList>
#include <QArrayData>

constexpr std::array<const char*,3> format_={".xlsx",".omb",".ods"};

QWidget* findParent(QWidget* widget, QString name);

//using for classes, where any translations are provided
class Retranslatable{
    virtual void retranslate() = 0;
};

QIcon negativeIcon(const QIcon &icon);
