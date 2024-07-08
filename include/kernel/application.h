#pragma once
#include <QApplication>
#include <QSettings>
#include "styles.h"
#include "settings.h"

class BookMath;
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
        static BookMath* get_active_book();
        static model::Manager* get_model_manager();
        static void set_active_data(BaseData*);
        static void set_active_pool(DataPool*);
        static void set_active_book(BookMath*);
        static void set_model_manager(model::Manager*);
    public slots:
        void set_language(const settings::LANG_DATA&);
        void set_variable_list_showed(bool);
    public:
        signals:
        void language_changed();
        void font_inc_changed();
        void style_changed();
        bool variable_list_showed(bool);
    private:
        static void __save_settings__();
        static void __load_settings__();
        static BaseData* active_data_;
        static DataPool* active_pool_;
        static BookMath* active_book_ui_;
        static model::Manager* manager;
    };
}
