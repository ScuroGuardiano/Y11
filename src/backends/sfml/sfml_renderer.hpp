#pragma once

#include <SFML/Graphics.hpp>
#include "src/point.hpp"
#include "src/widgets/renderer_visitor.hpp"

namespace y11 {

class SfmlRenderer : public widgets::RendererVisitor {
public:
    SfmlRenderer(sf::RenderWindow& window);
    void visit(widgets::Rectangle &rect) override;

private:
    unsigned int getWidth(const Padding& padding) {
        return window.getSize().x - padding.left - padding.right;
    }

    unsigned int getHeight(const Padding& padding) {
        return window.getSize().y - padding.top - padding.bottom;
    }

    sf::RenderWindow& window;
    Point currentPos{};
};

}

