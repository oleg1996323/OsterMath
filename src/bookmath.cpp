#include "bookmath.h"
//#include "./ui_bookmath.h"
#include "varlist.h"
//#include "./ui_var_list.h"
#include <QScreen>
#include <QStatusBar>
#include <QMenuBar>

BookMath::BookMath(QWidget *parent)
    : QMainWindow(parent)
{
    var_list_ = new VarList::DockWidget(this);

    addDockWidget(Qt::LeftDockWidgetArea,var_list_,Qt::Vertical);
    __define_window__();
    __define_status_bar__();
    __define_data_view__();
    __define_menu__();
    __define_tool_bar__();
    __define_signals_slots__();
    retranslate();
}

void BookMath::__define_window__(){
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("BookMath"));

    __load_styles__();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize(width,height);
}

void BookMath::__define_status_bar__(){
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    setStatusBar(statusbar);
}

void BookMath::__define_tool_bar__(){
    tool_bar = new BookToolBar(this);
    this->addToolBar(tool_bar);
}

void BookMath::__define_menu__(){
    menubar = new QMenuBar(this);
    menubar->setNativeMenuBar(true);
    QSizePolicy menubar_policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    menubar->setSizePolicy(menubar_policy);
    menubar->setObjectName(QString::fromUtf8("menubar"));

    file_menu = new QMenu(menubar);
    file_menu->setObjectName(QString::fromUtf8("file_menu"));

    file_menu->addAction(QIcon(":booktool/icons/createfilemenu.png"),QObject::tr("Create new"),this,&BookMath::create_new_book,QKeySequence::New);
    file_menu->addAction(QIcon(":booktool/icons/openfilemenu.png"),QObject::tr("Open book"),this,&BookMath::open_new_book,QKeySequence::Open);
    file_menu->addAction(QIcon(":booktool/icons/savefilemenu.png"),QObject::tr("Save"),this,&BookMath::save_book,QKeySequence::Save);
    file_menu->addAction(QIcon(":booktool/icons/saveasmenu.png"),QObject::tr("Save as"),this,&BookMath::save_as,QKeySequence::SaveAs);

    insert_menu = new QMenu(menubar);
    insert_menu->addAction(QIcon(":booktool/icons/chart.png"),QObject::tr("Insert chart"),this,&BookMath::insert_chart);

    view_menu = new QMenu(menubar);
    view_menu->addAction(QObject::tr("Show variables"),this,&BookMath::show_variable_list);

    menubar->addMenu(file_menu);
    menubar->addMenu(insert_menu);
    menubar->addMenu(view_menu);
    menubar->addAction(QObject::tr("Format"));
    menubar->addAction(QObject::tr("Settings"));
    menubar->addAction(QObject::tr("About"));

    this->setMenuBar(menubar);
}

void BookMath::__define_data_view__(){
    centralwidget = new VarDataView(this);

    centralwidget->setObjectName(QString::fromUtf8("mainwidget"));
    centralwidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralwidget);
}

void BookMath::__define_signals_slots__(){
    connect(findChild<ToolButton*>("createnewbook"),&ToolButton::clicked,this,&BookMath::create_new_book);
    connect(findChild<ToolButton*>("savebook"),&ToolButton::clicked,this,&BookMath::save_book);
}

void BookMath::retranslate(){
    file_menu->setTitle(QObject::tr("File"));
    insert_menu->setTitle(QObject::tr("Insert"));
    view_menu->setTitle(QObject::tr("View"));

    //label_var_list->setText(QCoreApplication::translate("BookMath", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
}

void BookMath::create_new_book(){
    setEnabled(false);
    subwindow = new CreateNewBook(this);
    connect(static_cast<CreateNewBook*>(subwindow),&CreateNewBook::closing,this,&QMainWindow::setEnabled);
}

void BookMath::open_new_book(){
    setEnabled(false);
    subwindow = new OpenNewBook(this);
    connect(static_cast<OpenNewBook*>(subwindow),&OpenNewBook::closing,this,&QMainWindow::setEnabled);
}

void BookMath::save_book(){

}

void BookMath::save_as(){

}

void BookMath::insert_chart(){

}

void BookMath::show_variable_list(){
    if(!var_list_->isVisible()){
        var_list_->show();
    }
}

void BookMath::changed(bool ch){
    changed_ = ch;
}

BookMath::~BookMath()
{
}

