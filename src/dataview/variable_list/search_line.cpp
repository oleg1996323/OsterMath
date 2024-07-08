#include "dataview/variable_list/search_line.h"
#include "kernel/application.h"

namespace dataview{

Frame::Label::Label(QWidget* parent):QLabel(parent){}

Frame::Frame(QWidget* parent):QFrame(parent->parentWidget()){
    setObjectName("VarListSearchLine");
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    //setPalette(Colors::DarkStyle().palette());

    label_search_var_list = new Label(this);

    QFont font1;
    font1.setFamily(QString::fromUtf8("FreeSans"));
    font1.setPointSize(8);
    font1.setBold(true);
    font1.setWeight(100);
    label_search_var_list->setFont(font1);
    label_search_var_list->setAlignment(Qt::AlignCenter);
    QSizePolicy sizepolicy;
    sizepolicy.setRetainSizeWhenHidden(true);
    label_search_var_list->setSizePolicy(sizepolicy);

    search_var_list = new SearchLine(this);

    QHBoxLayout* search_line = new QHBoxLayout(this);
    search_line->setSizeConstraint(QHBoxLayout::SetMaximumSize);
    search_line->setContentsMargins(0,4,0,4);

    search_line->addWidget(label_search_var_list);
    search_line->addWidget(search_var_list);

    setLayout(search_line);
}

void Frame::retranslate(){
    label_search_var_list->setText(kernel::Application::translate("BookMath", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    label_search_var_list->setFixedSize(
                    QSize(QFontMetrics(font()).horizontalAdvance(label_search_var_list->text()),
                          QFontMetrics(font()).height()));
    search_var_list->setPlaceholderText(QCoreApplication::translate("BookMath", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
    table_var_list->retranslate();
}

Frame::SearchLine::SearchLine(QWidget* parent):QLineEdit(parent){
    QSizePolicy sizepolicy;
    sizepolicy.setRetainSizeWhenHidden(true);
    setObjectName(QString::fromUtf8("search_var_list"));
    setMaximumSize(QSize(16777215, 20));
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizepolicy);
    QFont font2;
    font2.setFamily(QString::fromUtf8("Sans"));
    font2.setPointSize(9);
    font2.setBold(false);
    font2.setItalic(false);
    font2.setWeight(50);
    font2.setStyleStrategy(QFont::PreferDefault);
    setFont(font2);
    setLayoutDirection(Qt::LeftToRight);
    setStyleSheet(QString::fromUtf8("font: 9pt \"Sans\";color:rgb(36, 31, 49)"));
    setFrame(true);
    setEchoMode(QLineEdit::Normal);
    setDragEnabled(false);
    setCursorMoveStyle(Qt::LogicalMoveStyle);
    setClearButtonEnabled(false);
}
}
