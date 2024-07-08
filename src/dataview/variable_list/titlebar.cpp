#include "dataview/variable_list/titlebar.h"

namespace dataview{

TitleBar::TitleBar(QWidget* parent):QFrame(parent){
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    setPalette(Themes::Palette::get());

    label_var_list = new Label(this);
    collapse_var_list = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::EXPANDED,
                                           ":common/common/expand.png",
                                            ":common/common/collapse.png",
                                            this);
    collapse_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_collapse"));

    close_var_list = new CloseButton(":common/common/close.png",this);
    close_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_close"));

    connect(close_var_list,&CloseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::close);
    connect(collapse_var_list,&CollapseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::collapse);
    setHorizontal();
}

void TitleBar::retranslate(){
    label_var_list->setText(QCoreApplication::translate("Form", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
    collapse_var_list->setText(QString());
    close_var_list->setText(QString());
}
}
