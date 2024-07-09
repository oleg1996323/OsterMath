#pragma once
#include <QMainWindow>
#include <QAbstractProxyModel>

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

class View:public QMainWindow{
    Q_OBJECT
public:
    View(QWidget* parent, BaseData* data);
public slots:
    QAbstractProxyModel* search_var(const QString&);
    void show_variable_list();
private:
    //widget where var are illustrated
    DockWidget* var_list_;
    NodeData* data_view_;
    model::VariablesDelegate* var_list_delegate_;
    model::VariablesHeader* var_list_header_;
    model::NodeViewDelegate* node_view_delegate_;
    model::NodeViewHeader* node_view_header_;
};
}
