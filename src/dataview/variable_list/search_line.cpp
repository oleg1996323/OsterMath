#include "dataview/variable_list/search_line.h"
#include "kernel/application.h"

namespace dataview{

SearchLine::SearchLine(QWidget* parent):QFrame(parent->parentWidget()){
    __define_label__();
    __define_search_line__();
    __define_frame__();
}

void SearchLine::__retranslate__(){
    label_search_var_list->setText(kernel::Application::translate("BookMath", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    label_search_var_list->setFixedSize(
                    QSize(QFontMetrics(font()).horizontalAdvance(label_search_var_list->text()),
                          QFontMetrics(font()).height()));
    search_var_list->setPlaceholderText(kernel::Application::translate("BookMath", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
}

void SearchLine::set_model(model::Variables* var){
    var_list_model_ = var;
}

void SearchLine::__define_label__(){
    label_search_var_list = new QLabel(this);
    QFont font1;
    font1.setFamily(QString::fromUtf8("FreeSans"));
    font1.setPointSize(8);
    font1.setBold(true);
    font1.setWeight(QFont::Normal);
    label_search_var_list->setFont(font1);
    label_search_var_list->setAlignment(Qt::AlignCenter);
    QSizePolicy sizepolicy;
    sizepolicy.setRetainSizeWhenHidden(true);
    label_search_var_list->setSizePolicy(sizepolicy);
}

void SearchLine::__define_frame__(){
    setObjectName("VarListSearchLine");
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    QHBoxLayout* search_line = new QHBoxLayout(this);
    search_line->setSizeConstraint(QHBoxLayout::SetMaximumSize);
    search_line->setContentsMargins(0,4,0,4);
    search_line->addWidget(label_search_var_list);
    search_line->addWidget(search_var_list);
    setLayout(search_line);
}

void SearchLine::__define_search_line__(){
    search_var_list = new QLineEdit(this);
    QSizePolicy sizepolicy;
    sizepolicy.setRetainSizeWhenHidden(true);
    search_var_list->setObjectName(QString::fromUtf8("search_var_list"));
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    search_var_list->setSizePolicy(sizepolicy);
    QFont font2;
    font2.setFamily(QString::fromUtf8("Sans"));
    font2.setPointSize(9);
    font2.setBold(false);
    font2.setItalic(false);
    font2.setWeight(QFont::Normal);
    font2.setStyleStrategy(QFont::PreferDefault);
    search_var_list->setFont(font2);
    search_var_list->setLayoutDirection(Qt::LeftToRight);
    search_var_list->setStyleSheet(QString::fromUtf8("font: 9pt \"Sans\";color:rgb(36, 31, 49)"));
    search_var_list->setFrame(true);
    search_var_list->setEchoMode(QLineEdit::Normal);
    search_var_list->setDragEnabled(false);
    search_var_list->setCursorMoveStyle(Qt::LogicalMoveStyle);
    search_var_list->setClearButtonEnabled(false);
}
}
