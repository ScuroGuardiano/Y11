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
    return std::make_unique<y11::SfmlBackend>(1200, 800);
}

#endif

int main() {
    using namespace y11::widgets;
    using namespace y11::widgets::literals;

    const auto backend = createBackend();
    backend->init();

    Root widgetTree;

    widgetTree.addWidget(std::make_shared<Rectangle>(200_px, 100_px))
        ->setColor(y11::colors::white)
        ->setPadding({ 40 });

    widgetTree.addWidget(std::make_shared<Rectangle>(1.0_pc, 50_px))
        ->setColor({ 0, 255, 0 })
        ->setPadding({ 0, 40 });

    backend->render(widgetTree);
    sleep(5);
}

