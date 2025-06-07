#include "rectangle.hpp"
#include "renderer_visitor.hpp"

namespace y11::widgets {

Rectangle::Rectangle(Dimension width, Dimension height) {
    this->width = width;
    this->height = height;
}

Color Rectangle::getColor(){
    return this->color;
}

Rectangle* Rectangle::setColor(Color color) {
    this->color = color;
    return this;
}

void Rectangle::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
