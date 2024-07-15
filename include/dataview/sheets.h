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
class Sheets:public QTabWidget, public Retranslatable, public ObjectFromSettings{
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

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;

    model::Manager manager_;
    DockWidget* var_list_;

    signals:
    void set_model_to_var_list(QAbstractItemModel*);

private slots:
    void __change_dock_to__(View*);
};
}
