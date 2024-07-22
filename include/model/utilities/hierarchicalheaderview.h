#pragma once
#include <QHeaderView>

class HierarchicalHeaderView : public QHeaderView
{
        Q_OBJECT

        class private_data;
        private_data* _pd;

        QStyleOptionHeader styleOptionForCell(int logicalIndex) const;

    protected:
        virtual void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
        virtual QSize sectionSizeFromContents(int logicalIndex) const override;
    public:

        enum HeaderDataModelRoles
            {HorizontalHeaderDataRole=Qt::UserRole,
             VerticalHeaderDataRole=Qt::UserRole+1};

        HierarchicalHeaderView(Qt::Orientation orientation, QWidget* parent = 0);
        ~HierarchicalHeaderView();

        virtual void setModel(QAbstractItemModel* model) override;
    private slots:
        void on_sectionResized(int logicalIndex);
};
