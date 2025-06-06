#include "circle.hpp"
#include "renderer_visitor.hpp"
#include "src/widgets/common.hpp"

namespace y11::widgets {

Circle::Circle(Dimension radius) {
    this->width = radius*2.0;
    this->height = radius*2.0;
}


Circle* Circle::setColor(Color color)
{
    this->color = color;
    return this;
}

Color Circle::getColor()
{
    return this->color;
}

Circle* Circle::setRadius(Dimension radius)
{
    this->width = radius*2.0;
    this->height = radius*2.0;
    return this;
}

Dimension Circle::getRadius()
{
    return this->width*0.5;
}


void Circle::accept(RendererVisitor& visitor)
{
    visitor.visit(*this, this->layoutMetadata);
}

}
