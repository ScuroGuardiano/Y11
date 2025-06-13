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

bool SfmlBackend::getKeyState(events::Key key) {
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


// 3 functions below were generated mainly with ChatGPT.
// I would go insane if I had to type them manually XD
// But of course it made some mistakes and I had to fix them
// I wonder how all those vibe coders write production code... Oh yeah, they only brag about that XD
// Reality: https://www.reddit.com/r/ClaudeAI/comments/1dw3uqt/losing_context_in_projects/
std::unique_ptr<events::Event> SfmlBackend::pollEvent()
{
    using namespace y11::events;

    sf::Event sfEvent;
    if (!window.pollEvent(sfEvent))
        return nullptr;

    switch (sfEvent.type)
    {
    case sf::Event::Closed:
        return std::make_unique<QuitEvent>();

    case sf::Event::KeyPressed:
        return std::make_unique<KeyDownEvent>(EventType::KeyDown, mapKey(sfEvent.key.code));

    case sf::Event::KeyReleased:
        return std::make_unique<KeyUpEvent>(EventType::KeyUp, mapKey(sfEvent.key.code));

    case sf::Event::MouseButtonPressed:
        return std::make_unique<MouseDownEvent>(
            EventType::MouseDown,
            sfEvent.mouseButton.x,
            sfEvent.mouseButton.y,
            mapMouseButton(sfEvent.mouseButton.button));

    case sf::Event::MouseButtonReleased:
        return std::make_unique<MouseUpEvent>(
            EventType::MouseUp,
            sfEvent.mouseButton.x,
            sfEvent.mouseButton.y,
            mapMouseButton(sfEvent.mouseButton.button));

    case sf::Event::MouseMoved:
    {
        static int lastX = sfEvent.mouseMove.x;
        static int lastY = sfEvent.mouseMove.y;

        int dx = sfEvent.mouseMove.x - lastX;
        int dy = sfEvent.mouseMove.y - lastY;

        lastX = sfEvent.mouseMove.x;
        lastY = sfEvent.mouseMove.y;

        return std::make_unique<MouseMoveEvent>(
            sfEvent.mouseMove.x,
            sfEvent.mouseMove.y,
            dx,
            dy);
    }

    default:
        return nullptr;
    };
}

y11::events::Key SfmlBackend::mapKey(sf::Keyboard::Key code) {
    using namespace y11::events;

    switch (code) {
        case sf::Keyboard::A: return Key::A;
        case sf::Keyboard::B: return Key::B;
        case sf::Keyboard::C: return Key::C;
        case sf::Keyboard::D: return Key::D;
        case sf::Keyboard::E: return Key::E;
        case sf::Keyboard::F: return Key::F;
        case sf::Keyboard::G: return Key::G;
        case sf::Keyboard::H: return Key::H;
        case sf::Keyboard::I: return Key::I;
        case sf::Keyboard::J: return Key::J;
        case sf::Keyboard::K: return Key::K;
        case sf::Keyboard::L: return Key::L;
        case sf::Keyboard::M: return Key::M;
        case sf::Keyboard::N: return Key::N;
        case sf::Keyboard::O: return Key::O;
        case sf::Keyboard::P: return Key::P;
        case sf::Keyboard::Q: return Key::Q;
        case sf::Keyboard::R: return Key::R;
        case sf::Keyboard::S: return Key::S;
        case sf::Keyboard::T: return Key::T;
        case sf::Keyboard::U: return Key::U;
        case sf::Keyboard::V: return Key::V;
        case sf::Keyboard::W: return Key::W;
        case sf::Keyboard::X: return Key::X;
        case sf::Keyboard::Y: return Key::Y;
        case sf::Keyboard::Z: return Key::Z;

        case sf::Keyboard::Escape: return Key::Esc;
        case sf::Keyboard::LAlt: return Key::LAlt;
        case sf::Keyboard::RAlt: return Key::RAlt;
        case sf::Keyboard::LControl: return Key::LCtrl;
        case sf::Keyboard::RControl: return Key::RCtrl;
        case sf::Keyboard::Space: return Key::Space;
        case sf::Keyboard::LShift: return Key::LShift;
        case sf::Keyboard::RShift: return Key::RShift;
        case sf::Keyboard::Enter: return Key::Enter;
        case sf::Keyboard::Tab: return Key::Tab;
        case sf::Keyboard::BackSpace: return Key::BSpace;
        case sf::Keyboard::Grave: return Key::Grave;

        case sf::Keyboard::Num0: return Key::N0;
        case sf::Keyboard::Num1: return Key::N1;
        case sf::Keyboard::Num2: return Key::N2;
        case sf::Keyboard::Num3: return Key::N3;
        case sf::Keyboard::Num4: return Key::N4;
        case sf::Keyboard::Num5: return Key::N5;
        case sf::Keyboard::Num6: return Key::N6;
        case sf::Keyboard::Num7: return Key::N7;
        case sf::Keyboard::Num8: return Key::N8;
        case sf::Keyboard::Num9: return Key::N9;

        case sf::Keyboard::Up: return Key::Up;
        case sf::Keyboard::Down: return Key::Down;
        case sf::Keyboard::Left: return Key::Left;
        case sf::Keyboard::Right: return Key::Right;

        default: return Key::Unknown; // Dodaj `Unknown` jeśli chcesz mieć fallback
    }
}

y11::events::MouseButton SfmlBackend::mapMouseButton(sf::Mouse::Button btn) {
    using namespace y11::events;

    switch (btn) {
        case sf::Mouse::Left: return MouseButton::Left;
        case sf::Mouse::Right: return MouseButton::Right;
        case sf::Mouse::Middle: return MouseButton::Middle;
        default: return MouseButton::Other;
    }
}

}