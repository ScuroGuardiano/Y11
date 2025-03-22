#include "widget.hpp"
#include "layout.hpp"

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

AutoSizeHint Widget::getAutoSizeHint() {
    return AutoSizeHint::FIT_CONTENT;
}

void Widget::accept(LayoutVisitor& visitor) {
    visitor.visit(*this, layoutMetadata);
};

Widget* Widget::setPadding(Padding padding) {
    this->padding = padding;

    return this;
}

bool Widget::hasChildren() {
    return false;
}

std::shared_ptr<Widget> Widget::getWidgetById(unsigned short _) {
    return nullptr;
}

bool Widget::removeWidget(const std::shared_ptr<Widget> _) {
    return false;
}
bool Widget::removeWidgetById(unsigned short _) {
    return false;
}

}

