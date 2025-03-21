#include "sfml_renderer.hpp"
#include "src/backends/sfml/sfml_widget_metadata.hpp"
#include "src/widgets/rectangle.hpp"
#include <algorithm>
#include <memory>

namespace y11 {

SfmlRenderer::SfmlRenderer(sf::RenderWindow& window) : window(window) {}

void SfmlRenderer::visit(widgets::Rectangle &rect) {
    auto metadata = std::make_unique<SfmlWidgetMetadata>();

    metadata->x = currentPos.x;
    metadata->y = currentPos.y;

    metadata->width = std::max<short>(0, rect.width.getPixelValue(getWidth(rect.padding)));
    metadata->height = std::max<short>(0, rect.height.getPixelValue(getWidth(rect.padding)));

    sf::RectangleShape sf_rect({ (float)metadata->width, (float)metadata->height });
    sf_rect.setPosition(currentPos.x + rect.padding.left, currentPos.y + rect.padding.top);
    sf_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));

    window.draw(sf_rect);

    // In default renderer we only change height, because we render elements
    // in vertical column
    currentPos.y += rect.padding.top + metadata->height + rect.padding.bottom;
    rect._rendererMetadata = std::move(metadata);
}

}
