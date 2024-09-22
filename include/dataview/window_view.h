#pragma once
#include <QMainWindow>
#include <QAbstractProxyModel>
#include <QItemSelectionModel>
#include "kernel/def.h"

class BaseData;
struct INFO_NODE;
class Node;
namespace model{
class VariablesDelegate;
class VariablesHeader;
class NodeViewDelegate;
class NodeViewHeader;
}
namespace utilities::windows{
class FunctionWizard;
}
namespace dataview{
class NodeData;
class LinkViewedNodes;

//TODO add variable search in model
class WindowView:public QMainWindow, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    WindowView(QWidget* parent, BaseData* data);
    ~WindowView();
    bool state_initialized() const;
public slots:
    QAbstractProxyModel* search_var(const QString&);
    void show_variable(Node*,int) const;
    void set_model(QAbstractItemModel*);
    void set_selection(QItemSelectionModel*);
    NodeData* data_viewer() const;
private:
    //widget where var are illustrated
    NodeData* data_view_;
    LinkViewedNodes* link_viewed_nodes_;
    utilities::windows::FunctionWizard* wizard_window;
    bool state_initialized_ = false;

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
};
}
