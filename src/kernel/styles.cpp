#include "kernel/styles.h"
#include "kernel/settings.h"
#include <QPushButton>
#include <QStyleOption>

namespace Themes {

QPalette Palette::dark_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(0, 92, 144));
    res.setColor(QPalette::WindowText,QColor(255, 255, 255));
    res.setColor(QPalette::Base,QColor(0, 92, 144));
    res.setColor(QPalette::AlternateBase,QColor(0, 64, 104));
    res.setColor(QPalette::ToolTipBase,QColor(0, 92, 144));
    res.setColor(QPalette::ToolTipText,QColor(255, 255, 255));
    res.setColor(QPalette::PlaceholderText,QColor(255,255,255));
    res.setColor(QPalette::Text,QColor(255, 255, 255));
    res.setColor(QPalette::Button,QColor(0, 92, 144));
    res.setColor(QPalette::ButtonText,QColor(255,255,255));
    res.setColor(QPalette::BrightText,QColor(255, 255, 255));

    res.setColor(QPalette::Light,QColor(173, 232, 255));
    res.setColor(QPalette::Midlight,QColor(144, 212, 244));
    res.setColor(QPalette::Dark,QColor(0, 64, 104));
    res.setColor(QPalette::Mid,QColor(0, 92, 144));
    res.setColor(QPalette::Shadow,QColor(0, 0, 0));
    return res;
    }();


QPalette Palette::light_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(173, 232, 255));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,QColor(173, 232, 255));
    res.setColor(QPalette::AlternateBase,QColor(122, 188, 222));
    res.setColor(QPalette::ToolTipBase,QColor(173, 232, 255));
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,QColor(122, 188, 222));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(255, 255, 255));

    res.setColor(QPalette::Light,QColor(173, 232, 255));
    res.setColor(QPalette::Midlight,QColor(144, 212, 244));
    res.setColor(QPalette::Dark,QColor(0, 64, 104));
    res.setColor(QPalette::Mid,QColor(0, 92, 144));
    res.setColor(QPalette::Shadow,QColor(0, 0, 0));
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
