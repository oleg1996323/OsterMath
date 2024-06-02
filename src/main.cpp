#include "kernel/application.h"
#include <QLocale>
#include <QTranslator>
#include "bookmath.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    kernel::Application a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "OsterMath_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    settings::initSettings();
    BookMath w;
    w.show();
    return a.exec();
}
