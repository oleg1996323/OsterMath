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
#include "model/data_view_header.h"
#include "kernel/application.h"


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

#include <QMessageBox>
#include "model/data_view_header.h"
#include "model/dataview_delegate.h"
#include "model/dataviewmodel.h"

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

    void set_new_model(QAbstractTableModel* model);

    void __load_settings__();

    void __save_settings__();

private:

    void __init__(){
        setTabPosition(QTabWidget::South);
    }
    model::DataViewDelegate* delegate_;
    model::DataViewHeader* header_;
};

class DataViewSplit:public QSplitter{
    Q_OBJECT
public:
    DataViewSplit(QWidget* parent):QSplitter(Qt::Vertical,parent){
        expression_view_ = new VarExpressionView(this);
        data_ = new Sheets(this);
        addWidget(expression_view_);
        addWidget(data_);
        setCollapsible(0,false);
        setCollapsible(1,false);
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        data_->setObjectName("data_view");
        this->setSizes({20,data_->maximumHeight()});

    }

private:
    Sheets* data_;
    VarExpressionView* expression_view_;
};


