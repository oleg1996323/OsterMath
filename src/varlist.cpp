#include "varlist.h"
#include "model/list_header.h"
#include "kernel/styles.h"
#include "kernel/application.h"
#include "model/varlistmodel_delegate.h"
#include <QSizePolicy>
#include <QDebug>

using namespace VarList;

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

Frame::Label::Label(QWidget* parent):QLabel(parent){}

Table::Table(QWidget* parent){
    var_list_ = new model::Variables(parent, kernel::Application::get_active_data());
    setModel(var_list_);
    setItemDelegate(new model::VariablesDelegate(this));
    model::ListHeader* header = new model::ListHeader(this);
    setHorizontalHeader(header);
    header->setModel(var_list_);
    /*assert(header->itemDelegate());
    if (columnCount() < 3)
        setColumnCount(3);
    QFont font3;
    font3.setFamily(QString::fromUtf8("Sans Serif"));
    font3.setPointSize(8);
    font3.setBold(true);
    font3.setWeight(75);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem->setFont(font3);
    setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem1->setFont(font3);
    setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem2->setFont(font3);
    setHorizontalHeaderItem(2, __qtablewidgetitem2);
    if (rowCount() < 1)
        setRowCount(1);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    setItem(0, 0, __qtablewidgetitem3);
    setObjectName(QString::fromUtf8("table_var_list"));
    setEnabled(true);
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy3.setRetainSizeWhenHidden(true);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy3);
    setMouseTracking(true);
    setTabletTracking(true);
    setAcceptDrops(false);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Plain);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    setDragEnabled(false);
    setDragDropMode(QAbstractItemView::NoDragDrop);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(true);
    setRowCount(1);
    horizontalHeader()->setVisible(true);
    horizontalHeader()->setCascadingSectionResizes(false);
    horizontalHeader()->setDefaultSectionSize(150);
    horizontalHeader()->setStretchLastSection(true);*/
}

Frame::Frame(QWidget* parent):QFrame(parent){
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    //setPalette(Colors::DarkStyle().palette());

    gridLayout = new QVBoxLayout(this);

    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QString::fromUtf8("varlistwidget_layout"));
    gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    label_search_var_list = new Label(this);
    label_search_var_list->setPalette(Themes::Palette::get());
    label_search_var_list->setObjectName(QString::fromUtf8("label_search_var_list"));

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
    gridLayout->addLayout(search_line);

    table_var_list = new Table(this);


    gridLayout->addWidget(table_var_list);
    setLayout(gridLayout);

}

void Frame::retranslate(){
    label_search_var_list->setText(QCoreApplication::translate("BookMath", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    label_search_var_list->setFixedSize(
                    QSize(QFontMetrics(font()).horizontalAdvance(label_search_var_list->text()),
                          QFontMetrics(font()).height()));
    search_var_list->setPlaceholderText(QCoreApplication::translate("BookMath", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
    table_var_list->retranslate();
}

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

#include <QMainWindow>

DockWidget::DockWidget(QMainWindow* parent):QDockWidget(parent,Qt::Widget){
    __load_styles__();
    //QBrush brush_1(QColor(190,220,255,255));
    //palette->setBrush(QPalette::ColorRole::Window, brush_1);

    titlebar_ = new TitleBar(this);
    titlebar_->setPalette(Themes::Palette::get());
    this->setContentsMargins(0,0,0,0);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea);
    QSizePolicy sizepolicy;
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    frame_ = new Frame(this);
    frame_->setPalette(Themes::Palette::get());
    setWidget(frame_);

    retranslate();
    last_size = size();
}

void DockWidget::retranslate(){
    frame_->retranslate();
    titlebar_->retranslate();
}
