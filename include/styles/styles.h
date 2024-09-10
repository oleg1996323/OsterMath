#pragma once
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QStyle>
#include <QPainter>
#include <QCommonStyle>
#include <QProxyStyle>
#include <QStyleOption>

class QSplitterHandle;

namespace Themes{
constexpr int border_round_common = 5;
constexpr int frame_line_width_back = 6;
constexpr int frame_line_width_submid = 4;
constexpr int frame_line_width_mid = 2;

enum TYPE{
    Light,
    Dark
};

enum StyleOptionTypes{
    SO_AdvancedPushButton = QStyleOption::SO_CustomBase + 1
};

class Palette:public QPalette{
public:
    static const QPalette& get();
private:
    static QPalette dark_style;
    static QPalette light_style;
};

//class CustomStyle: public QCommonStyle{
//    Q_OBJECT
//public:

//    virtual void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const override;

//    virtual void drawPrimitive(PrimitiveElement,
//                               const QStyleOption*,
//                               QPainter*,
//                               const QWidget*) const override;
//    virtual void drawControl(ControlElement element,
//                             const QStyleOption *opt,
//                             QPainter *p,
//                             const QWidget*) const override;
//    virtual QPixmap generatedIconPixmap(QIcon::Mode,
//                                        const QPixmap&,
//                                        const QStyleOption*) const override;
//    virtual QStyle::SubControl hitTestComplexControl(QStyle::ComplexControl,
//                                                     const QStyleOptionComplex *,
//                                                     const QPoint &,
//                                                     const QWidget *) const override;
//    virtual int layoutSpacing(QSizePolicy::ControlType control1,
//                              QSizePolicy::ControlType control2,
//                              Qt::Orientation orientation,
//                              const QStyleOption *option,
//                              const QWidget *widget) const override;
//    virtual int	pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget) const override;
//    virtual void	polish(QPalette &pal) override;
//    virtual void	polish(QApplication *app) override;
//    virtual void	polish(QWidget *widget) override;
//    virtual QSize	sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget) const override;
//    virtual QPixmap	standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *option, const QWidget *widget) const override;
//    virtual int	styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *widget, QStyleHintReturn *hret) const override;
//    virtual QRect	subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *widget) const override;
//    virtual QRect	subElementRect(QStyle::SubElement sr, const QStyleOption *opt, const QWidget *widget) const override;
//    virtual void	unpolish(QWidget *widget) override;
//    virtual void	unpolish(QApplication *application) override;
//};

//class CustomStyle: public QProxyStyle{
//    Q_OBJECT
//public:

//    virtual void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const override;

//    virtual void drawPrimitive(PrimitiveElement,
//                               const QStyleOption*,
//                               QPainter*,
//                               const QWidget*) const override;
//    virtual void drawControl(ControlElement element,
//                             const QStyleOption *opt,
//                             QPainter *p,
//                             const QWidget*) const override;
//    virtual QPixmap generatedIconPixmap(QIcon::Mode,
//                                        const QPixmap&,
//                                        const QStyleOption*) const override;
//    virtual QStyle::SubControl hitTestComplexControl(QStyle::ComplexControl,
//                                                     const QStyleOptionComplex *,
//                                                     const QPoint &,
//                                                     const QWidget *) const override;
//    virtual int layoutSpacing(QSizePolicy::ControlType control1,
//                              QSizePolicy::ControlType control2,
//                              Qt::Orientation orientation,
//                              const QStyleOption *option,
//                              const QWidget *widget) const override;
//    virtual int	pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget) const override;
//    virtual void	polish(QPalette &pal) override;
//    virtual void	polish(QApplication *app) override;
//    virtual void	polish(QWidget *widget) override;
//    virtual QSize	sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget) const override;
//    virtual QPixmap	standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *option, const QWidget *widget) const override;
//    virtual int	styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *widget, QStyleHintReturn *hret) const override;
//    virtual QRect	subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *widget) const override;
//    virtual QRect	subElementRect(QStyle::SubElement sr, const QStyleOption *opt, const QWidget *widget) const override;
//    virtual void	unpolish(QWidget *widget) override;
//    virtual void	unpolish(QApplication *application) override;
//};

class OsterStyle: public QProxyStyle{
    Q_OBJECT
public:
    OsterStyle();

    virtual void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const override;

    virtual void drawPrimitive(PrimitiveElement,
                               const QStyleOption*,
                               QPainter*,
                               const QWidget*) const override;
    virtual void drawControl(ControlElement element,
                             const QStyleOption *opt,
                             QPainter *p,
                             const QWidget*) const override;
    virtual QPixmap generatedIconPixmap(QIcon::Mode,
                                        const QPixmap&,
                                        const QStyleOption*) const override;
    virtual QStyle::SubControl hitTestComplexControl(QStyle::ComplexControl,
                                                     const QStyleOptionComplex *,
                                                     const QPoint &,
                                                     const QWidget *) const override;
    virtual int layoutSpacing(QSizePolicy::ControlType control1,
                              QSizePolicy::ControlType control2,
                              Qt::Orientation orientation,
                              const QStyleOption *option,
                              const QWidget *widget) const override;
    virtual int	pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget) const override;
    virtual void	polish(QPalette &pal) override;
    virtual void	polish(QApplication *app) override;
    virtual void	polish(QWidget *widget) override;
    virtual QSize	sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &csz, const QWidget *widget) const override;
    virtual QPixmap	standardPixmap(QStyle::StandardPixmap sp, const QStyleOption *option, const QWidget *widget) const override;
    virtual int	styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *widget, QStyleHintReturn *hret) const override;
    virtual QRect	subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QStyle::SubControl sc, const QWidget *widget) const override;
    virtual QRect	subElementRect(QStyle::SubElement sr, const QStyleOption *opt, const QWidget *widget) const override;
    virtual void	unpolish(QWidget *widget) override;
    virtual void	unpolish(QApplication *application) override;

    virtual bool eventFilter(QObject *obj, QEvent *event) override;
};

}

Q_DECLARE_METATYPE(Themes::TYPE)

