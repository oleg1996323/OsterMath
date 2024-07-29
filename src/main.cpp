#include "kernel/application.h"
#include <QLocale>
#include <QTranslator>
#include "bookmath.h"

int main(int argc, char *argv[])
{
    kernel::Application a(argc, argv);

    qRegisterMetaType<TYPE_VAL>("TYPE_VAL");
    qRegisterMetaType<model::HEADER>("model::HEADER");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<Value_t>("Value_t");
    qRegisterMetaType<Node*>("Node*");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "OsterMath_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Book::BookMath w;
    w.show();
    return a.exec();
}
