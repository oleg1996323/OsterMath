#include "bookmath.h"
//#include "./ui_bookmath.h"
#include "varlist.h"
//#include "./ui_var_list.h"
#include "utilities/functionalities/sz_functions.h"
#include <QScreen>
#include <QStatusBar>
#include <QMenuBar>

BookMath::BookMath(QWidget *parent)
    : QMainWindow(parent)
{
    __book_initialization__();
    __load_styles__();
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
    __load_settings__();
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
    view_menu->addAction(QObject::tr("Show variables"),this,&BookMath::show_variable_list);

    menubar->addMenu(file_menu);
    menubar->addMenu(insert_menu);
    menubar->addMenu(view_menu);
    menubar->addAction(QObject::tr("Format"));
    menubar->addAction(QObject::tr("Settings"));
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
    centralwidget = new VarDataView(this);

    centralwidget->setObjectName(QString::fromUtf8("mainwidget"));
    centralwidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralwidget);
}

void BookMath::__define_signals_slots__(){
    connect(findChild<ToolButton*>("createnewbook"),&ToolButton::clicked,this,&BookMath::create_new_book);
    connect(findChild<ToolButton*>("savebook"),&ToolButton::clicked,this,&BookMath::save_book);
    QObject::connect(qobject_cast<kernel::Application*>(QApplication::instance()),&kernel::Application::language_changed,this,&BookMath::changed_language);
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

void BookMath::settings(){
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

void BookMath::changed_language(){
    using namespace kernel::settings;
    langs_->setIcon(QIcon(kernel::settings::Program::get_language_properties().path));
    retranslate();
}

BookMath::~BookMath()
{
    __save_settings__();
}

void BookMath::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("bookmath");
        if(sets_->value("geometry").isNull())
            functional::fullscreen(this);
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

void BookMath::__load_styles__(){
    if(kernel::settings::Program::get_theme() == Themes::Dark)
        setPalette(Themes::DarkStyle().palette());
    else setPalette(Themes::LightStyle().palette());
}

void BookMath::__book_initialization__(){
    pool_ = std::make_unique<DataPool>("Pool data 1");
    for(int i=0;i<3;++i)
        pool_->add_data(QString("Data base %1").arg(i).toStdString());
    kernel::Application::set_active_pool(pool_.get());
    kernel::Application::set_active_data(pool_->data_bases().at(0).get());
}
