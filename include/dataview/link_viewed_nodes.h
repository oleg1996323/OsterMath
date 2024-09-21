#pragma once
#include <QWidget>
#include <PushLabel.h>
#include "kernel/def.h"
#include "node.h"
#include <QSignalMapper>
#include <QMouseEvent>

struct INFO_NODE;
class QHBoxLayout;
namespace dataview{
class LinkViewedNodes:public QWidget,public ObjectFromSettings,public Retranslatable{
    Q_OBJECT
public:
    LinkViewedNodes(QWidget* parent);
    void reset();
signals:
    void update_sequence(std::vector<INFO_NODE>);
public slots:
    void add_button(INFO_NODE);
private:
    virtual void __retranslate__() override;
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_language__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
private slots:
    void activated_button();
private:
    class LinkButton:public PushLabel{
    public:
        LinkButton(QString,QWidget*,int32_t pos);
        int get_pos() const;
        void set_pos(int32_t pos);
        LinkButton* push_next(LinkButton*);
        void erase_next();
        LinkButton* last();
        void set_info(INFO_NODE info);
        LinkButton* get_next() const;
        std::vector<INFO_NODE> get_sequence() const;
    protected:
        virtual void paintEvent(QPaintEvent*) override;
        virtual QSize sizeHint() const override;
        virtual void mouseMoveEvent(QMouseEvent *) override;
        virtual void mousePressEvent(QMouseEvent *) override;
        virtual void leaveEvent(QEvent*) override;
    private:
        void draw_link_arrow(QPainter& painter);
        std::vector<INFO_NODE> __get_sequence__(std::vector<INFO_NODE>&) const;
        QRect area;
        INFO_NODE info_;
        LinkButton* next_ = nullptr;
        int32_t pos_=-1;
        static uint8_t arrowSize;
        static uint8_t arrowLenght;
        static uint8_t arrowTextSpacing;
        static uint8_t arrowTotalLength();
    };
    void __add_button__(const QString&, INFO_NODE);
    LinkButton* root_ = nullptr;
    QHBoxLayout* layout_;
};

}
