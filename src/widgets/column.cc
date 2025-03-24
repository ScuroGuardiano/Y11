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

    return height;
}

void Column::accept(RendererVisitor& visitor) {
    visitor.visit(*this, layoutMetadata);
}

void Column::accept(LayoutVisitor& layoutVisitor) {
    layoutVisitor.visit(*this, layoutMetadata);
    this->applyLayout();
}

void Column::applyLayout() {

}

} // namespace y11::widgets

