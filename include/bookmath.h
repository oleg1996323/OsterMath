#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include "settings.h"
#include "styles.h"
#include "def.h"
#include "booktoolbar.h"
#include "utilitiesWin/createnew.h"

class VarListDockWidget;

class BookMath : public QMainWindow, public Retranslatable
{
    Q_OBJECT
public:
    BookMath(QWidget *parent = nullptr);
    ~BookMath();

    virtual void retranslate() override;

private:
    //widget where var are illustrated
    VarListDockWidget* var_list_;

    //main widgets
    QWidget *centralwidget;
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

    AbstractSubWindowInterface* subwindow;

    void __define_menu__();

    void __define_tool_bar__();

    void __define_data_view__();

    void __define_signals_slots__();

private slots:
    void create_new_book();
    void open_new_book();
    void save_book();
    void save_as();
    void insert_chart();
    void show_variable_list();

};
