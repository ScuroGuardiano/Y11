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
    sf::RenderWindow& window;
    Point currentPos{};
};

}

