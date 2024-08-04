#include "styles.h"
#include "kernel/settings.h"
#include "utilities/paths.h"
#include <QPushButton>
#include <QStyleOption>
#include <QToolBar>
#include <QPainterPath>
#include <QPainter>
#include <QBoxLayout>
#include <qdrawutil.h>

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
        if(opt){
            if(opt->state&QStyle::State_MouseOver){
                p->save();
                QPainterPath path = QPainterPath();
                path.addEllipse(opt->rect.center(),20,opt->rect.height()/2);
                p->setRenderHint(QPainter::Antialiasing,true);
                p->setClipPath(path);

                p->strokePath(path,QPen(QBrush(opt->palette.color(QPalette::ColorRole::Base)),2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin));
                p->fillPath(path,opt->palette.color(QPalette::Window));
                p->drawPath(path);
                p->restore();
            }
        }
        else
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
        break;
    }
    case CE_DockWidgetTitle:{
        if(!widget)
            return;
        QPainterPath path;
        p->save();
        QBoxLayout* l = qobject_cast<QBoxLayout*>(widget->layout());
        if(l->direction()==QBoxLayout::LeftToRight){
            path = paths::semiRoundedRect(paths::TOP, opt->rect,Themes::border_round_common);
        }
        else {
            path = paths::semiRoundedRect(paths::LEFT, opt->rect,Themes::border_round_common);
        }
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

    case PM_DockWidgetTitleMargin:{
        return 0;
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
    {
        QPushButton* btn = qobject_cast<QPushButton*>(widget);
        if(btn)
            btn->setAttribute(Qt::WA_Hover,true);
    }
    QCommonStyle::polish(widget);
}
QSize OsterStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget = nullptr) const{
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
    QCommonStyle::unpolish(widget);
}
void OsterStyle::unpolish(QApplication *application){
    QCommonStyle::unpolish(application);
}

//void CustomStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget = nullptr) const{
//    switch(cc){
//    case CC_ComboBox:{
//        break;
//        return;
//    }
//    case CC_Dial:{
//        QCommonStyle::drawComplexControl(cc,opt,p,widget);
//        break;
//        return;
//    }
//    case CC_GroupBox:{
//        break;
//    }
//    case CC_SpinBox:{
//        break;
//    }
//    case CC_MdiControls:{
//        QCommonStyle::drawComplexControl(cc,opt,p,widget);
//        break;
//        return;
//    }
//    case CC_ScrollBar:{
//        break;
//    }
//    case CC_Slider:{
//        break;
//    }
//    case CC_ToolButton:{
//        break;
//    }
//    case CC_TitleBar:{
//        break;
//    }
//    case CC_CustomBase:{
//        break;
//    }
//    default:{
//        QCommonStyle::drawComplexControl(cc,opt,p,widget);
//        break;
//    }
//    }


//}

//void CustomStyle::drawPrimitive(PrimitiveElement element,
//                                const QStyleOption *opt,
//                                QPainter * p,
//                                const QWidget *widget = nullptr) const{
//    switch(element){
//    case PE_FrameDockWidget:{
//        const QStyleOptionDockWidget* pOptionDock =
//                qstyleoption_cast<const QStyleOptionDockWidget*>(opt);
//        if(pOptionDock){
//            p->save();
//            QPainterPath path = QPainterPath();
//            path.addRoundedRect(pOptionDock->rect,5,5);
//            p->setRenderHint(QPainter::Antialiasing,true);
//            p->setClipPath(path);
//            p->strokePath(path,QPen(QBrush(pOptionDock->palette.color(QPalette::Shadow)),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
//            p->fillPath(path,pOptionDock->palette.color(QPalette::Window));
//            p->drawPath(path);
//            p->restore();
//        }
//        break;
//    }
//    case PE_FrameDefaultButton:{
//        QCommonStyle::drawPrimitive(element,opt,p,widget);
//        break;
//    }
//    case PE_PanelMenuBar:{
////        if (widget && qobject_cast<QToolBar*>(widget->parentWidget()))
////            break;
////        if (const QStyleOptionFrame *frame = qstyleoption_cast<const QStyleOptionFrame *>(opt)){
////            qDrawShadePanel(p, frame->rect, frame->palette, false, frame->lineWidth,
////                            &frame->palette.brush(QPalette::Button));
////        }
////        else if (const QStyleOptionToolBar *frame = qstyleoption_cast<const QStyleOptionToolBar *>(opt)){
////            qDrawShadePanel(p, frame->rect, frame->palette, false, frame->lineWidth,
////                            &frame->palette.brush(QPalette::Button));
////        }
//        break;
//    }
//    case PE_Frame:{
//        if(opt){
//            p->save();
//            QPainterPath path = QPainterPath();
//            path.addRoundedRect(opt->rect,3,3);
//            p->setRenderHint(QPainter::Antialiasing,true);
//            p->setClipPath(path);
//            p->strokePath(path,QPen(QBrush(opt->palette.color(QPalette::ColorRole::Dark)),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
//            p->fillPath(path,opt->palette.color(QPalette::Window));
//            p->drawPath(path);
//            p->restore();
//        }
//    }
//    case PE_FrameButtonBevel:{

