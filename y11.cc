#include "src/backend.hpp"
#include "src/padding.hpp"
#include "src/widgets/column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/rectangle.hpp"
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

    // widgetTree.addWidget(std::make_shared<Rectangle>(200_px, 100_px))
    //     ->setColor(y11::colors::white)
    //     ->setPadding({ 40 });

    // widgetTree.addWidget(std::make_shared<Rectangle>(1.0_pc, 50_px))
    //     ->setColor({ 0, 255, 0 })
    //     ->setPadding({ 0, 40 });

    auto column = std::make_shared<Column>();
    column->setGap(10);
    column->setAlignment(HorizontalAlignment::CENTER);
    column->setArrangement(Arrangement::CENTER);
    // column->setPadding(y11::Padding(10));
    column->height = 1.0_pc;

    // column->addWidget(std::make_shared<Rectangle>(0.25_pc, 0.2_pc))
    //     ->setColor({ 0, 255, 0 });

    column->addWidget(std::make_shared<Rectangle>(0.5_pc, 0.5_pc))
        ->setColor({ 0, 0, 255 });

    // column->addWidget(std::make_shared<Rectangle>(0.75_pc, 0.2_pc))
    //     ->setColor({ 255, 0, 0 });

    widgetTree.addWidget(column);

    backend->render(widgetTree);
    sleep(5);
}

