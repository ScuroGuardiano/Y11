#include "widget.hpp"

namespace y11::widgets {

Widget::~Widget() {}

Point Widget::getPos() {
    if (_rendererMetadata == nullptr) {
        return {};
    }
    return _rendererMetadata->getPos();
}

Size Widget::getSize() {
    if (_rendererMetadata == nullptr) {
        return {};
    }
    return _rendererMetadata->getSize();
}

Rect Widget::getBoundingRect() {
    if (_rendererMetadata == nullptr) {
        return {};
    }
    return _rendererMetadata->getBoudingRect();
}

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

