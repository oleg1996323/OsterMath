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
public slots:
    QAbstractProxyModel* search_var(const QString&);
    void show_variable_list();
    void set_node_view_delegate(model::NodeViewDelegate*);
    void set_variables_delegate(model::VariablesDelegate*);
    void set_node_view_header(model::NodeViewHeader*);
    void set_variables_header(model::NodeViewHeader*);
private:
    //widget where var are illustrated
    DockWidget* var_list_;
    NodeData* data_view_;

    model::NodeViewDelegate* node_view_delegate_;
    model::NodeViewHeader* node_view_header_;

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void upload_fonts() override;
    virtual void upload_style() override;
    virtual void upload_language() override;
    virtual void retranslate() override;
};
}
