#include "circle.hpp"
#include "renderer_visitor.hpp"

namespace y11::widgets {

Circle::Circle(short radius)
    : radius(radius) {}

Circle* Circle::setColor(Color color)
{
    this->color = color;
    return this;
}

Color Circle::getColor()
{
    return this->color;
}

Circle* Circle::setRadius(short radius)
{
    this->radius = radius;
    return this;
}

short Circle::getRadius()
{
    return this->radius;
}

unsigned short Circle::measureWidth()
{
    return radius * 2 + padding.totalHorizontal();
}

unsigned short Circle::measureHeight()
{
    return radius * 2 + padding.totalVertical();
}

void Circle::accept(RendererVisitor& visitor)
{
    visitor.visit(*this, this->layoutMetadata);
}

}
