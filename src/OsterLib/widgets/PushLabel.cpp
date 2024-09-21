#include "PushLabel.h"
#include <QBackingStore>

PushLabel::PushLabel(QString text, QWidget* parent):QLabel(text,parent,Qt::Widget){
    setAttribute(Qt::WidgetAttribute::WA_Hover);
    setTextInteractionFlags(textInteractionFlags() |
                            Qt::TextInteractionFlag::LinksAccessibleByMouse |
                            Qt::TextInteractionFlag::TextBrowserInteraction);
    setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setMouseTracking(false);
    setFixedSize(minimumSizeHint());
    setContentsMargins(0,0,0,0);
    setOpenExternalLinks(true);
    QFont font;
    font.setFamily(this->font().family());
    font.setItalic(true);
    font.setBold(false);
    setFont(font);
}
PushLabel::PushLabel(QWidget* parent):QLabel(parent,Qt::Widget){
    setAttribute(Qt::WidgetAttribute::WA_Hover);
    setTextInteractionFlags(textInteractionFlags() |
                            Qt::TextInteractionFlag::LinksAccessibleByMouse |
                            Qt::TextInteractionFlag::TextBrowserInteraction);
    setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setMouseTracking(false);
    setFixedSize(minimumSizeHint());
    setContentsMargins(0,0,0,0);
    setOpenExternalLinks(false);
    QFont font;
    font.setFamily(this->font().family());
    font.setItalic(true);
    font.setBold(false);
    setFont(font);
}
