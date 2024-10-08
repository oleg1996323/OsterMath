#pragma once
#include <QApplication>
#include <QSettings>
#include "settings.h"

namespace Book{
class BookMath;
}
class BaseData;
class DataPool;

namespace model{
class Manager;
}

namespace kernel{

    class Application:public QApplication{
        Q_OBJECT
    public:
        Application(int &argc, char** argv);
        ~Application();
        static BaseData* get_active_data();
        static DataPool* get_active_pool();
        static Book::BookMath* get_active_book();
        static model::Manager* get_model_manager();
        static void set_active_data(BaseData*);
        static void set_active_pool(DataPool*);
        static void set_active_book(Book::BookMath*);
        static void set_model_manager(model::Manager*);
    public slots:
        void set_language(const settings::LANG_DATA&);
    public:
        signals:
        void language_changed();
        void font_inc_changed();
        void style_changed();
    private:
        static void __save_settings__();
        static void __load_settings__();
        static BaseData* active_data_;
        static DataPool* active_pool_;
        static Book::BookMath* active_book_ui_;
        static model::Manager* manager;
    };
}
