#pragma once
#include <QTextEdit>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>
#include <QFont>
#include <QSizePolicy>
#include <utilities/custom_widgets/buttons.h>
#include <kernel/styles.h>
#include "kernel/exception.h"
#include "utilities/validators/validator.h"


class ExpressionButton:public IconedButton{
    Q_OBJECT
public:
    ExpressionButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){

        setContentsMargins(0,0,0,0);
        setFixedSize(45,45);
    }
};

class VarExpressionView:public QWidget{
    Q_OBJECT
public:
    VarExpressionView(QWidget* parent);
private:
    QHBoxLayout* layout_;
    QTextEdit* expression_;


    ExpressionButton* formula_expl_;
    QPushButton* expand_collapse_expl_;

private slots:
    void expand_collapse();
};

#include <QTableView>
#include <QTabWidget>
#include <data.h>
#include <QSettings>

class VarData:public QTableView{
public:
    VarData(QWidget* parent, const QString& name, BaseData* data);

    void rename(const QString& name) noexcept;

private:
    BaseData* data_;
    QSettings sets_;
};

#include <QMessageBox>

class Sheets:public QTabWidget{
    Q_OBJECT
public:
    Sheets(QWidget* parent);

    Sheets(QWidget* parent, const QString& name);

    ~Sheets();

    void rename(const QString& name);

    void erase_sheet(const QString& name) noexcept;

    void change_sheet_name(QString&& name, int tab_id);

    void add_default_sheet();

    void __load_settings__();

    void __save_settings__();

private:
    DataPool data_pool;

    void __init__(){
        setTabPosition(QTabWidget::South);
    }
};

class VarDataView:public QSplitter{
    Q_OBJECT
public:
    VarDataView(QWidget* parent):QSplitter(Qt::Vertical,parent){

        expression_view_ = new VarExpressionView(this);
        data_ = new Sheets(this);
        addWidget(expression_view_);
        addWidget(data_);
        setCollapsible(0,false);
        setCollapsible(1,false);
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        data_->setObjectName("data_view"+parent->objectName());
        this->setSizes({20,data_->maximumHeight()});

    }
private:
    Sheets* data_;
    VarExpressionView* expression_view_;
};


