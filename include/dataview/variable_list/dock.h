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
    void set_model(const model::Data&);
    void collapse();
//    virtual void closeEvent(QCloseEvent *event) override;
//    virtual void showEvent(QShowEvent *event) override;
};
}
