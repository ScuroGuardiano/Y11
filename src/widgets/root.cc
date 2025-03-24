#include "root.hpp"

namespace y11::widgets {

void Root::setLayoutRect(const Rect& rect) {
    layoutVisitor.setLayoutRect(rect);
}

void Root::applyLayout() {
    for (auto& widget : children) {
        widget->accept(layoutVisitor);
    }
}

}
