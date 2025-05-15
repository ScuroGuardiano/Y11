#include "src/backend.hpp"
#include "src/padding.hpp"
#include "src/widgets/column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/rectangle.hpp"
#include "src/widgets/circle.hpp"
#include "src/widgets/root.hpp"

#include <memory>
#include <unistd.h>

#ifdef Y11_BACKEND_USE_SFML
#include "src/backends/sfml/sfml_backend.hpp"

std::unique_ptr<y11::Backend> createBackend() {
    return std::make_unique<y11::SfmlBackend>(1200, 800);
}

#elif defined(Y11_BACKEND_USE_BLANK)

std::unique_ptr<y11::Backend> createBackend() {
    return std::make_unique<y11::BlankBackend>();
}

#endif


int main() {
    using namespace y11::widgets;
    using namespace y11::widgets::literals;

    const auto backend = createBackend();
    backend->init();

    Root widgetTree;

    auto square = std::make_shared<Rectangle>(200_px, 200_px);
    square->setColor(y11::Color(0, 255, 0));

    auto square2 = std::make_shared<Rectangle>(200_px, 200_px);
    square2->setColor(y11::Color(0, 255, 0));

    auto circle = std::make_shared<Circle>(100);

    auto column = std::make_shared<Column>();
    column
        ->setArrangement(Arrangement::CENTER)
        ->setAlignment(HorizontalAlignment::CENTER)
        ->setGap(20);

    column->height = 1.0_pc;

    column->addWidget(square);
    column->addWidget(square2);
    column->addWidget(circle);

    widgetTree.addWidget(column);

    backend->render(widgetTree);
    sleep(5);
}
