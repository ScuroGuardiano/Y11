#include "column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/renderer_visitor.hpp"

namespace y11::widgets {

AutoSizeHint Column::getWidthAutoSizeHint() {
    return AutoSizeHint::EXPAND;
}

unsigned short Column::measureWidth() {
    unsigned short width = 0;

    if (this->width.getUnit() == DimensionUnit::PIXEL) {
        // In case of pixel unit, value passed here doesn't matter
        width = std::max<short>(0, this->width.getPixelValue(2137));
    }
    else if (this->width.getUnit() == DimensionUnit::FIT_CONTENT)
    {
        // Now where's the fun begins
        unsigned short maxWidth = 0;
        for (auto& w : children) {
            auto measurement = w->measureWidth();
            if (measurement > maxWidth) {
                maxWidth = measurement;
            }
        }

        return padding.totalHorizontal() + innerPadding.totalHorizontal() + maxWidth;
    }

    return std::max<unsigned short>(padding.totalHorizontal() + innerPadding.totalHorizontal(), width);
}

unsigned short Column::measureHeight() {
    unsigned short height = 0;

    if (this->height.getUnit() == DimensionUnit::PIXEL) {
        height = std::max<short>(0, this->height.getPixelValue(2137));
    }
    else if (this->height.getUnit() == DimensionUnit::FIT_CONTENT)
    {
        unsigned short childrenHeightSum = 0;

        for (auto& w : children) {
            childrenHeightSum += w->measureHeight();
        }

        return padding.totalVertical() + innerPadding.totalVertical() + childrenHeightSum;
    }

    return std::max<unsigned short>(height, padding.totalVertical() + innerPadding.totalVertical());
}

void Column::accept(RendererVisitor& visitor) {
    visitor.visit(*this, layoutMetadata);
}

void Column::accept(LayoutVisitor& layoutVisitor) {
    layoutVisitor.visit(*this, layoutMetadata);
    this->applyLayout();
}

void Column::applyLayout() {
    ColumnLayoutVisitor visitor(*this);

    for (auto& w : children) {
        w->accept(visitor);
    }
}

Column* Column::setInnerPadding(Padding padding) {
    this->innerPadding = padding;
    return this;
}

Column* Column::setGap(unsigned short gap) {
    this->gap = gap;
    return this;
}

Column* Column::setAlignment(HorizontalAlignment alignment) {
    this->alignment = alignment;
    return this;
}

Column* Column::setArrangement(Arrangement arrangement) {
    this->arrangement = arrangement;
    return this;
}

Column::ColumnLayoutVisitor::ColumnLayoutVisitor(const Column& column)
: column(column) {
    innerRect.x = column.layoutMetadata.x + column.innerPadding.left;
    innerRect.y = column.layoutMetadata.y + column.innerPadding.top;
    short w = innerRect.width - column.innerPadding.totalHorizontal();
    short h = innerRect.height - column.innerPadding.totalVertical();

    innerRect.width = std::max<short>(0, w);
    innerRect.height = std::max<short>(0, h);

    currentY = innerRect.y;

    // For now height can only grow if column is set to fit content
    heightGrow = column.height.isAuto() || column.height.isFitContent();
}



void Column::ColumnLayoutVisitor::visit(Widget& widget, LayoutMetadata& metadata) {

}

} // namespace y11::widgets

