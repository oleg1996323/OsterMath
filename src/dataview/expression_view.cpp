#include "styles.h"
#include <QPainterPath>
#include <QDebug>
#include "CollapsibleButton.h"
#include "dataview/expression_view.h"
#include "icon_functions.h"
#include "dataview/expression_text_edit.h"
#include "kernel/application.h"

namespace dataview{

ExpressionButton::ExpressionButton(const QString& res_path,QWidget* parent):IconedButton("",parent), ObjectFromSettings(this){
    setObjectName("expression_button");
    set_size({30,30});
    setBorders(true);
    setRounded_borders(true);
    setBorder_radius(Themes::border_round_common);
    setIcon(QIcon(res_path));
}

void ExpressionButton::__load_settings__(){}
void ExpressionButton::__save_settings__(){}
void ExpressionButton::__upload_fonts__(){

}
void ExpressionButton::__upload_style__(){
    if(kernel::settings::Program::get_theme() == Themes::Dark)
        setIcon(QIcon(":booktool/icons/expr_dark.png"));
    else
        setIcon(QIcon(":booktool/icons/expr_light.png"));
}
void ExpressionButton::__upload_language__(){}

VarExpressionView::VarExpressionView(QWidget* parent):QWidget(parent){
    this->setContentsMargins(0,0,0,0);
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);

    expression_ = new ExpressionTextEdit(this);
    formula_expl_ = new ExpressionButton(kernel::settings::Program::get_theme() == Themes::Dark?":booktool/icons/expr_dark.png":":booktool/icons/expr_light.png",this);
    expand_collapse_expl_ = new CollapseButton(CollapseButtonState::COLLAPSED,":common/common/expandexpr.png",":common/common/collapseexpr.png",this);
    expand_collapse_expl_->setObjectName("expand_collapse_expl");
    expand_collapse_expl_->set_size({30,30});

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
