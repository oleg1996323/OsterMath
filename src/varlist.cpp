#include "varlist.h"
#include "styles.h"
#include <QSizePolicy>

VarListFrame::VarListFrame(QWidget* parent):QFrame(parent){
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

    label_search_var_list = new QLabel(this);
    label_search_var_list->setPalette(Colors::DarkStyle().palette());
    label_search_var_list->setObjectName(QString::fromUtf8("label_search_var_list"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(label_search_var_list->sizePolicy().hasHeightForWidth());
    label_search_var_list->setSizePolicy(sizePolicy2);
    label_search_var_list->setMinimumSize(QSize(50, 0));
    label_search_var_list->setMaximumSize(QSize(50, 20));
    QFont font1;
    font1.setFamily(QString::fromUtf8("FreeSans"));
    font1.setPointSize(8);
    font1.setBold(true);
    font1.setWeight(100);
    label_search_var_list->setFont(font1);
    label_search_var_list->setAlignment(Qt::AlignCenter);

    search_var_list = new QLineEdit(this);
    search_var_list->setObjectName(QString::fromUtf8("search_var_list"));
    search_var_list->setMaximumSize(QSize(16777215, 20));
    QFont font2;
    font2.setFamily(QString::fromUtf8("Sans"));
    font2.setPointSize(9);
    font2.setBold(false);
    font2.setItalic(false);
    font2.setWeight(50);
    font2.setStyleStrategy(QFont::PreferDefault);
    search_var_list->setFont(font2);
    search_var_list->setLayoutDirection(Qt::LeftToRight);
    search_var_list->setStyleSheet(QString::fromUtf8("font: 9pt \"Sans\";color:rgb(36, 31, 49)"));
    search_var_list->setFrame(true);
    search_var_list->setEchoMode(QLineEdit::Normal);
    search_var_list->setDragEnabled(false);
    search_var_list->setCursorMoveStyle(Qt::LogicalMoveStyle);
    search_var_list->setClearButtonEnabled(false);

    QHBoxLayout* search_line = new QHBoxLayout(this);
    search_line->setContentsMargins(0,4,0,4);

    search_line->addWidget(label_search_var_list);
    search_line->addWidget(search_var_list);
    gridLayout->addLayout(search_line);

    table_var_list = new QTableWidget(this);
    if (table_var_list->columnCount() < 3)
        table_var_list->setColumnCount(3);
    QFont font3;
    font3.setFamily(QString::fromUtf8("Sans Serif"));
    font3.setPointSize(8);
    font3.setBold(true);
    font3.setWeight(75);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem->setFont(font3);
    table_var_list->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem1->setFont(font3);
    table_var_list->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem2->setFont(font3);
    table_var_list->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    if (table_var_list->rowCount() < 1)
        table_var_list->setRowCount(1);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    table_var_list->setItem(0, 0, __qtablewidgetitem3);
    table_var_list->setObjectName(QString::fromUtf8("table_var_list"));
    table_var_list->setEnabled(true);
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(table_var_list->sizePolicy().hasHeightForWidth());
    table_var_list->setSizePolicy(sizePolicy3);
    table_var_list->setMouseTracking(true);
    table_var_list->setTabletTracking(true);
    table_var_list->setAcceptDrops(false);
    table_var_list->setFrameShape(QFrame::Panel);
    table_var_list->setFrameShadow(QFrame::Plain);
    table_var_list->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    table_var_list->setDragEnabled(false);
    table_var_list->setDragDropMode(QAbstractItemView::NoDragDrop);
    table_var_list->setAlternatingRowColors(false);
    table_var_list->setSelectionMode(QAbstractItemView::SingleSelection);
    table_var_list->setShowGrid(true);
    table_var_list->setRowCount(1);
    table_var_list->horizontalHeader()->setVisible(true);
    table_var_list->horizontalHeader()->setCascadingSectionResizes(false);
    table_var_list->horizontalHeader()->setDefaultSectionSize(150);
    table_var_list->horizontalHeader()->setStretchLastSection(true);

    gridLayout->addWidget(table_var_list);
    setLayout(gridLayout);
}

void VarListFrame::retranslate(){
    label_search_var_list->setText(QCoreApplication::translate("BookMath", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    search_var_list->setInputMask(QString());
    search_var_list->setText(QString());
    search_var_list->setPlaceholderText(QCoreApplication::translate("BookMath", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
    QTableWidgetItem *___qtablewidgetitem = table_var_list->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText(QCoreApplication::translate("BookMath", "\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
    QTableWidgetItem *___qtablewidgetitem1 = table_var_list->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText(QCoreApplication::translate("BookMath", "\320\242\320\270\320\277", nullptr));
    QTableWidgetItem *___qtablewidgetitem2 = table_var_list->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText(QCoreApplication::translate("BookMath", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
}

VarListTitleBar::VarListTitleBar(QWidget* parent):QFrame(parent){
    this->setContentsMargins(0,0,0,0);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(1);
    setPalette(Colors::DarkStyle().palette());

    layout_ = new QHBoxLayout(this);
    layout_->setSpacing(0);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
    layout_->setSizeConstraint(QLayout::SetNoConstraint);

    label_var_list = new QLabel(this);
    label_var_list->setContentsMargins(0,0,0,0);
    label_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_label"));
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    label_var_list->setSizePolicy(sizePolicy);
    label_var_list->setMaximumSize(QSize(2000, 20));
    QFont font;
    font.setFamily("Sans");
    font.setPointSize(10);
    font.setBold(true);
    font.setWeight(100);
    label_var_list->setFont(font);

    layout_->addWidget(label_var_list,Qt::AlignLeft);

    horizontalSpacer = new QSpacerItem(0, 0,QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout_->addItem(horizontalSpacer);

    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
    collapse_var_list = new CloseCollapseButtons(":common/common/collapse.png",this);
    collapse_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_collapse"));

    layout_->addWidget(collapse_var_list,Qt::AlignRight);

    close_var_list = new CloseCollapseButtons(":common/common/close.png",this);
    close_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_close"));

    layout_->addWidget(close_var_list,Qt::AlignRight);

    setLayout(layout_);

    connect(close_var_list,&CloseCollapseButtons::clicked,qobject_cast<VarListDockWidget*>(parent),&VarListDockWidget::close);
    connect(collapse_var_list,&CloseCollapseButtons::clicked,qobject_cast<VarListDockWidget*>(parent),&VarListDockWidget::collapse);
}

void VarListTitleBar::retranslate(){
    label_var_list->setText(QCoreApplication::translate("Form", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
    collapse_var_list->setText(QString());
    close_var_list->setText(QString());
}

#include <QMainWindow>

VarListDockWidget::VarListDockWidget(QMainWindow* parent):QDockWidget(parent,Qt::Widget){
    palette = new QPalette(Colors::DarkStyle().palette());
    //QBrush brush_1(QColor(190,220,255,255));
    //palette->setBrush(QPalette::ColorRole::Window, brush_1);
    this->setPalette(*palette);

    titlebar_ = new VarListTitleBar(this);
    titlebar_->setPalette(Colors::DarkStyle().palette());
    this->setContentsMargins(0,0,0,0);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    layout_ = new QVBoxLayout(this);
    layout_->setMargin(0);
    layout_->setContentsMargins(0,0,0,0);
    setLayout(layout_);
    frame_ = new VarListFrame(this);
    frame_->setPalette(Colors::DarkStyle().palette());
    setWidget(frame_);

    retranslate();
}

void VarListDockWidget::retranslate(){
    frame_->retranslate();
    titlebar_->retranslate();
}

