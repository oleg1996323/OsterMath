#include "varlist.h"
#include "styles.h"
#include <QSizePolicy>

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

void Frame::SearchLine::showEvent(QShowEvent *event){
    (void)event;
    updateGeometry();
}

Frame::Label::Label(QWidget* parent):QLabel(parent){}

Frame::Table::Table(QWidget* parent):QTableWidget(parent){
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
    horizontalHeader()->setStretchLastSection(true);
    last_size = size();
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
    label_search_var_list->setPalette(Colors::DarkStyle().palette());
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
    QTableWidgetItem *___qtablewidgetitem = table_var_list->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText(QCoreApplication::translate("BookMath", "\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
    QTableWidgetItem *___qtablewidgetitem1 = table_var_list->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText(QCoreApplication::translate("BookMath", "\320\242\320\270\320\277", nullptr));
    QTableWidgetItem *___qtablewidgetitem2 = table_var_list->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText(QCoreApplication::translate("BookMath", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
}

TitleBar::TitleBar(QWidget* parent):QFrame(parent){
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

    label_var_list = new Label(this);
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

    collapse_var_list = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::EXPANDED,
                                           ":common/common/expand.png",
                                            ":common/common/collapse.png",
                                            this);
    collapse_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_collapse"));

    layout_->addWidget(collapse_var_list,Qt::AlignRight);

    close_var_list = new CloseButton(":common/common/close.png",this);
    close_var_list->setObjectName(QString::fromUtf8("varlisttitlebar_close"));

    layout_->addWidget(close_var_list,Qt::AlignRight);

    setLayout(layout_);

    connect(close_var_list,&CloseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::close);
    connect(collapse_var_list,&CollapseButton::clicked,qobject_cast<DockWidget*>(parent),&DockWidget::collapse);
}

void TitleBar::retranslate(){
    label_var_list->setText(QCoreApplication::translate("Form", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
    collapse_var_list->setText(QString());
    close_var_list->setText(QString());
}

#include <QMainWindow>

DockWidget::DockWidget(QMainWindow* parent):QDockWidget(parent,Qt::Widget){
    palette = new QPalette(Colors::DarkStyle().palette());
    //QBrush brush_1(QColor(190,220,255,255));
    //palette->setBrush(QPalette::ColorRole::Window, brush_1);
    this->setPalette(*palette);

    titlebar_ = new TitleBar(this);
    titlebar_->setPalette(Colors::DarkStyle().palette());
    this->setContentsMargins(0,0,0,0);
    this->setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
    this->setTitleBarWidget(titlebar_);
    setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QSizePolicy sizepolicy;
    sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizepolicy.setRetainSizeWhenHidden(true);
    setSizePolicy(sizepolicy);
    frame_ = new Frame(this);
    frame_->setPalette(Colors::DarkStyle().palette());
    setWidget(frame_);

    retranslate();
}

void DockWidget::retranslate(){
    frame_->retranslate();
    titlebar_->retranslate();
}
