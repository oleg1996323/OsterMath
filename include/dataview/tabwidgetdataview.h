#pragma once
#include <QMainWindow>
#include <QAbstractProxyModel>

namespace dataview{

class DockWidget;
class NodeData;
class BaseData;

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
};
}
