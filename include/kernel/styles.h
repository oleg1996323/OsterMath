#pragma once
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QStyle>
#include <QPainter>
#include <QCommonStyle>

namespace Themes{

enum TYPE{
    Light,
    Dark
};

class Palette:public QPalette{
public:
//    DarkStyle(){

        //setBrush(QPalette::ColorRole::Base,QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern));
//    }

    static const QPalette& get();
private:
    static QPalette dark_style;
    static QPalette light_style;
};

class CustomStyle: public QCommonStyle{
public:
    virtual void polish(QWidget* pwgt) override;
    virtual void unpolish(QWidget* pwgt) override;

    virtual void drawPrimitive(PrimitiveElement elem,
                               const QStyleOption* popt,
                               QPainter* ppainter,
                               const QWidget* pwgt = 0) const override;
};

}

Q_DECLARE_METATYPE(Themes::TYPE)

