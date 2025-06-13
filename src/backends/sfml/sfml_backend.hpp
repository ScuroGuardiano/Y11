#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "src/backend.hpp"
#include "src/backends/sfml/sfml_renderer.hpp"
#include "src/events/event.hpp"
#include "src/widgets/root.hpp"
#include <SFML/Graphics.hpp>
#include <map>

namespace y11 {

class SfmlBackend : public Backend {
public:
    SfmlBackend(unsigned int width, unsigned int height);
    ~SfmlBackend() override;

    void init() override;
    void render(widgets::Root& widgetTree) override;

    unsigned int getWidth() override;
    unsigned int getHeight() override;
    bool getKeyState(events::Key) override;
    void renderRaw(short, short, short) override;

private:

    sf::RenderWindow window;
    SfmlRenderer renderer{window};
    unsigned int width, height;
    std::map<events::Key, sf::Keyboard::Key> keyMap = {
        {events::Key::Up, sf::Keyboard::Key::Up},
        {events::Key::Down, sf::Keyboard::Key::Down},
        {events::Key::Left, sf::Keyboard::Key::Left},
        {events::Key::Right, sf::Keyboard::Key::Right},
        {events::Key::A, sf::Keyboard::Key::A},
        {events::Key::B, sf::Keyboard::Key::B},
        {events::Key::C, sf::Keyboard::Key::C},
        {events::Key::D, sf::Keyboard::Key::D},
        {events::Key::E, sf::Keyboard::Key::E},
        {events::Key::F, sf::Keyboard::Key::F},
        {events::Key::G, sf::Keyboard::Key::G},
        {events::Key::H, sf::Keyboard::Key::H},
        {events::Key::I, sf::Keyboard::Key::I},
        {events::Key::J, sf::Keyboard::Key::J},
        {events::Key::K, sf::Keyboard::Key::K},
        {events::Key::L, sf::Keyboard::Key::L},
        {events::Key::M, sf::Keyboard::Key::M},
        {events::Key::N, sf::Keyboard::Key::N},
        {events::Key::O, sf::Keyboard::Key::O},
        {events::Key::P, sf::Keyboard::Key::P},
        {events::Key::Q, sf::Keyboard::Key::Q},
        {events::Key::R, sf::Keyboard::Key::R},
        {events::Key::S, sf::Keyboard::Key::S},
        {events::Key::T, sf::Keyboard::Key::T},
        {events::Key::U, sf::Keyboard::Key::U},
        {events::Key::W, sf::Keyboard::Key::W},
        {events::Key::V, sf::Keyboard::Key::V},
        {events::Key::X, sf::Keyboard::Key::X},
        {events::Key::Y, sf::Keyboard::Key::Y},
        {events::Key::Z, sf::Keyboard::Key::Z},
        {events::Key::Esc, sf::Keyboard::Key::Escape},
        {events::Key::LAlt, sf::Keyboard::Key::LAlt},
        {events::Key::RAlt, sf::Keyboard::Key::RAlt},
        {events::Key::LCtrl, sf::Keyboard::Key::LControl},
        {events::Key::RCtrl, sf::Keyboard::Key::RControl},
        {events::Key::Space, sf::Keyboard::Key::Space},
        {events::Key::LShift, sf::Keyboard::Key::LShift},
        {events::Key::RShift, sf::Keyboard::Key::RShift},
        {events::Key::Enter, sf::Keyboard::Key::Enter},
        {events::Key::Grave, sf::Keyboard::Key::Grave},
        {events::Key::Tab, sf::Keyboard::Key::Tab},
        {events::Key::BSpace, sf::Keyboard::Key::BackSpace},
        {events::Key::N0, sf::Keyboard::Key::Num0},
        {events::Key::N1, sf::Keyboard::Key::Num1},
        {events::Key::N2, sf::Keyboard::Key::Num2},
        {events::Key::N3, sf::Keyboard::Key::Num3},
        {events::Key::N4, sf::Keyboard::Key::Num4},
        {events::Key::N5, sf::Keyboard::Key::Num5},
        {events::Key::N6, sf::Keyboard::Key::Num6},
        {events::Key::N7, sf::Keyboard::Key::Num7},
        {events::Key::N8, sf::Keyboard::Key::Num8},
        {events::Key::N9, sf::Keyboard::Key::Num9},
    };

    std::unique_ptr<events::Event> pollEvent() override;
    y11::events::Key mapKey(sf::Keyboard::Key code);
    y11::events::MouseButton mapMouseButton(sf::Mouse::Button btn);

};

}
