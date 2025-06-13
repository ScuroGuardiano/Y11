#include "sfml_backend.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace y11 {

SfmlBackend::SfmlBackend(unsigned int width, unsigned int height)
: width(width), height(height) {}

SfmlBackend::~SfmlBackend() {
    if (window.isOpen()) {
        window.close();
    }
}

void SfmlBackend::init() {
    window.create(sf::VideoMode({ width, height }), "Y11 - SFML Backend");
}

void SfmlBackend::render(widgets::Root& widgetTree) {
    window.clear();
    
    widgetTree.setLayoutRect({
        // YOLO
        0, 0, (unsigned short)window.getSize().x, (unsigned short)window.getSize().y
    });

    widgetTree.applyLayout();

    widgetTree.foreach([this](widgets::Widget& widget) {
        widget.accept(renderer);
    });

    window.display();
}

unsigned int SfmlBackend::getWidth()
{
    return this->width;
}

unsigned int SfmlBackend::getHeight()
{
    return this->height;
}

bool SfmlBackend::getKeyState(Key key) {
    return sf::Keyboard::isKeyPressed(this->keyMap.at(key));
}

void SfmlBackend::renderRaw(short posX, short PosY, short radius) {
    sf::CircleShape circle( (float)radius );
    circle.setFillColor(sf::Color(255,0,0));
    circle.setOrigin( (float)radius/2.0, (float)radius/2.0 );
    circle.setPosition( (float)posX, (float)PosY );
    this->renderer.window.draw(circle);
    this->renderer.window.display();
}

}

