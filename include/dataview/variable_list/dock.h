#pragma once
#include <QObject>
#include <QMainWindow>
#include <QDockWidget>
#include <QSize>
#include "kernel/application.h"
#include "kernel/def.h"
#include "dataview/variable_list/table.h"

namespace dataview{

class Frame;
class TitleBar;

class DockWidget:public QDockWidget, public ::Retranslatable{
    Q_OBJECT
public:
    DockWidget(QMainWindow* parent);
    ~DockWidget();
    virtual void retranslate() override;
private:
    Frame* frame_;
    Table* var_list_;
    TitleBar* titlebar_;
    QSize last_size;

    void __load_settings__();
    void __save_settings__();
    void __load_styles__();
public slots:
    void collapse();
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
};
}
