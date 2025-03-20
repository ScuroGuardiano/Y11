#include "sfml_backend.hpp"

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

    widgetTree.foreach([this](widgets::Widget& widget) {
        widget.accept(renderer);
    });

    window.display();
}

}

