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

class SearchLine;
class TitleBar;
class View;

class DockWidget:public QDockWidget, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    DockWidget(QWidget* parent);
    ~DockWidget();
    bool closed_by_titlebar() const;

private:

    QSize dock_size_before_hidding;
    SearchLine* search_line_= nullptr;
    Table* var_list_=nullptr;
    TitleBar* titlebar_=nullptr;
    bool closed = false;

    virtual QSize sizeHint() const override;
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    virtual void paintEvent(QPaintEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;

public slots:
    void setData(model::Data*);
    void collapse();
    void close_from_titlebar();

};
}
