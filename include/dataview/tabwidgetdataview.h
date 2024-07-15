#pragma once
#include <QMainWindow>
#include <QAbstractProxyModel>
#include "kernel/def.h"

class BaseData;
namespace model{
class VariablesDelegate;
class VariablesHeader;
class NodeViewDelegate;
class NodeViewHeader;
}
namespace dataview{
class DockWidget;
class NodeData;

class View:public QMainWindow, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    View(QWidget* parent, BaseData* data);
    ~View();
    bool state_initialized() const;
public slots:
    QAbstractProxyModel* search_var(const QString&);
    void show_variable_list(QModelIndex index) const;
private:
    //widget where var are illustrated
    DockWidget* var_list_;
    NodeData* data_view_;

    model::NodeViewDelegate* node_view_delegate_;
    model::NodeViewHeader* node_view_header_;
    bool state_initialized_ = false;

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
};
}
