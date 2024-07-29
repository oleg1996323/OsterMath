#include "menuwidgets/booktoolbar.h"
#include "kernel/application.h"
#include "menuwidgets/groups/file.h"
#include "menuwidgets/groups/export.h"

namespace Book{
namespace Widgets{
ToolBar::ToolBar(QWidget* parent):QToolBar(parent), ObjectFromSettings(this){
    __load_settings__();
    setFloatable(false);
    setMovable(false);
    setContentsMargins(10,5,10,5);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QFont font;

    font.setFamily("FreeSans");
    font.setPointSize(8);
    font.setBold(true);
    setFont(font);

    tabs_=new TabbedGroupedTools(this);
    addWidget(tabs_);
}

void ToolBar::__default_init__(){
    tabs_ = new TabbedGroupedTools(this);
    QList<QGroupBox*> box;
    box.append(new Book::Widgets::toolbar::File(tabs_));
    box.append(new Book::Widgets::toolbar::Export(tabs_));
    tabs_->set_box(box, QObject::tr("Main"));
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
