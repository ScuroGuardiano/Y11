#pragma once

#include <SFML/Graphics.hpp>
#include "src/widgets/column.hpp"
#include "src/widgets/layout_metadata.hpp"
#include "src/widgets/renderer_visitor.hpp"
#include "src/widgets/row.hpp"

namespace y11 {

class SfmlRenderer : public widgets::RendererVisitor {
public:
    SfmlRenderer(sf::RenderWindow& window);
    void visit(widgets::Rectangle &rect, const widgets::LayoutMetadata& layoutMetadata) override;
    void visit(widgets::Ellipse &ellipse, const widgets::LayoutMetadata& layoutMetadata) override;
    void visit(widgets::Column &column, const widgets::LayoutMetadata& layoutMetadata) override;
    void visit(widgets::Row &row, const widgets::LayoutMetadata& layoutMetadata) override;
    void visit(widgets::Circle &circle, const widgets::LayoutMetadata& layoutMetadata) override;
    void visit(widgets::Text& text, const widgets::LayoutMetadata& LayoutMetadata) override;

private:
    unsigned int getWidth(const Padding& padding) {
        return window.getSize().x - padding.left - padding.right;
    }

    unsigned int getHeight(const Padding& padding) {
        return window.getSize().y - padding.top - padding.bottom;
    }

    sf::RenderWindow& window;
};

}

