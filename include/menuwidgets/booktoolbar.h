#pragma once
#include <QToolBar>
#include <QTabWidget>
#include "utilities/custom_widgets/tabbed_toolbox_group.h"
#include "kernel/def.h"

namespace Book{
namespace Widgets{
class ToolBar:public QToolBar, public ObjectFromSettings{
    Q_OBJECT
public:
    ToolBar(QWidget* parent);
private:
    TabbedGroupedTools *tabs_;
    void __default_init__();
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
};
}
}
