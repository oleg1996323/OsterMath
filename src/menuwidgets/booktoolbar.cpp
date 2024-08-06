#include "menuwidgets/booktoolbar.h"
#include "kernel/application.h"
#include "menuwidgets/groups/file.h"
#include "menuwidgets/groups/export.h"

namespace Book{
namespace Widgets{
ToolBar::ToolBar(QWidget* parent):QToolBar(parent), ObjectFromSettings(this){
    __load_settings__();
}

void ToolBar::__default_init__(){
    setFloatable(false);
    setMovable(false);
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setBackgroundRole(QPalette::Window);
    QFont font;

    font.setFamily("FreeSans");
    font.setPointSize(8);
    font.setBold(true);
    setFont(font);
    tabs_ = new TabbedGroupedTools(this);
    QList<QGroupBox*> box;
    box.append(new Book::Widgets::toolbar::File(tabs_));
    box.append(new Book::Widgets::toolbar::Export(tabs_));
    tabs_->set_box(box, QObject::tr("Main"));
    //TODO
//    box.clear();
//    box.append(new QGroupBox("Any_1",tabs_));
//    box.append(new QGroupBox("Any_2",tabs_));
//    tabs_->set_box(box, "Any");
    tabs_->setLayoutsContentsMargins(0,0,0,0);
    tabs_->setGroupsMargins(0,0,0,0);
    addWidget(tabs_);
}

void ToolBar::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    __default_init__();
}
void ToolBar::__save_settings__(){

}
void ToolBar::__upload_fonts__(){

}
void ToolBar::__upload_style__(){

}
void ToolBar::__upload_language__(){

}
}
}
