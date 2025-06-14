#include "sfml_renderer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "src/widgets/button.hpp"
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

    // float width = (float)ellipse.getWidth().getPixelValue(metadata.contentWidth);
    // float height = (float)ellipse.getHeight().getPixelValue(metadata.contentHeight);

    float width = metadata.contentWidth;
    float height = metadata.contentHeight;

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
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        font.loadFromFile("src/FiraCode.ttf");
        fontLoaded = true;
    }

    sf::Text txt;
    txt.setFont(font);
    std::string str = text.getString();    
    txt.setString(sf::String::fromUtf8(str.begin(), str.end()));
    txt.setCharacterSize(text.getLetterHeight());
    Color color = text.getColor();
    txt.setFillColor(sf::Color(color.r, color.g, color.b));
    
    txt.setPosition(metadata.contentX + ( metadata.contentWidth - (float)text.measureWidth() )/2.0, metadata.contentY );
    window.draw(txt);
}

void SfmlRenderer::visit(widgets::Button &butt, const widgets::LayoutMetadata &metadata) {
    sf::RectangleShape border({ (float)metadata.contentWidth, (float)metadata.contentHeight });
    border.setPosition(metadata.contentX, metadata.contentY);
    border.setFillColor(sf::Color(
        (unsigned char)(0.5*(float)butt.color.r), 
        (unsigned char)(0.5*(float)butt.color.g), 
        (unsigned char)(0.5*(float)butt.color.b) ));

    float min = (float)metadata.contentWidth;
    if (min > (float)metadata.contentHeight) min = (float)metadata.contentHeight;
    
    float offset = ( min - min*0.8 )/2.0;
    
    float width = ((float)metadata.contentWidth) - offset - offset;
    float height = ((float)metadata.contentHeight) - offset - offset;
    sf::RectangleShape sf_rect({ width, height });
    sf_rect.setPosition(metadata.contentX+offset, metadata.contentY+offset);
    sf_rect.setFillColor(sf::Color(butt.color.r, butt.color.g, butt.color.b));
    
    window.draw(border);
    window.draw(sf_rect);
    
    sf::Font font;
    font.loadFromFile("src/FiraCode.ttf");
    sf::Text txt;
    txt.setString(butt.text.getString());
    txt.setFont(font);
    txt.setCharacterSize(butt.text.getLetterHeight());
    Color color = butt.text.getColor();
    txt.setFillColor(sf::Color(color.r, color.g, color.b));

    float x = ((float)metadata.contentWidth) / 2.0 + (float)metadata.contentX;
    float y = ((float)metadata.contentHeight) / 2.0 + (float)metadata.contentY;
    x -= ((float)butt.text.measureWidth()) / 2.0;
    y -= ((float)butt.text.getLetterHeight()) / 2.0;
    
    txt.setPosition(x,y);
    window.draw(txt);
}

}
