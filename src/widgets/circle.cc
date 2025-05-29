#include "circle.hpp"
#include "renderer_visitor.hpp"
#include "src/widgets/common.hpp"

namespace y11::widgets {

Circle::Circle(Dimension radius)
    : radius(radius.getPixelValue(2137)) {}

Circle::Circle(Dimension radius, const std::unique_ptr<y11::Backend>& backend)
    : radius(radius.getPixelValue(backend->getWidth())) {}

Circle* Circle::setColor(Color color)
{
    this->color = color;
    return this;
}

Color* Circle::getColor()
{
    return &this->color;
}

Circle* Circle::setRadius(Dimension radius)
{
    this->radius = radius.getPixelValue(2137);
    return this;
}

Circle* Circle::setRadius(Dimension radius, const std::unique_ptr<y11::Backend>& backend)
{
    this->radius = radius.getPixelValue(backend->getWidth());
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
