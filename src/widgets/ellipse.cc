#include "ellipse.hpp"
#include "renderer_visitor.hpp"
#include "src/backend.hpp"

namespace y11::widgets {

Ellipse::Ellipse(Dimension radius_x, Dimension radius_y) {
    this->radius_x = radius_x.getPixelValue(2137);
    this->radius_y = radius_y.getPixelValue(2137);
}

Ellipse::Ellipse(Dimension radius_x, Dimension radius_y, const std::unique_ptr<y11::Backend>& backend) {
    this->radius_x = radius_x.getPixelValue(backend->getWidth());
    this->radius_y = radius_y.getPixelValue(backend->getHeight());
}

Ellipse* Ellipse::setDims(Dimension radius_x, Dimension radius_y) {
    this->radius_x = radius_x.getPixelValue(2137);
    this->radius_y = radius_y.getPixelValue(2137);

    return this;
}

Ellipse* Ellipse::setDims(Dimension radius_x, Dimension radius_y, const std::unique_ptr<y11::Backend>& backend) {
    this->radius_x = radius_x.getPixelValue(backend->getWidth());
    this->radius_y = radius_y.getPixelValue(backend->getHeight());

    return this;
}

short Ellipse::getRadiusX()
{
    return this->radius_x;
}

short Ellipse::getRadiusY()
{
    return this->radius_y;
}

Ellipse* Ellipse::setColor(Color color) {
    this->color = color;
    return this;
}

Color* Ellipse::getColor()
{
    return &this->color;
}

unsigned short Ellipse::measureWidth()
{
    return radius_x * 2 + padding.totalHorizontal();
}

unsigned short Ellipse::measureHeight()
{
    return radius_y * 2 + padding.totalVertical();
}

void Ellipse::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
