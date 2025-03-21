#include "sfml_renderer.hpp"
#include "src/widgets/layout_metadata.hpp"
#include "src/widgets/rectangle.hpp"

namespace y11 {

SfmlRenderer::SfmlRenderer(sf::RenderWindow& window) : window(window) {}

void SfmlRenderer::visit(widgets::Rectangle &rect, const widgets::LayoutMetadata &metadata) {
    sf::RectangleShape sf_rect({ (float)metadata.contentWidth, (float)metadata.contentHeight });

    sf_rect.setPosition(metadata.contentX, metadata.contentY);
    sf_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));

    window.draw(sf_rect);
}

}

