#include "ellipse.hpp"
#include "renderer_visitor.hpp"

namespace y11::widgets {

Ellipse::Ellipse(Dimension radius_x, Dimension radius_y) {
    this->width = radius_x;
    this->height = radius_y;
}


Ellipse* Ellipse::setColor(Color color) {
    this->color = color;
    return this;
}

Color Ellipse::getColor()
{
    return this->color;
}

void Ellipse::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
