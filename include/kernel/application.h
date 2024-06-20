#pragma once
#include <QApplication>
#include <QSettings>
#include "styles.h"
#include "settings.h"
#include "data.h"

class BookMath;

namespace kernel{

    class Application:public QApplication{
    public:
        Application(int &argc, char** argv);

        ~Application();

        static BaseData* get_active_sheet();

        static DataPool* get_active_pool();

        static BookMath* get_active_book();

    private:
        static void __save_settings__();

        static void __load_settings__();

        static BaseData* active_sheet_;
        static DataPool* active_pool_;
        static BookMath* active_book_ui_;
    };
}
