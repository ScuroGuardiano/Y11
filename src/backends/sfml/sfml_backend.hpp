#pragma once

#include "src/backend.hpp"
#include "src/backends/sfml/sfml_renderer.hpp"
#include "src/widgets/root.hpp"
#include <SFML/Graphics.hpp>

namespace y11 {

class SfmlBackend : public Backend {
public:
    SfmlBackend(unsigned int width, unsigned int height);
    ~SfmlBackend() override;

    void init() override;
    void render(widgets::Root& widgetTree) override;

private:
    sf::RenderWindow window;
    SfmlRenderer renderer{window};
    unsigned int width, height;
};

}
