#include "kernel/styles.h"
#include "kernel/settings.h"

namespace Themes {

QPalette Palette::dark_style=QPalette(QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(34,107,154),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(250,250,250),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(0,0,180),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(120,120,120),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(66,139,186),Qt::BrushStyle::SolidPattern),
                                        QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern));



QPalette Palette::light_style=QPalette(QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(34,107,154),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(250,250,250),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(0,0,180),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(120,120,120),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(0,0,0),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(230,230,230),Qt::BrushStyle::SolidPattern),
                                       QBrush(QColor(26,82,118),Qt::BrushStyle::SolidPattern));

const QPalette& Palette::get(){
    switch(kernel::settings::Program::get_theme()){
    case TYPE::Light:
        return light_style;
        break;
    case TYPE::Dark:
        return dark_style;
        break;
    default:
        return light_style;
        break;
    }
}

}