//        break;
//    }
//    case PE_FrameButtonTool:{
//        break;
//    }
//    case PE_FrameFocusRect:{
//        break;
//    }
//    case PE_FrameGroupBox:{
//        break;
//    }
//    case PE_FrameLineEdit:{
//        break;
//    }
//    case PE_FrameMenu:{
//        break;
//    }
//    case PE_FrameStatusBarItem:{
//        break;
//    }
//    case PE_FrameTabBarBase:{
//        if (const QStyleOptionTabBarBase *tbb
//                = qstyleoption_cast<const QStyleOptionTabBarBase *>(opt)) {
//            p->save();
//            switch (tbb->shape) {
//            case QTabBar::RoundedNorth:
//            case QTabBar::TriangularNorth:
//                p->setPen(QPen(tbb->palette.light(), 0));
//                p->drawLine(tbb->rect.topLeft(), tbb->rect.topRight());
//                break;
//            case QTabBar::RoundedWest:
//            case QTabBar::TriangularWest:
//                p->setPen(QPen(tbb->palette.light(), 0));
//                p->drawLine(tbb->rect.topLeft(), tbb->rect.bottomLeft());
//                break;
//            case QTabBar::RoundedSouth:
//            case QTabBar::TriangularSouth:
//                p->setPen(QPen(tbb->palette.shadow(), 0));
//                p->drawLine(tbb->rect.left(), tbb->rect.bottom(),
//                            tbb->rect.right(), tbb->rect.bottom());
//                p->setPen(QPen(tbb->palette.dark(), 0));
//                p->drawLine(tbb->rect.left(), tbb->rect.bottom() - 1,
//                            tbb->rect.right() - 1, tbb->rect.bottom() - 1);
//                break;
//            case QTabBar::RoundedEast:
//            case QTabBar::TriangularEast:
//                p->setPen(QPen(tbb->palette.dark(), 0));
//                p->drawLine(tbb->rect.topRight(), tbb->rect.bottomRight());
//                break;
//            }
//            p->restore();
//        }
//    break;
//    }
//    case PE_FrameTabWidget:{
//        break;
//    }
//    case PE_FrameWindow:{
//        break;
//    }
//    case PE_IndicatorArrowDown:{
//        break;
//    }
//    case PE_IndicatorArrowLeft:{
//        break;
//    }
//    case PE_IndicatorArrowRight:{
//        break;
//    }
//    case PE_IndicatorArrowUp:{
//        break;
//    }
//    case PE_IndicatorBranch:{
//        break;
//    }
//    case PE_IndicatorButtonDropDown:{
//        break;
//    }
//    case PE_IndicatorCheckBox:{
//        break;
//    }
//    case PE_IndicatorColumnViewArrow:{
//        break;
//    }
//    case PE_IndicatorDockWidgetResizeHandle:{
//        break;
//    }
//    case PE_IndicatorHeaderArrow:{
//        break;
//    }
//    case PE_IndicatorItemViewItemCheck:{
//        break;
//    }
//    case PE_IndicatorItemViewItemDrop:{
//        break;
//    }
//    case PE_IndicatorMenuCheckMark:{
//        break;
//    }
//    case PE_IndicatorProgressChunk:{
//        break;
//    }
//    case PE_IndicatorRadioButton:{
//        break;
//    }
//    case PE_IndicatorSpinDown:{
//        break;
//    }
//    case PE_IndicatorSpinMinus:{
//        break;
//    }
//    case PE_IndicatorSpinPlus:{
//        break;
//    }
//    case PE_IndicatorSpinUp:{
//        break;
//    }
//    case PE_IndicatorTabClose:{
//        break;
//    }
//    case PE_IndicatorTabTearLeft:{
//        break;
//    }
//    case PE_IndicatorTabTearRight:{
//        break;
//    }
//    case PE_IndicatorToolBarHandle:{
//        break;
//    }
//    case PE_IndicatorToolBarSeparator:{
//        break;
//    }
//    case PE_PanelButtonBevel:{
//        break;
//    }
//    case PE_PanelButtonCommand:{
//        break;
//    }
//    case PE_PanelButtonTool:{
//        break;
//    }
//    case PE_PanelItemViewItem:{
//        break;
//    }
//    case PE_PanelItemViewRow:{
//        break;
//    }
//    case PE_PanelLineEdit:{
//        break;
//    }
//    case PE_PanelMenu:{
//        break;
//    }
//    case PE_PanelScrollAreaCorner:{
//        break;
//    }
//    case PE_PanelStatusBar:{
//        break;
//    }
//    case PE_PanelTipLabel:{
//        break;
//    }
//    case PE_PanelToolBar:{
//        break;
//    }
//    case PE_Widget:{
//        break;
//    }
//    default:
//        QCommonStyle::drawPrimitive(element,opt,p,widget);
//        break;
//    }
//}

