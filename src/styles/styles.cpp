#include "styles.h"
#include "kernel/settings.h"
#include "utilities/paths.h"
#include <QPushButton>
#include <QStyleOption>
#include <QToolBar>
#include <QPainterPath>
#include <QPainter>
#include <QBoxLayout>
#include <QSplitter>
#include <QStylePainter>
#include <qdrawutil.h>

namespace dataview{
class TitleBar;
}

namespace Themes {

QPalette Palette::dark_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(0, 92, 144));
    res.setColor(QPalette::WindowText,QColor(230, 230, 230));
    res.setColor(QPalette::Base,res.window().color().lighter(115));
    res.setColor(QPalette::AlternateBase,res.window().color().lighter(130));
    res.setColor(QPalette::ToolTipBase,res.alternateBase().color());
    res.setColor(QPalette::ToolTipText,QColor(230, 230, 230));
    res.setColor(QPalette::PlaceholderText,QColor(230,230,230));
    res.setColor(QPalette::Text,QColor(230, 230, 230));
    res.setColor(QPalette::Button,res.window().color().lighter(130));
    res.setColor(QPalette::ButtonText,QColor(230,230,230));
    res.setColor(QPalette::BrightText,QColor(230, 230, 230));

    res.setColor(QPalette::Midlight,res.button().color().lighter(125));
    res.setColor(QPalette::Light,res.midlight().color().lighter(125));
    res.setColor(QPalette::Mid,res.button().color().darker(125));
    res.setColor(QPalette::Dark,res.mid().color().darker(125));
    res.setColor(QPalette::Shadow,QColor(0, 0, 0));
    return res;
    }();


QPalette Palette::light_style=[](){
    QPalette res;
    res.setColor(QPalette::Window,QColor(173, 232, 255));
    res.setColor(QPalette::WindowText,QColor(0,0,0));
    res.setColor(QPalette::Base,res.window().color().lighter(110));
    res.setColor(QPalette::AlternateBase,res.window().color().lighter(120));
    res.setColor(QPalette::ToolTipBase,res.alternateBase().color());
    res.setColor(QPalette::ToolTipText,QColor(0,0,0));
    res.setColor(QPalette::PlaceholderText,QColor(0,0,0));
    res.setColor(QPalette::Text,QColor(0,0,0));
    res.setColor(QPalette::Button,res.window().color().lighter(120));
    res.setColor(QPalette::ButtonText,QColor(0,0,0));
    res.setColor(QPalette::BrightText,QColor(230, 230, 230));

    res.setColor(QPalette::Midlight,res.button().color().lighter(125));
    res.setColor(QPalette::Light,res.midlight().color().lighter(125));
    res.setColor(QPalette::Mid,res.button().color().darker(125));
    res.setColor(QPalette::Dark,res.mid().color().darker(125));
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

OsterStyle::OsterStyle(){

}

void OsterStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget = nullptr) const{
    switch(cc){
    case CC_CustomBase:{
        QProxyStyle::drawComplexControl(cc,opt,p,widget);
        break;
    }
    default:{
        QProxyStyle::drawComplexControl(cc,opt,p,widget);
        break;
    }
    }
}

