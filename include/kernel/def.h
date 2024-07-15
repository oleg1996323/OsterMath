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
public:
    void retranslate();

private:
    virtual void __retranslate__() = 0;
};

class ObjectFromSettings{
public:
    ObjectFromSettings(QObject* object);

    void upload_fonts();
    void upload_style();
    void upload_language();
    void load_settings();
    void save_settings();

private:
    virtual void __load_settings__() = 0;
    virtual void __save_settings__() = 0;
    virtual void __upload_fonts__() = 0;
    virtual void __upload_style__() = 0;
    virtual void __upload_language__() = 0;

public slots:
    void changed_language();
    void changed_font();
    void changed_style();
};

QIcon negativeIcon(const QIcon &icon);
