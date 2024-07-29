#include "kernel/styles.h"
#include "kernel/settings.h"
#include <QPushButton>
#include <QStyleOption>

namespace Themes {

QPalette Palette::dark_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(5, 25, 35));
    res.setColor(QPalette::WindowText,QColor(230, 230, 230));
    res.setColor(QPalette::Base,QColor(0, 53, 84));
    res.setColor(QPalette::AlternateBase,QColor(0, 100, 148));
    res.setColor(QPalette::ToolTipBase,QColor(0, 100, 148));
    res.setColor(QPalette::ToolTipText,QColor(230, 230, 230));
    res.setColor(QPalette::PlaceholderText,QColor(230,230,230));
    res.setColor(QPalette::Text,QColor(230, 230, 230));
    res.setColor(QPalette::Button,QColor(0, 100, 148));
    res.setColor(QPalette::ButtonText,QColor(230,230,230));
    res.setColor(QPalette::BrightText,QColor(5, 130, 202));

    res.setColor(QPalette::Light,QColor(0, 166, 251));
    res.setColor(QPalette::Midlight,QColor(5, 130, 202));
    res.setColor(QPalette::Dark,QColor(0, 53, 84));
    res.setColor(QPalette::Mid,QColor(0, 100, 148));
    res.setColor(QPalette::Shadow,QColor(5, 25, 35));
    res.setColor(QPalette::Highlight,QColor(5, 25, 35));
    return res;
    }();


QPalette Palette::light_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(173, 232, 244));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,QColor(144, 224, 239));
    res.setColor(QPalette::AlternateBase,QColor(72, 202, 228));
    res.setColor(QPalette::ToolTipBase,QColor(72, 202, 228));
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,QColor(72, 202, 228));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(72, 202, 228));

    res.setColor(QPalette::Light,QColor(202, 240, 248));
    res.setColor(QPalette::Midlight,QColor(0, 180, 216));
    res.setColor(QPalette::Dark,QColor(2, 62, 138));
    res.setColor(QPalette::Mid,QColor(120,120,120));
    res.setColor(QPalette::Shadow,QColor(3, 4, 94));
    return res;
    }();

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

void CustomStyle::polish(QWidget *pwgt){
    if(qobject_cast<QPushButton*>(pwgt)){
        pwgt->setAttribute(Qt::WA_Hover,true);
    }
}

void CustomStyle::unpolish(QWidget *pwgt){
    if(qobject_cast<QPushButton*>(pwgt)){
        pwgt->setAttribute(Qt::WA_Hover,false);
    }
}

void CustomStyle::drawPrimitive(PrimitiveElement elem,
                                const QStyleOption *popt,
                                QPainter *ppainter,
                                const QWidget *pwgt) const{
    switch(elem){
        case PE_PanelButtonCommand:{
            const QStyleOptionButton* pOptionButton =
                    qstyleoption_cast<const QStyleOptionButton*>(popt);
            if(pOptionButton){
                QPixmap pix(pOptionButton->rect.size());
                pix.fill(QColor(0,0,255));
                ppainter->drawPixmap(pOptionButton->rect,pix);

            }
            break;
        }
    default:
        QCommonStyle::drawPrimitive(elem,popt,ppainter,pwgt);
        break;
    }
}

}
