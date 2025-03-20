#include "sfml_renderer.hpp"
#include "src/widgets/rectangle.hpp"

namespace y11 {

SfmlRenderer::SfmlRenderer(sf::RenderWindow& window) : window(window) {}

void SfmlRenderer::visit(widgets::Rectangle &rect) {
    rect.setPos(currentPos.x, currentPos.y);
    auto size = rect.getSize();

    sf::RectangleShape sf_rect({ (float)size.width, (float)size.height });
    sf_rect.setPosition(currentPos.x + rect.padding.left, currentPos.y + rect.padding.top);
    sf_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));

    window.draw(sf_rect);

    // In default renderer we only change height, because we render elements
    // in vertical column
    currentPos.y += rect.padding.top + size.height + rect.padding.bottom;
}

}
