#pragma once
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>
#include <QFont>
#include <QSizePolicy>
#include <kernel/styles.h>
#include "kernel/exception.h"
#include "utilities/validators/validator.h"
#include "model/nodeview_header.h"
#include "kernel/application.h"
#include "dataview/tabwidgetdataview.h"
#include "model/manager.h"

#include <QMessageBox>

namespace dataview{
class Sheets:public QTabWidget{
    Q_OBJECT
public:
    Sheets(QWidget* parent);

    Sheets(QWidget* parent, const QString& data_name);

    ~Sheets();

    virtual void tabRemoved(int index) override;

    void rename(const QString& name);

    void init_new_pool();

    void erase_sheet(const QString& name) noexcept;

    void change_sheet_name(QString&& name, int tab_id);

    virtual void tabInserted(int id) override;

    void add_default_sheet(int after);

    void add_default_sheet();

private:

    void __init__(){
        setTabPosition(QTabWidget::South);
    }

    void __load_settings__();

    void __save_settings__();

    model::Manager manager_;
    QList<View*> central_view_tabs_;
    DockWidget* var_list_;

private slots:
    void __change_dock_to__(QMainWindow*);
};
}
