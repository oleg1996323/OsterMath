#pragma once
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QStyle>
#include <QPainter>

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

class LightStyle:public QPalette{
public:
    LightStyle(){
        setBrush(QPalette::ColorRole::Window,QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern));
        setBrush(QPalette::ColorRole::WindowText,QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern));
        setBrush(QPalette::ColorRole::Button,QBrush(QColor(34,107,154),Qt::BrushStyle::SolidPattern));
        setBrush(QPalette::ColorRole::ButtonText,QBrush(QColor(250,250,250),Qt::BrushStyle::SolidPattern));
        setBrush(QPalette::ColorRole::Text,QBrush(QColor(0,0,0),Qt::BrushStyle::SolidPattern));
        setBrush(QPalette::ColorRole::PlaceholderText,QBrush(QColor(0,0,0),Qt::BrushStyle::SolidPattern));
        //setBrush(QPalette::ColorRole::Base,QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern));
    }

    const QPalette& palette() const{
        return *this;
    }
};

}

Q_DECLARE_METATYPE(Themes::TYPE)

