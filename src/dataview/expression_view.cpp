#include "styles.h"
#include <QPainterPath>
#include <QDebug>
#include "CollapsibleButton.h"
#include "dataview/expression_view.h"
#include "icon_functions.h"
#include "dataview/expression_text_edit.h"

namespace dataview{

ExpressionButton::ExpressionButton(const QString& res_path,QWidget* parent):PushButton("",parent){
    setContentsMargins(0,0,0,0);
    setFixedSize(30,30);
    setBorders(true);
    setRounded_borders(true);
    setBorder_radius(Themes::border_round_common);
    setIcon(QIcon(res_path));
    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
}

VarExpressionView::VarExpressionView(QWidget* parent):QWidget(parent){
    this->setContentsMargins(0,0,0,0);
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);

    expression_ = new ExpressionTextEdit(this);
    formula_expl_ = new ExpressionButton(":booktool/icons/expr.png",this);
    formula_expl_->setObjectName("formula_expl"+parent->objectName());

    expand_collapse_expl_ = new CollapseButton(CollapseButtonState::COLLAPSED,":common/common/expandexpr.png",":common/common/collapseexpr.png",this);
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
