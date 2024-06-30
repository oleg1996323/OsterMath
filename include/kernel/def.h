#pragma once
#include <QPushButton>
#include <QCommonStyle>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QStringList>
#include <QArrayData>

namespace files{
constexpr std::array<const char*,3> format={".xlsx",".omb",".ods"};
}

namespace variables{
static QList<QString> names_of_types = {
        QT_TRANSLATE_NOOP("ModelItemsTypes","Unknown"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","String array"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Numeric array"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Value"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","String"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Array")
    };
}


QWidget* findParent(QWidget* widget, QString name);

//using for classes, where any translations are provided
class Retranslatable{
    virtual void retranslate() = 0;
};

class ObjectFromSettings{
public:
    ObjectFromSettings(QObject* object);

    virtual void upload_fonts() = 0;
    virtual void upload_style() = 0;
    virtual void upload_language() = 0;

public slots:
    void changed_language();
    void changed_font();
    void changed_style();
};

QIcon negativeIcon(const QIcon &icon);
