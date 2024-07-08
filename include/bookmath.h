#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include "def.h"
#include "kernel/application.h"
#include "menuwidgets/booktoolbar.h"
#include "utilities/windows.h"
#include "dataview/expr_view_splitter.h"
#include "data.h"

namespace VarList{
    class DockWidget;
}

class BookMath : public QMainWindow, public Retranslatable, public ObjectFromSettings
{
    Q_OBJECT
public:
    BookMath(QWidget *parent = nullptr);
    ~BookMath();

    virtual void retranslate() override;

    dataview::Sheets* get_sheets_handler() const;

private:
    std::unique_ptr<DataPool> pool_;

    //main widgets

    dataview::DataViewSplit *centralwidget;

    //menu items
    QMenuBar *menubar;
    QMenu *file_menu;
    QMenu *insert_menu;
    QMenu *view_menu;
    QMenu *langs_;

    //status bar
    QStatusBar *statusbar;

    //toolbar
    BookToolBar* tool_bar;

    //utility window deactivating the book-window when openned
    AbstractSubWindowInterface* subwindow;
    bool changed_ = false;

    void __define_window__();

    void __define_menu__();

    void __define_tool_bar__();

    void __define_data_view__();

    void __define_status_bar__();

    void __define_signals_slots__();

    void __load_settings__();

    void __save_settings__();

    void __load_styles__();

    void __book_initialization__();

    virtual void upload_language() override;
    virtual void upload_fonts() override;
    virtual void upload_style() override;

private slots:
    void create_new_book();
    void open_new_book();
    void settings();
    void save_book();
    void save_as();
    void insert_chart();
    void changed(bool);
};
