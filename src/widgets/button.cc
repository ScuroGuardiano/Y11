#include "button.hpp"
#include "renderer_visitor.hpp"

namespace y11::widgets {

Button::Button(Dimension width, Dimension height) {
    this->width = width;
    this->height = height;
}

Color Button::getColor(){
    return this->color;
}

Button* Button::setColor(Color color) {
    this->color = color;
    return this;
}

void Button::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
