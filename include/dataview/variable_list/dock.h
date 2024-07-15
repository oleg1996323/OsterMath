#pragma once
#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <QSize>
#include "kernel/application.h"
#include "kernel/def.h"
#include "model/manager.h"
#include "dataview/variable_list/table.h"

namespace dataview{

class Frame;
class TitleBar;
class View;

class DockWidget:public QDockWidget, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    DockWidget(QWidget* parent);
    ~DockWidget();
    QMainWindow* window_attached() const;
    void set_window_attached(View*);
    bool closed_by_titlebar() const;

private:

    Frame* frame_=nullptr;
    Table* var_list_=nullptr;
    TitleBar* titlebar_=nullptr;
    bool closed = false;

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;


public slots:
    void setData(model::Data*);
    void collapse();
    void close_from_titlebar();

};
}
