#include "styles/styles.h"
#include "dataview/expression_view.h"
#include <QDebug>
#include "utilities/paths.h"

namespace dataview{

ExpressionButton::ExpressionButton(const QString& res_path,QWidget* parent):QPushButton("",parent){

    setContentsMargins(0,0,0,0);
    setFixedSize(30,30);
    QPainterPath path;
    path.addRoundedRect(rect(),Themes::border_round_common,Themes::border_round_common);
    setIcon(paths::iconFromPath(path,QPixmap(res_path),size(),Qt::transparent));
    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
}

VarExpressionView::VarExpressionView(QWidget* parent):QWidget(parent){
    this->setContentsMargins(0,0,0,0);
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);

    expression_ = new QTextEdit(this);
    expression_->setObjectName("expression"+parent->objectName());
    expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    expression_->setMinimumHeight(QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
    expression_->setGeometry(pos().x(),pos().y(),width(),QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
    //qDebug()<<QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom();

    formula_expl_ = new ExpressionButton(":booktool/icons/expr.png",this);
    formula_expl_->setObjectName("formula_expl"+parent->objectName());

    expand_collapse_expl_ = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,":common/common/expandexpr.png",":common/common/collapseexpr.png",this);
    expand_collapse_expl_->setObjectName("expand_collapse_expl"+parent->objectName());
    expand_collapse_expl_->setFixedSize(30,30);

    layout_->addWidget(formula_expl_);
    layout_->addWidget(expression_);
    layout_->addWidget(expand_collapse_expl_);
    layout_->setAlignment(formula_expl_,Qt::AlignTop);
    layout_->setAlignment(expression_,Qt::AlignTop);
    layout_->setAlignment(expand_collapse_expl_,Qt::AlignTop);

    layout_->setSizeConstraint(QHBoxLayout::SizeConstraint::SetMinimumSize);

    this->setLayout(layout_);
}

void VarExpressionView::expand_collapse(){
    expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
}
}
