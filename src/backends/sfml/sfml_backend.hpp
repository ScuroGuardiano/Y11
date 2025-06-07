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
    bool getKeyState(Key) override;
    void renderRaw(short, short, short) override;

private:
    sf::RenderWindow window;
    SfmlRenderer renderer{window};
    unsigned int width, height;
    std::map<Key, sf::Keyboard::Key> keyMap = {
        {Key::Up, sf::Keyboard::Key::Up},
        {Key::Down, sf::Keyboard::Key::Down},
        {Key::Left, sf::Keyboard::Key::Left},
        {Key::Right, sf::Keyboard::Key::Right},
        {Key::A, sf::Keyboard::Key::A},
        {Key::B, sf::Keyboard::Key::B},
        {Key::C, sf::Keyboard::Key::C},
        {Key::D, sf::Keyboard::Key::D},
        {Key::E, sf::Keyboard::Key::E},
        {Key::F, sf::Keyboard::Key::F},
        {Key::G, sf::Keyboard::Key::G},
        {Key::H, sf::Keyboard::Key::H},
        {Key::I, sf::Keyboard::Key::I},
        {Key::J, sf::Keyboard::Key::J},
        {Key::K, sf::Keyboard::Key::K},
        {Key::L, sf::Keyboard::Key::L},
        {Key::M, sf::Keyboard::Key::M},
        {Key::N, sf::Keyboard::Key::N},
        {Key::O, sf::Keyboard::Key::O},
        {Key::P, sf::Keyboard::Key::P},
        {Key::Q, sf::Keyboard::Key::Q},
        {Key::R, sf::Keyboard::Key::R},
        {Key::S, sf::Keyboard::Key::S},
        {Key::T, sf::Keyboard::Key::T},
        {Key::U, sf::Keyboard::Key::U},
        {Key::W, sf::Keyboard::Key::W},
        {Key::V, sf::Keyboard::Key::V},
        {Key::X, sf::Keyboard::Key::X},
        {Key::Y, sf::Keyboard::Key::Y},
        {Key::Z, sf::Keyboard::Key::Z},
        {Key::Esc, sf::Keyboard::Key::Escape},
        {Key::LAlt, sf::Keyboard::Key::LAlt},
        {Key::RAlt, sf::Keyboard::Key::RAlt},
        {Key::LCtrl, sf::Keyboard::Key::LControl},
        {Key::RCtrl, sf::Keyboard::Key::RControl},
        {Key::Space, sf::Keyboard::Key::Space},
        {Key::LShift, sf::Keyboard::Key::LShift},
        {Key::RShift, sf::Keyboard::Key::RShift},
        {Key::Enter, sf::Keyboard::Key::Enter},
        {Key::Grave, sf::Keyboard::Key::Grave},
        {Key::Tab, sf::Keyboard::Key::Tab},
        {Key::BSpace, sf::Keyboard::Key::BackSpace},
        {Key::N0, sf::Keyboard::Key::Num0},
        {Key::N1, sf::Keyboard::Key::Num1},
        {Key::N2, sf::Keyboard::Key::Num2},
        {Key::N3, sf::Keyboard::Key::Num3},
        {Key::N4, sf::Keyboard::Key::Num4},
        {Key::N5, sf::Keyboard::Key::Num5},
        {Key::N6, sf::Keyboard::Key::Num6},
        {Key::N7, sf::Keyboard::Key::Num7},
        {Key::N8, sf::Keyboard::Key::Num8},
        {Key::N9, sf::Keyboard::Key::Num9},
    };
};

}
