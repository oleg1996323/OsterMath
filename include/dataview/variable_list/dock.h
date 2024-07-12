#pragma once
#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <QSize>
#include "kernel/application.h"
#include "kernel/def.h"
#include "dataview/variable_list/table.h"
#include "model/varlist_delegate.h"
#include "model/varlist_header.h"

namespace dataview{

class Frame;
class TitleBar;

class DockWidget:public QDockWidget, public Retranslatable{
    Q_OBJECT
public:
    DockWidget(QWidget* parent);
    ~DockWidget();
    QMainWindow* window_attached() const;
    void set_window_attached(QMainWindow*);
    virtual void retranslate() override;
private:
    Frame* frame_=nullptr;
    Table* var_list_=nullptr;
    TitleBar* titlebar_=nullptr;
    QMainWindow* window_owner_=nullptr;

    void __load_settings__();
    void __save_settings__();
    void __load_styles__();

public slots:
    void set_model(const model::Data&);
    void collapse();
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
};
}