void OsterStyle::drawPrimitive(PrimitiveElement element,
                                const QStyleOption *opt,
                                QPainter * p,
                                const QWidget *widget = nullptr) const{
    switch(element){
    case PE_FrameDockWidget:{
    const QStyleOptionDockWidget* pOptionDock =
            qstyleoption_cast<const QStyleOptionDockWidget*>(opt);
    if(pOptionDock){
        if(!widget)
            return;
        QPainterPath path;
        p->save();
        path.addRoundedRect(opt->rect,Themes::border_round_common,Themes::border_round_common);
        p->setRenderHint(QPainter::Antialiasing,true);
        p->setClipPath(path);
        QPen middle = QPen(opt->palette.dark().color());
        QPen back = QPen(opt->palette.light().color());
        middle.setWidth(Themes::frame_line_width_mid);
        back.setWidth(Themes::frame_line_width_back);
        p->fillPath(path,opt->palette.window());
        p->setPen(back);
        p->drawPath(path);
        p->setPen(middle);
        p->drawPath(path);
        p->restore();
    }
    else
        QProxyStyle::drawPrimitive(element,opt,p,widget);
    break;
    }
    case PE_FrameGroupBox:{
        p->save();
        QPainterPath path;
        QPen back;
        QPen submid;
        QPen mid;
        back.setBrush(opt->palette.dark());
        submid.setBrush(opt->palette.mid());
        mid.setBrush(opt->palette.midlight());
        back.setWidth(Themes::frame_line_width_back);
        submid.setWidth(Themes::frame_line_width_submid);
        mid.setWidth(Themes::frame_line_width_mid);
        path.addRoundedRect(opt->rect,Themes::border_round_common,Themes::border_round_common);
        p->setClipPath(path);
        p->fillPath(path,opt->palette.window());
        p->setPen(back);
        p->drawPath(path);
        p->setPen(submid);
        p->drawPath(path);
        p->setPen(mid);
        p->drawPath(path);
        p->restore();
        break;
    }
    case PE_PanelToolBar:{}
    case PE_PanelButtonCommand:{
        if(!widget)
            return;
        if(opt->state&QStyle::State_MouseOver){
            QLinearGradient grad;
            grad.setStart(0,0);
            grad.setFinalStop(opt->rect.width(),opt->rect.height());
            grad.setColorAt(0,opt->palette.button().color());
            grad.setColorAt(0.5,opt->palette.midlight().color());
            grad.setColorAt(1,opt->palette.light().color());
            QPainterPath path;
            path.addRoundedRect(opt->rect,Themes::border_round_common,Themes::border_round_common);
            p->setClipPath(path);
            p->fillPath(path,grad);
        }
        else{
            QPainterPath path;
            path.addRoundedRect(opt->rect,Themes::border_round_common,Themes::border_round_common);
            p->setClipPath(path);
            p->fillPath(path,opt->palette.button());
        }
        break;
    }
    case PE_IndicatorDockWidgetResizeHandle:{
//        if(opt){
//            if(opt->state&QStyle::State_MouseOver){
//                p->save();
//                QPainterPath path = QPainterPath();
//                path.addEllipse(opt->rect.center(),20,opt->rect.height()/2);
//                p->setRenderHint(QPainter::Antialiasing,true);
//                p->setClipPath(path);

//                p->strokePath(path,QPen(QBrush(opt->palette.color(QPalette::ColorRole::Base)),2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin));
//                p->fillPath(path,opt->palette.color(QPalette::Window));
//                p->drawPath(path);
//                p->restore();
//            }
//        }
//        else
            QProxyStyle::drawPrimitive(element,opt,p,widget);
        break;
    }
    default:
        QProxyStyle::drawPrimitive(element,opt,p,widget);
        break;
    }
}

void OsterStyle::drawControl(ControlElement element,
                             const QStyleOption *opt,
                             QPainter *p,
                             const QWidget* widget = nullptr) const{
    switch(element){
    case CE_Splitter:{
//        if(const QSplitterHandle* handle = qobject_cast<const QSplitterHandle*>(widget)){
//            p->save();
//            QLinearGradient grad;
//            grad.setColorAt(0,Qt::transparent);
//            QColor color = kernel::settings::Program::get_theme()&Themes::Dark?handle->palette().light().color():handle->palette().dark().color();
//            grad.setColorAt(0.5,color);
//            color.setAlpha(255);
//            grad.setColorAt(0.2,color);
//            grad.setColorAt(0.8,color);
//            grad.setColorAt(1,Qt::transparent);
//            if(opt->state&QStyle::State_MouseOver){
//                if(handle->orientation()&Qt::Horizontal){
//                    grad.setStart(-handle->width(),handle->height()/2);
//                    grad.setFinalStop(handle->width(),handle->height()/2);
//                    p->fillRect(QRect(0,0,handle->width(),handle->height()),grad);
//                }
//                else{
//                    grad.setStart(handle->width()/2,0);
//                    grad.setFinalStop(handle->width()/2,handle->height()*4);
//                    p->fillRect(QRect(0,0,handle->width(),handle->height()*4),grad);
//                }
//            }
//            else{
//                if(handle->orientation()&Qt::Horizontal){
//                    grad.setStart(0,handle->height()/2);
//                    grad.setFinalStop(handle->width(),handle->height()/2);
//                    p->fillRect(QRect(0,0,handle->width(),handle->height()),grad);
//                }
//                else{
//                    grad.setStart(handle->width()/2,0);
//                    grad.setFinalStop(handle->width()/2,handle->height());
//                    p->fillRect(QRect(0,0,handle->width(),handle->height()),grad);
//                }
//            }
//            p->restore();
//        }
        break;
    }
    case CE_DockWidgetTitle:{
        if(!widget)
            return;
        if(opt->state&QStyle::State_MouseOver){
            QPainterPath path;
            p->save();
            QLinearGradient grad;
            grad.setStart(0,0);
            grad.setFinalStop(opt->rect.width(),opt->rect.height());
            grad.setColorAt(0,opt->palette.button().color());
            grad.setColorAt(0.5,opt->palette.midlight().color());
            grad.setColorAt(1,opt->palette.light().color());
            p->setClipPath(path);
            p->fillPath(path,grad);
            p->restore();
        }
        else{
            QPainterPath path;
            p->save();
            p->setClipPath(path);
            p->fillPath(path,opt->palette.window());
            p->restore();
        }
        break;
    }
    default:
        QProxyStyle::drawControl(element,opt,p,widget);
    }
}

