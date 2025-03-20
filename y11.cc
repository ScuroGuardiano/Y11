#include "src/backend.hpp"
#include "src/padding.hpp"
#include "src/widgets/rectangle.hpp"
#include "src/widgets/root.hpp"

#include <memory>
#include <unistd.h>

#define Y11_BACKEND_USE_SFML

#ifdef Y11_BACKEND_USE_SFML
#include "src/backends/sfml/sfml_backend.hpp"

std::unique_ptr<y11::Backend> createBackend() {
    return std::make_unique<y11::SfmlBackend>(480, 320);
}

#endif

int main() {
    using namespace y11::widgets;

    auto backend = createBackend();
    backend->init();

    Root widgetTree;

    auto rect1 = std::make_shared<Rectangle>(200, 100);
    rect1->padding = y11::Padding(40);
    rect1->color = y11::colors::white;

    auto rect2 = std::make_shared<Rectangle>(50, 50);
    rect2->padding.left = 40;
    rect2->color = y11::Color(0, 255, 0);

    widgetTree.addWidget(rect1);
    widgetTree.addWidget(rect2);

    backend->render(widgetTree);
    sleep(5);
}

