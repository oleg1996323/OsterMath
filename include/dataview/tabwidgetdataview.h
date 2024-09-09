#pragma once
#include <QMainWindow>
#include <QAbstractProxyModel>
#include <QItemSelectionModel>
#include "kernel/def.h"

class BaseData;
class Node;
namespace model{
class VariablesDelegate;
class VariablesHeader;
class NodeViewDelegate;
class NodeViewHeader;
}
namespace dataview{
class NodeData;

//TODO add variable search in model
class View:public QMainWindow, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    View(QWidget* parent, BaseData* data);
    ~View();
    bool state_initialized() const;
public slots:
    QAbstractProxyModel* search_var(const QString&);
    void show_node(Node*,size_t) const;
    void set_model(QAbstractItemModel*);
    void set_selection(QItemSelectionModel*);
    NodeData* data_viewer() const;
private:
    //widget where var are illustrated
    NodeData* data_view_;
    bool state_initialized_ = false;

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
};
}
