#pragma once
#include <QTextEdit>
#include <QFont>
#include <utilities/custom_widgets/buttons.h>
#include <styles.h>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>
#include <QSizePolicy>

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

class VarData:public QTableView{
public:
    VarData(QWidget* parent):QTableView(parent){

    }

};

class VarDataView:public QSplitter{
    Q_OBJECT
public:
    VarDataView(QWidget* parent):QSplitter(Qt::Vertical,parent){

        expression_view_ = new VarExpressionView(this);
        data_ = new VarData(this);
        addWidget(expression_view_);
        addWidget(data_);
        setCollapsible(0,false);
        setCollapsible(1,false);
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        data_->setObjectName("data_view"+parent->objectName());
        this->setSizes({20,data_->maximumHeight()});

    }
private:
    VarData* data_;
    VarExpressionView* expression_view_;
};
