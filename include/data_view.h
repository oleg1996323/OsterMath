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
//        QPalette palette
//        formula_expl_->setPalette(QPalette());



        expand_collapse_expl_ = new QPushButton(this);
        expand_collapse_expl_->setObjectName("expand_collapse_expl"+parent->objectName());
        expand_collapse_expl_->setFixedSize(30,30);

        layout_->addWidget(formula_expl_);
        layout_->addWidget(expression_);
        layout_->addWidget(expand_collapse_expl_);

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

class VarDataView:public QSplitter{
    Q_OBJECT
public:
    VarDataView(QWidget* parent):QSplitter(Qt::Vertical,parent){

        expression_view_ = new VarExpressionView(this);
        data_ = new QTableWidget(this);
        addWidget(expression_view_);
        addWidget(data_);
        setCollapsible(0,false);
        setCollapsible(1,false);
        data_->setObjectName("data_view"+parent->objectName());

    }
private:
    QTableWidget* data_;
    VarExpressionView* expression_view_;
};
