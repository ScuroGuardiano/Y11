#include "layout.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/layout_metadata.hpp"
#include <algorithm>

namespace y11::widgets {

void Layout::accept(LayoutVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
    this->applyLayout();
};

DefaultLayoutVisitor::DefaultLayoutVisitor() {}

DefaultLayoutVisitor::DefaultLayoutVisitor(const Rect& rect)
    : rect(rect), currentPos({ rect.x, rect.y }) {}

void DefaultLayoutVisitor::setLayoutRect(const Rect& rect) {
    this->rect = rect;
    currentPos = { rect.x, rect.y };
}

void DefaultLayoutVisitor::visit(Widget &widget, LayoutMetadata &metadata) {
    // Width
    bool expand = widget.width.isAuto() && widget.getWidthAutoSizeHint() == AutoSizeHint::EXPAND;
    bool fitContent = (widget.width.isAuto() && widget.getWidthAutoSizeHint() == AutoSizeHint::FIT_CONTENT)
        || widget.width.isFitContent();

    short w = expand ? rect.width
        : fitContent ? widget.measureWidth() : widget.width.getPixelValue(rect.width);

    // Height
    expand = widget.height.isAuto() && widget.getHeightAutoSizeHint() == AutoSizeHint::EXPAND;
    fitContent = (widget.height.isAuto() && widget.getHeightAutoSizeHint() == AutoSizeHint::FIT_CONTENT)
        || widget.height.isFitContent();

    short h = expand ? rect.height
        : fitContent ? widget.measureHeight() : widget.height.getPixelValue(rect.height);


    metadata.width = std::max<short>(0, w);
    metadata.height = std::max<short>(0, h);

    metadata.contentWidth = std::max<short>(0, metadata.width - widget.padding.totalHorizontal());
    metadata.contentHeight = std::max<short>(0, metadata.height - widget.padding.totalVertical());

    metadata.x = currentPos.x;
    metadata.y = currentPos.y;

    metadata.contentX = currentPos.x + widget.padding.left;
    metadata.contentY = currentPos.y + widget.padding.top;

    this->currentPos.y += metadata.height;
}

}