QPixmap OsterStyle::generatedIconPixmap(QIcon::Mode iconMode,
                                         const QPixmap &pixmap,
                                         const QStyleOption *opt) const{
    return QProxyStyle::generatedIconPixmap(iconMode,pixmap,opt);
}

QStyle::SubControl OsterStyle::hitTestComplexControl(QStyle::ComplexControl cc,
                                                      const QStyleOptionComplex *opt,
                                                      const QPoint &pt,
                                                      const QWidget *widget = nullptr) const{
    return QProxyStyle::hitTestComplexControl(cc,opt,pt,widget);
}

int OsterStyle::layoutSpacing(QSizePolicy::ControlType control1,
                              QSizePolicy::ControlType control2,
                              Qt::Orientation orientation,
                              const QStyleOption *option = nullptr,
                  const QWidget *widget = nullptr) const{
    return QProxyStyle::layoutSpacing(control1,control2,orientation,option,widget);
}

int OsterStyle::pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr) const{
    switch(m){
    case(PM_SplitterWidth):{
        return 0;
        break;
    }
    default:{
        return baseStyle()->pixelMetric(m,opt,widget);
    }
    }
}
void OsterStyle::polish(QPalette &pal){
    QCommonStyle::polish(pal);
}
void OsterStyle::polish(QApplication *app){
    QCommonStyle::polish(app);
}
void OsterStyle::polish(QWidget *widget){
    if(QPushButton* btn = qobject_cast<QPushButton*>(widget))
        btn->setAttribute(Qt::WA_Hover,true);
    if(QSplitterHandle* handle = qobject_cast<QSplitterHandle*>(widget)){
        handle->setAttribute(Qt::WA_Hover,true);
    }
    QCommonStyle::polish(widget);
}
QSize OsterStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget = nullptr) const{
    if(ct==QStyle::CT_ItemViewItem)
        return QProxyStyle::sizeFromContents(ct,opt,csz,widget);
    return QProxyStyle::sizeFromContents(ct,opt,csz,widget);
}
QPixmap	OsterStyle::standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const{
    return QProxyStyle::standardPixmap(sp,option,widget);
}
int	OsterStyle::styleHint(QStyle::StyleHint sh, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *hret = nullptr) const{
    return QProxyStyle::styleHint(sh,opt,widget,hret);
}
QRect OsterStyle::subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *widget = nullptr) const{
    return QProxyStyle::subControlRect(cc,opt,sc,widget);
}
QRect OsterStyle::subElementRect(QStyle::SubElement sr, const QStyleOption *opt, const QWidget *widget = nullptr) const{
    return QProxyStyle::subElementRect(sr,opt,widget);
}
void OsterStyle::unpolish(QWidget *widget){
    {
        QPushButton* btn = qobject_cast<QPushButton*>(widget);
        if(btn)
            btn->setAttribute(Qt::WA_Hover,false);
    }
    {
        QSplitterHandle* spt = qobject_cast<QSplitterHandle*>(widget);
        if(spt)
            spt->setAttribute(Qt::WA_Hover,false);
    }
    QCommonStyle::unpolish(widget);
}
void OsterStyle::unpolish(QApplication *application){
    QCommonStyle::unpolish(application);
}

bool OsterStyle::eventFilter(QObject *obj, QEvent *event){
    return QProxyStyle::eventFilter(obj, event);
}

}
