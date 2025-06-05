#include "text.hpp"
#include "renderer_visitor.hpp"
#include "src/backend.hpp"
#include <string>

namespace y11::widgets {

Text::Text(unsigned short height){
    this->height = height;
}

Text* Text::setString(std::string stuff) {
    this->stuff = stuff;
    return this;
}

std::string Text::getString()
{
    return this->stuff;
}

Text* Text::setColor(Color color) {
    this->color = color;
    return this;
}

Text* Text::setWidth(float width) {
    this->width = width;
    return this;
}

Color Text::getColor()
{
    return this->color;
}

unsigned short Text::getHeight() {
    return this->height;
}

unsigned short Text::measureWidth()
{
    return width;
    // return stuff.length() * height + padding.totalHorizontal();
}

unsigned short Text::measureHeight()
{
    return height + padding.totalVertical();
}

void Text::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