//void CustomStyle::drawControl(ControlElement element,
//                             const QStyleOption *opt,
//                             QPainter *p,
//                             const QWidget* widget = nullptr) const{
//    QCommonStyle::drawControl(element,opt,p,widget);
//}

//QPixmap CustomStyle::generatedIconPixmap(QIcon::Mode iconMode,
//                                         const QPixmap &pixmap,
//                                         const QStyleOption *opt) const{
//    return QCommonStyle::generatedIconPixmap(iconMode,pixmap,opt);
//}

//QStyle::SubControl CustomStyle::hitTestComplexControl(QStyle::ComplexControl cc,
//                                                      const QStyleOptionComplex *opt,
//                                                      const QPoint &pt,
//                                                      const QWidget *widget = nullptr) const{
//    return QCommonStyle::hitTestComplexControl(cc,opt,pt,widget);
//}

//int CustomStyle::layoutSpacing(QSizePolicy::ControlType control1,
//                              QSizePolicy::ControlType control2,
//                              Qt::Orientation orientation,
//                              const QStyleOption *option = nullptr,
//                  const QWidget *widget = nullptr) const{
//    return QCommonStyle::layoutSpacing(control1,control2,orientation,option,widget);
//}

//int CustomStyle::pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr) const{
//    return QCommonStyle::pixelMetric(m,opt,widget);
//}
//void CustomStyle::polish(QPalette &pal){
//    QCommonStyle::polish(pal);
//}
//void CustomStyle::polish(QApplication *app){
//    QCommonStyle::polish(app);
//}
//void CustomStyle::polish(QWidget *widget){
//    QCommonStyle::polish(widget);
//}
//QSize CustomStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget = nullptr) const{
//    switch(ct){
//    case CT_CheckBox:{
//        break;
//    }
//    case CT_ComboBox:{
//        break;
//    }
//    case CT_DialogButtons:{
//        break;
//    }
//    case CT_GroupBox:{
//        break;
//    }
//    case CT_HeaderSection:{
//        break;
//    }
//    case CT_ItemViewItem:{
//        break;
//    }
//    case CT_LineEdit:{
//        break;
//    }
//    case CT_MdiControls:{
//        break;
//    }
//    case CT_Menu:{
//        if(opt){

//        }
//        break;
//    }
//    case CT_MenuBar:{
//        const QStyleOptionMenuItem* option = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
//        if(opt){
//            int w = QProxyStyle::pixelMetric(PM_MenuBarItemSpacing,option,widget);
//            if(widget)
//                w*=(widget->children().size()-1);
//            int h = QProxyStyle::pixelMetric(PM_MenuBarItemSpacing,option,widget);
//            if(widget)
//                h*=2;
//            h+=option->rect.height();
//        }
//        break;
//    }
//    case CT_MenuBarItem:{
//        const QStyleOptionMenuItem* option = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
//        if(opt){

//        }
//        break;
//    }
//    case CT_MenuItem:{
//        const QStyleOptionMenuItem* option = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
//        if(opt){

//        }
//        break;
//    }
//    case CT_ProgressBar:{
//        break;
//    }
//    case CT_PushButton:{
//        break;
//    }
//    case CT_RadioButton:{
//        break;
//    }
//    case CT_ScrollBar:{
//        break;
//    }
//    case CT_SizeGrip:{
//        break;
//    }
//    case CT_Slider:{
//        break;
//    }
//    case CT_SpinBox:{
//        break;
//    }
//    case CT_Splitter:{
//        break;
//    }
//    case CT_TabBarTab:{
//        break;
//    }
//    case CT_TabWidget:{
//        break;
//    }
//    case CT_ToolButton:{
//        break;
//    }
//    case CT_CustomBase:{
//        break;
//    }
//    default:{
//        return QCommonStyle::sizeFromContents(ct,opt,csz,widget);
//    }
//    }
//    return QCommonStyle::sizeFromContents(ct,opt,csz,widget);
//}
//QPixmap	CustomStyle::standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const{
//    return QCommonStyle::standardPixmap(sp,option,widget);
//}
//int	CustomStyle::styleHint(QStyle::StyleHint sh, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *hret = nullptr) const{
//    return QCommonStyle::styleHint(sh,opt,widget,hret);
//}
//QRect CustomStyle::subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *widget = nullptr) const{
//    return QCommonStyle::subControlRect(cc,opt,sc,widget);
//}
//QRect CustomStyle::subElementRect(QStyle::SubElement sr, const QStyleOption *opt, const QWidget *widget = nullptr) const{
//    return QCommonStyle::subElementRect(sr,opt,widget);
//}
//void CustomStyle::unpolish(QWidget *widget){
//    QCommonStyle::unpolish(widget);
//}
//void CustomStyle::unpolish(QApplication *application){
//    QCommonStyle::unpolish(application);
//}

}
