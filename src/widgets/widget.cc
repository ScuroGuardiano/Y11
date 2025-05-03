#include "widget.hpp"
#include "layout.hpp"
#include <algorithm>
#include "src/widgets/common.hpp"

namespace y11::widgets {

Widget::~Widget() {}

Point Widget::getPos() {
    return { layoutMetadata.x, layoutMetadata.y };
}

Size Widget::getSize() {
    return { layoutMetadata.width, layoutMetadata.height };
}

Rect Widget::getBoundingRect() {
    return {
        layoutMetadata.x,
        layoutMetadata.y,
        layoutMetadata.width,
        layoutMetadata.height
    };
}

AutoSizeHint Widget::getWidthAutoSizeHint() {
    return AutoSizeHint::FIT_CONTENT;
}

AutoSizeHint Widget::getHeightAutoSizeHint() {
    return AutoSizeHint::FIT_CONTENT;
}

Sizing Widget::getHorizontalSizing() {
    switch (width.getUnit()) {
        case DimensionUnit::PIXEL:
            return Sizing::PIXEL;
        case DimensionUnit::PERCENT:
            return Sizing::PERCENT;
        case DimensionUnit::FIT_CONTENT:
            return Sizing::FIT_CONTENT;
        case DimensionUnit::AUTO:
            if (getWidthAutoSizeHint() == AutoSizeHint::FIT_CONTENT) {
                return Sizing::FIT_CONTENT;
            }
            else {
                return Sizing::EXPAND;
            }
    }
}

Sizing Widget::getVerticalSizing() {
    switch (height.getUnit()) {
        case DimensionUnit::PIXEL:
            return Sizing::PIXEL;
        case DimensionUnit::PERCENT:
            return Sizing::PERCENT;
        case DimensionUnit::FIT_CONTENT:
            return Sizing::FIT_CONTENT;
        case DimensionUnit::AUTO:
            if (getHeightAutoSizeHint() == AutoSizeHint::FIT_CONTENT) {
                return Sizing::FIT_CONTENT;
            }
            else {
                return Sizing::EXPAND;
            }
    }
}

Size Widget::measure() {
    return { this->measureWidth(), this->measureHeight() };
}

unsigned short Widget::measureWidth() {
    unsigned short width = 0;

    if (this->width.getUnit() == DimensionUnit::PIXEL) {
        // In case of pixel unit, value passed here doesn't matter
        width = std::max<short>(0, this->width.getPixelValue(2137));
    }

    return std::max<unsigned short>(width, padding.totalHorizontal());
}

unsigned short Widget::measureHeight() {
    unsigned short height = 0;

    if (this->height.getUnit() == DimensionUnit::PIXEL) {
        height = std::max<short>(0, this->height.getPixelValue(2137));
    }

    return std::max<unsigned short>(height, padding.totalVertical());
}

void Widget::accept(LayoutVisitor& visitor) {
    visitor.visit(*this, layoutMetadata);
};

Widget* Widget::setPadding(Padding padding) {
    this->padding = padding;

    return this;
}

}

