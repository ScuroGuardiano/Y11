#include "layout.hpp"
#include "src/widgets/layout_metadata.hpp"
#include <algorithm>

namespace y11::widgets {

void Layout::accept(LayoutVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
    this->apply();
};

DefaultLayoutVisitor::DefaultLayoutVisitor() {}

DefaultLayoutVisitor::DefaultLayoutVisitor(const Rect& rect)
    : rect(rect), currentPos({ rect.x, rect.y }) {}

void DefaultLayoutVisitor::setLayoutRect(const Rect& rect) {
    this->rect = rect;
    currentPos = { rect.x, rect.y };
}

void DefaultLayoutVisitor::visit(Widget &widget, LayoutMetadata &metadata) {
    metadata.width = std::max<short>(0, widget.width.getPixelValue(rect.width));
    metadata.height = std::max<short>(0, widget.height.getPixelValue(rect.height));

    metadata.contentWidth = std::max<short>(0, metadata.width - widget.padding.totalHorizontal());
    metadata.contentHeight = std::max<short>(0, metadata.height - widget.padding.totalVertical());

    metadata.x = currentPos.x;
    metadata.y = currentPos.y;

    metadata.contentX = currentPos.x + widget.padding.left;
    metadata.contentY = currentPos.y + widget.padding.top;

    this->currentPos.y += metadata.height;
}

void DefaultLayoutVisitor::visit(Layout &layout, LayoutMetadata &metadata) {
    this->visit((Widget&)layout, metadata);
}

}

