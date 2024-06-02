#pragma once
#include "kernel/application.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include "kernel/styles.h"
#include "def.h"
#include "booktoolbar.h"
#include "utilities/windows/createnew.h"
#include "utilities/windows/opennew.h"
#include "data_view.h"

namespace VarList{
    class DockWidget;
}


class BookMath : public QMainWindow, public Retranslatable
{
    Q_OBJECT
public:
    BookMath(QWidget *parent = nullptr);
    ~BookMath();

    virtual void retranslate() override;

private:
    //widget where var are illustrated
    VarList::DockWidget* var_list_;

    //main widgets
    VarDataView *centralwidget;
    QVBoxLayout* central_widget_layout_;

    //menu items
    QMenuBar *menubar;
    QMenu *file_menu;
    QMenu *insert_menu;
    QMenu *view_menu;

    //status bar
    QStatusBar *statusbar;

    //toolbar
    BookToolBar* tool_bar;

    //utility window deactivating the book-window when openned
    AbstractSubWindowInterface* subwindow;

    void __define_window__();

    void __define_menu__();

    void __define_tool_bar__();

    void __define_data_view__();

    void __define_status_bar__();

    void __define_signals_slots__();

    void __load_settings__(){
        QSettings* sets_ = kernel::Application::get_settings();
        sets_->beginGroup("bookmath");
            setGeometry(sets_->value("geometry").toRect());
        sets_->endGroup();
    }

    void __save_settings__(){
        QSettings* sets_ = kernel::Application::get_settings();
        sets_->beginGroup("bookmath");
            sets_->setValue("geometry",geometry());
        sets_->endGroup();
    }

    void __load_styles__(){
        if(kernel::Application::get_theme() == Themes::Dark)
            setPalette(Themes::DarkStyle().palette());
        else setPalette(Themes::LightStyle().palette());
    }

private slots:
    void create_new_book();
    void open_new_book();
    void save_book();
    void save_as();
    void insert_chart();
    void show_variable_list();

};
