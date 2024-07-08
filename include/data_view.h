#pragma once
#include <QTextEdit>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>
#include <QFont>
#include <QSizePolicy>
#include <kernel/styles.h>
#include "kernel/exception.h"
#include "utilities/validators/validator.h"
#include "model/data_view_header.h"
#include "kernel/application.h"

#include <QMessageBox>
#include "view.h"

class Sheets:public QTabWidget{
    Q_OBJECT
public:
    Sheets(QWidget* parent);

    Sheets(QWidget* parent, const QString& data_name);

    ~Sheets();

    virtual void tabRemoved(int index) override;

    void rename(const QString& name);

    void erase_sheet(const QString& name) noexcept;

    void change_sheet_name(QString&& name, int tab_id);

    void add_default_sheet();

    void __load_settings__();

    void __save_settings__();

public:

private:

    void __init__(){
        setTabPosition(QTabWidget::South);
    }

    QList<QTableView*> sheets_;
    QList<View*> var_lists_;
};

#include "expression_view.h"

class DataViewSplit:public QSplitter{
    Q_OBJECT
public:
    DataViewSplit(QWidget* parent):QSplitter(Qt::Vertical,parent){
        setObjectName("MainDataView");
        __define_view__();
    }

public slots:
    void show_variable_list();

private:

    void __define_view__();

    void __define_signals_slots__();

    void __load_settings__();

    void __save_settings__();

    void __load_styles__();

    Sheets* data_;
    VarExpressionView* expression_view_;
};


