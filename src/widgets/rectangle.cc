#include "rectangle.hpp"
#include "renderer_visitor.hpp"

namespace y11::widgets {

Rectangle::Rectangle(unsigned short width, unsigned short height)
: width(width), height(height) {}

Rect Rectangle::getBoundingRect() {
    return Rect(x, y, width, height);
}

Size Rectangle::getSize() {
    return Size(width, height);
}

Point Rectangle::getPos() {
    return Point(x, y);
}

void Rectangle::setPos(short x, short y) {
    this->x = x;
    this->y = y;
}

void Rectangle::accept(RendererVisitor& visitor) {
    visitor.visit(*this);
}

}

