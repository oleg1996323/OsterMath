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
    VarExpressionView(QWidget* parent):QWidget(parent){
        this->setContentsMargins(0,0,0,0);
        layout_ = new QHBoxLayout(this);
        layout_->setContentsMargins(0,0,0,0);
        layout_->setSpacing(0);

        expression_ = new QTextEdit(this);
        expression_->setObjectName("expression"+parent->objectName());
        expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
        expression_->setMinimumHeight(QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
        expression_->setGeometry(pos().x(),pos().y(),width(),QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
        qDebug()<<QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom();

        formula_expl_ = new ExpressionButton(":booktool/icons/expr.png",this);
        formula_expl_->setObjectName("formula_expl"+parent->objectName());

        expand_collapse_expl_ = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,":common/common/expandexpr.png",":common/common/collapseexpr.png",this);
        expand_collapse_expl_->setObjectName("expand_collapse_expl"+parent->objectName());
        expand_collapse_expl_->setFixedSize(45,45);

        layout_->addWidget(formula_expl_);
        layout_->addWidget(expression_);
        layout_->addWidget(expand_collapse_expl_);
        layout_->setAlignment(formula_expl_,Qt::AlignTop);
        layout_->setAlignment(expression_,Qt::AlignTop);
        layout_->setAlignment(expand_collapse_expl_,Qt::AlignTop);

        layout_->setSizeConstraint(QHBoxLayout::SizeConstraint::SetMinimumSize);

        this->setLayout(layout_);

    }
private:
    QHBoxLayout* layout_;
    QTextEdit* expression_;


    ExpressionButton* formula_expl_;
    QPushButton* expand_collapse_expl_;

private slots:
    void expand_collapse(){
        expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    }
};

#include <QTableView>
#include <QTabWidget>
#include <data.h>
#include <QSettings>

class VarData:public QTableView{
public:  
    VarData(QWidget* parent, const QString& name, BaseData* data):
        QTableView(parent),
        data_(data)
    {

    }

    void rename(const QString& name) noexcept{
        data_->set_name(name.toStdString());
    }

private:
    BaseData* data_;
    QSettings sets_;
};

#include <QMessageBox>

class Sheets:public QTabWidget{
    Q_OBJECT
public:
    Sheets(QWidget* parent):
        QTabWidget(parent),
        data_pool(tr("Книга").toStdString())
    {
        __load_settings__();
        for(int i=0;i<3;++i)
            add_default_sheet();
    }

    Sheets(QWidget* parent, const QString& name):
        QTabWidget(parent),
        data_pool(name.toStdString())
    {
        __load_settings__();
    }

    ~Sheets(){
        __save_settings__();
    }

    void rename(const QString& name){
        data_pool.set_name(name.toStdString());
    }

    void erase_sheet(const QString& name) noexcept{
        data_pool.erase(name.toStdString());
    }

    void change_sheet_name(QString&& name, int tab_id){
        try{
            if(validator::BaseData::validate(name)==validator::Invalid)
                throw sheet::IncorrectName(tr("Недопустимое название листа").toStdString());
            for(int id = 0; id<count();++id)
                if(tabText(id)==name)
                    throw sheet::AlreadyExist(tr("Лист с таким названием уже существует").toStdString());
            setTabText(tab_id,name);
        }
        catch(const std::logic_error& err){
            QMessageBox(QMessageBox::Icon::Critical,QObject::tr("Невозможно создать лист"), tr("Лист с таким названием уже существует"),QMessageBox::Ok,this);
        }
    }

    void add_default_sheet(){
        QString new_name = tr("Лист"+QString::number(data_pool.size()+1).toUtf8());
        this->addTab(new VarData(this,
                                 new_name,
                                 data_pool.add_data(new_name.toStdString())),
                     new_name);

    }

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


