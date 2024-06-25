#pragma once
#include <QApplication>
#include <QSettings>
#include "styles.h"
#include "settings.h"

class BookMath;
class BaseData;
class DataPool;

namespace kernel{

    class Application:public QApplication{
        Q_OBJECT
    public:
        Application(int &argc, char** argv);

        ~Application();

        static BaseData* get_active_data();

        static DataPool* get_active_pool();

        static BookMath* get_active_book();

        static void set_active_data(BaseData*);

        static void set_active_pool(DataPool*);

        static void set_active_book(BookMath*);

    public slots:
        void set_language(const settings::LANG_DATA&);

    public:
        signals:
        void language_changed();

    private:
        static void __save_settings__();

        static void __load_settings__();

        static BaseData* active_data_;
        static DataPool* active_pool_;
        static BookMath* active_book_ui_;
    };
}
