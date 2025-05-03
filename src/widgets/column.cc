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

        return padding.totalHorizontal() + maxWidth;
    }

    return std::max<unsigned short>(padding.totalHorizontal(), width);
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

        return padding.totalVertical() + childrenHeightSum;
    }

    return std::max<unsigned short>(height, padding.totalVertical());
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
    innerRect.x = column.layoutMetadata.contentX;
    innerRect.y = column.layoutMetadata.contentY;

    innerRect.width = column.layoutMetadata.contentWidth;
    innerRect.height = column.layoutMetadata.contentHeight;

    currentY = innerRect.y;

    // For now height can only grow if column is set to fit content
    heightGrow = column.height.isAuto() || column.height.isFitContent();
}



void Column::ColumnLayoutVisitor::visit(Widget& widget, LayoutMetadata& metadata) {
    // x pos and width
    // x and width are easy because we have only 1 element occupying the space

    Sizing hSizing = widget.getHorizontalSizing();
    short w = 0;

    if (hSizing == Sizing::FIT_CONTENT) {
        w = widget.measureWidth();
    }
    else if (hSizing == Sizing::EXPAND) {
        w = innerRect.width;
    }
    else {
        w = widget.width.getPixelValue(innerRect.width);
    }

    if (w > innerRect.width) {
        metadata.overflow = true;
    }

    metadata.x = innerRect.x;
    metadata.contentX = innerRect.x + widget.padding.left;
    metadata.width = std::max<short>(0, w);
    metadata.contentWidth = std::max<short>(0, metadata.width - widget.padding.totalHorizontal());

    // y pos and width
    // Now it's fun! XD And I don't know how to do it
    
    if (heightGrow) {
        // Let's go with easier path first, if height is growing then all percent values
        // and expand values are just 0, because we can't calculate them reliably
        // In other words, if `measureHeight` returns 0 to us then height of an element is zero.

        short h = widget.measureHeight();

        metadata.y = currentY;
        metadata.contentY = metadata.y + widget.padding.top;
        metadata.height = h;
        metadata.contentHeight = std::max<short>(0, metadata.height - widget.padding.totalVertical());

        currentY += metadata.height + column.gap;
    }

}

} // namespace y11::widgets

