#include "text.hpp"
#include "renderer_visitor.hpp"
#include <string>

namespace y11::widgets {

Text::Text( std::string stuff ){
    this->stuff = stuff;
}

unsigned short Text::getLetterHeight() {
    return this->lH;
}

Text* Text::setLetterHeight( unsigned short height ) {
    this->lH = height;
    return this;
}

Color Text::getColor(){
    return this->color;
}

Text* Text::setColor(Color color) {
    this->color = color;
    return this;
}

std::string Text::getString()
{
    return this->stuff;
}

Text* Text::setString(std::string stuff) {
    this->stuff = stuff;
    return this;
}

#if defined(Y11_BACKEND_USE_BLANK)
unsigned short Text::measureWidth(){
    return stuff.length() * height + padding.totalHorizontal();
}

#elif defined(Y11_BACKEND_USE_SFML)
unsigned short Text::measureWidth(){
    sf::Font font;
    font.loadFromFile("src/FiraCode.ttf");
    sf::Text txt;
    txt.setString(this->stuff);
    txt.setFont(font);
    txt.setCharacterSize(this->lH);
    return txt.getLocalBounds().width;
}
#endif

unsigned short Text::measureHeight()
{
    return lH + padding.totalVertical();
}

void Text::accept(RendererVisitor& visitor) {
    visitor.visit(*this, this->layoutMetadata);
}

}
