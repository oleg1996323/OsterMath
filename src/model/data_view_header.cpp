#include "model/data_view_header.h"
#include "model/varlistmodel.h"
#include "types.h"
#include "arithmetic_functions.h"

namespace model {

void DataViewHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const{
    const Variables *model =
            qobject_cast<Variables *>(this->model());

    std::vector<size_t> sz_depth_measure;
    if(var_->is_array())
        functions::auxiliary::init_sz_depth_measure(sz_depth_measure,reinterpret_cast<ArrayNode*>(var_->node()->child(0).get()));

    const size_t depth = sz_depth_measure.size();
    for (int i = 0; i < depth; ++i) {
        QModelIndex cellIndex = (orientation() == Qt::Horizontal)
                ? model->index(i, logicalIndex)
                : model->index(logicalIndex, i);
        QSize cellSize = cellIndex.data(Qt::SizeHintRole).toSize();
        QRect sectionRect(rect);

        // set position of the cell
        if (orientation() == Qt::Horizontal)
            sectionRect.setTop(
                        rowSpanSize(logicalIndex, 0, i)); // distance from 0 to i-1 rows
        else
            sectionRect.setLeft(columnSpanSize(logicalIndex, 0, i));

        sectionRect.setSize(cellSize);

        // check up span column or row
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        if (colSpanIdx.isValid()) {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt =
                    colSpanIdx.data(GridTableHeaderModel::ColumnSpanRole).toInt();
            int colSpanTo = colSpanFrom + colSpanCnt - 1;
            int colSpan = columnSpanSize(cellIndex.row(), colSpanFrom, colSpanCnt);
            if (orientation() == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else {
                sectionRect.setLeft(columnSpanSize(logicalIndex, 0, colSpanFrom));
                i = colSpanTo;
            }

            sectionRect.setWidth(colSpan);

            // check up  if the column span index has row span
            QVariant subRowSpanData =
                    colSpanIdx.data(GridTableHeaderModel::RowSpanRole);
            if (subRowSpanData.isValid()) {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt = subRowSpanData.toInt();
                int subRowSpanTo = subRowSpanFrom + subRowSpanCnt - 1;
                int subRowSpan =
                        rowSpanSize(colSpanFrom, subRowSpanFrom, subRowSpanCnt);
                if (orientation() == Qt::Vertical)
                    sectionRect.setTop(sectionViewportPosition(subRowSpanFrom));
                else {
                    sectionRect.setTop(rowSpanSize(colSpanFrom, 0, subRowSpanFrom));
                    i = subRowSpanTo;
                }
                sectionRect.setHeight(subRowSpan);
            }
            cellIndex = colSpanIdx;
        }
        if (rowSpanIdx.isValid()) {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt =
                    rowSpanIdx.data(GridTableHeaderModel::RowSpanRole).toInt();
            int rowSpanTo = rowSpanFrom + rowSpanCnt - 1;
            int rowSpan = rowSpanSize(cellIndex.column(), rowSpanFrom, rowSpanCnt);
            if (orientation() == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else {
                sectionRect.setTop(rowSpanSize(logicalIndex, 0, rowSpanFrom));
                i = rowSpanTo;
            }
            sectionRect.setHeight(rowSpan);

            // check up if the row span index has column span
            QVariant subColSpanData =
                    rowSpanIdx.data(GridTableHeaderModel::ColumnSpanRole);
            if (subColSpanData.isValid()) {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt = subColSpanData.toInt();
                int subColSpanTo = subColSpanFrom + subColSpanCnt - 1;
                int subColSpan =
                        columnSpanSize(rowSpanFrom, subColSpanFrom, subColSpanCnt);
                if (orientation() == Qt::Horizontal)
                    sectionRect.setLeft(sectionViewportPosition(subColSpanFrom));
                else {
                    sectionRect.setLeft(columnSpanSize(rowSpanFrom, 0, subColSpanFrom));
                    i = subColSpanTo;
                }
                sectionRect.setWidth(subColSpan);
            }
            cellIndex = rowSpanIdx;
        }

        // draw section with style
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        opt.textAlignment = Qt::AlignCenter;
        opt.iconAlignment = Qt::AlignVCenter;
        opt.section = logicalIndex;
        opt.text = cellIndex.data(Qt::DisplayRole).toString();
        opt.rect = sectionRect;

        QVariant bg = cellIndex.data(Qt::BackgroundRole);
        QVariant fg = cellIndex.data(Qt::ForegroundRole);
        if (bg.canConvert<QBrush>()) {
            opt.palette.setBrush(QPalette::Button, bg.value<QBrush>());
            opt.palette.setBrush(QPalette::Window, bg.value<QBrush>());
        }
        if (fg.canConvert<QBrush>()) {
            opt.palette.setBrush(QPalette::ButtonText, fg.value<QBrush>());
        }

        painter->save();
        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
        painter->restore();
    }
}

}
