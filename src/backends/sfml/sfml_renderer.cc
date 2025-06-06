#include "sfml_renderer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "src/widgets/layout_metadata.hpp"
#include "src/widgets/rectangle.hpp"
#include "src/widgets/widget.hpp"

namespace y11 {

SfmlRenderer::SfmlRenderer(sf::RenderWindow& window) : window(window) {}

void SfmlRenderer::visit(widgets::Rectangle &rect, const widgets::LayoutMetadata &metadata) {
    sf::RectangleShape sf_rect({ (float)metadata.contentWidth, (float)metadata.contentHeight });

    sf_rect.setPosition(metadata.contentX, metadata.contentY);
    sf_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));

    window.draw(sf_rect);
}

void SfmlRenderer::visit(widgets::Ellipse &ellipse, const widgets::LayoutMetadata &metadata) {

    float width = (float)ellipse.getWidth().getPixelValue(metadata.contentWidth);
    float height = (float)ellipse.getHeight().getPixelValue(metadata.contentHeight);
    float aspect = height / width;
    sf::CircleShape sf_ellipse(width/2.0);

    sf_ellipse.setOrigin( width/2.0, width/2.0 );
    sf_ellipse.setScale(1.0, aspect);
    sf_ellipse.setPosition(metadata.contentX + width/2.0, metadata.contentY+height/2.0);
    Color color = ellipse.getColor();
    sf_ellipse.setFillColor(sf::Color(color.r, color.g, color.b));

    window.draw(sf_ellipse);
}

void SfmlRenderer::visit(widgets::Column &column, const widgets::LayoutMetadata &metadata) {
    column.foreach([this](widgets::Widget& w) {
        w.accept(*this);
    });
}

void SfmlRenderer::visit(widgets::Row &row, const widgets::LayoutMetadata &metadata)
{
    row.foreach([this](widgets::Widget& w) {
        w.accept(*this);
    });
}

void SfmlRenderer::visit(widgets::Circle &circle, const widgets::LayoutMetadata &metadata) {
    short bound = metadata.contentWidth;
    if (bound > metadata.contentHeight) {bound = metadata.contentHeight;}
    sf::CircleShape sf_circle(circle.getRadius().getPixelValue(bound));
    
    sf_circle.setPosition(metadata.contentX, metadata.contentY);
    Color color = circle.getColor();
    sf_circle.setFillColor(sf::Color(color.r, color.g, color.b));

    window.draw(sf_circle);
}

void SfmlRenderer::visit(widgets::Text &text, const widgets::LayoutMetadata &metadata) {
    sf::Font font;
    font.loadFromFile("src/FiraCode.ttf");
    sf::Text txt;
    txt.setString(text.getString());
    txt.setFont(font);
    txt.setCharacterSize(text.getLetterHeight());
    Color color = text.getColor();
    txt.setFillColor(sf::Color(color.r, color.g, color.b));
    
    txt.setPosition(metadata.contentX + ( metadata.contentWidth - (float)text.measureWidth() )/2.0, metadata.contentY );
    window.draw(txt);
}

}
