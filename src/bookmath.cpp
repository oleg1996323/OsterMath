#include "bookmath.h"
#include "sz_functions.h"
#include <QScreen>
#include <QStatusBar>
#include <QMenuBar>
#include "dataview/expression_text_edit.h"
#include "dataview/variable_list/dock.h"
namespace Book{
BookMath::BookMath(QWidget *parent)
    : QMainWindow(parent), ObjectFromSettings(this)
{
    kernel::Application::set_active_book(this);
    __book_initialization__();
    upload_style();
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

    upload_style();
    load_settings();
}

void BookMath::__define_status_bar__(){
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    setStatusBar(statusbar);
}

void BookMath::__define_tool_bar__(){
    tool_bar = new Widgets::ToolBar(this);
    auto role = tool_bar->backgroundRole();
    tool_bar->setBackgroundRole(QPalette::Window);
    tool_bar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    addToolBar(Qt::ToolBarArea::TopToolBarArea,tool_bar);
}

void BookMath::__define_menu__(){
    menubar = new QMenuBar(this);
    menubar->setContentsMargins(0,0,0,0);
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
    view_menu->addAction(QObject::tr("Show variables"),findChild<dataview::DockWidget*>("dockwidget_var_list"),&dataview::DockWidget::show);

    menubar->addMenu(file_menu);
    menubar->addMenu(insert_menu);
    menubar->addMenu(view_menu);
    menubar->addAction(QObject::tr("Format"));
    QAction* act_settings = new QAction(QObject::tr("Settings"),menubar);
    menubar->addAction(act_settings);
    connect(act_settings,&QAction::triggered, this,&BookMath::settings);
    menubar->addAction(QObject::tr("About"));
    {
        using namespace kernel::settings;
        langs_ = menubar->addMenu(QIcon(Program::get_language_properties().path), "");
        langs_->setContentsMargins(0,0,0,0);
        langs_->resize(30,30);
        for(const auto& res_data:resource_langs){
            QAction* action = langs_->addAction(QIcon(res_data.path),res_data.text);
            QObject::connect(action,&QAction::triggered,QApplication::instance(),[&res_data](){qobject_cast<kernel::Application*>(QApplication::instance())->set_language(res_data);});
        }
    }

    this->setMenuBar(menubar);
}

void BookMath::__define_data_view__(){
    centralwidget = new dataview::DataViewSplit(this);

    centralwidget->setObjectName(QString::fromUtf8("mainwidget"));
    centralwidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralwidget);
}

void BookMath::__define_signals_slots__(){
    connect(findChild<PushButton*>("createnewbook"),&PushButton::clicked,this,&BookMath::create_new_book);
    connect(findChild<PushButton*>("savebook"),&PushButton::clicked,this,&BookMath::save_book);
    //
}

void BookMath::__retranslate__(){
    file_menu->setTitle(QObject::tr("File"));
    insert_menu->setTitle(QObject::tr("Insert"));
    view_menu->setTitle(QObject::tr("View"));

    //label_var_list->setText(QCoreApplication::translate("BookMath", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
}

dataview::Sheets* BookMath::get_sheets_handler() const{
    return centralwidget->sheets();
}

dataview::ExpressionTextEdit* BookMath::get_expression_editor() const{
    if(dataview::ExpressionTextEdit* p = findChild<dataview::ExpressionTextEdit*>("expressionEditor")){
        return p;
    }
    else{
        qFatal("Not defined expression editor");
        throw std::runtime_error("Not defined expression editor");
    }
}

void BookMath::create_new_book(){
    setEnabled(false);
    subwindow = new SecondairyWindows::CreateNewBook(this);
    connect(static_cast<SecondairyWindows::CreateNewBook*>(subwindow),&SecondairyWindows::CreateNewBook::closing,this,&QMainWindow::setEnabled);
}

void BookMath::open_new_book(){
    setEnabled(false);
    subwindow = new SecondairyWindows::OpenNewBook(this);
    connect(static_cast<SecondairyWindows::OpenNewBook*>(subwindow),&SecondairyWindows::OpenNewBook::closing,this,&QMainWindow::setEnabled);
}

void BookMath::settings(){
    setEnabled(false);
    subwindow = new SecondairyWindows::Settings(this);
    connect(static_cast<SecondairyWindows::Settings*>(subwindow),&SecondairyWindows::Settings::closing,this,&QMainWindow::setEnabled);

}

void BookMath::save_book(){

}

void BookMath::save_as(){

}

void BookMath::insert_chart(){

}

void BookMath::changed(bool ch){
    changed_ = ch;
}

void BookMath::__upload_language__(){
    using namespace kernel::settings;
    langs_->setIcon(QIcon(kernel::settings::Program::get_language_properties().path));
    retranslate();
}
void BookMath::__upload_fonts__(){
    using namespace kernel::settings;
    langs_->setIcon(QIcon(kernel::settings::Program::get_language_properties().path));
    retranslate();
}
void BookMath::__upload_style__(){

}

BookMath::~BookMath()
{
    save_settings();
}

void BookMath::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("bookmath");
        if(sets_->value("geometry").isNull())
            resize(functional::fullscreen_size());
        else
            setGeometry(sets_->value("geometry").toRect());
    sets_->endGroup();
}

void BookMath::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("bookmath");
        sets_->setValue("geometry",geometry());
    sets_->endGroup();
}

void BookMath::__book_initialization__(){
    pool_ = std::make_unique<DataPool>("Pool data 1");
    kernel::Application::set_active_pool(pool_.get());
}

dataview::NodeData* BookMath::current_node_data_viewer() const{
    return qobject_cast<dataview::Sheets*>(get_sheets_handler())->active_sheet_node_data_viewer();
}
}
