#include "src/backend.hpp"
#include "src/padding.hpp"
#include "src/widgets/column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/ellipse.hpp"
#include "src/widgets/rectangle.hpp"
#include "src/widgets/circle.hpp"
#include "src/widgets/text.hpp"
#include "src/widgets/root.hpp"
#include "src/widgets/row.hpp"

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

    auto circle = std::make_shared<Circle>(0.1_pc, backend);
    
    auto ellipse = std::make_shared<Ellipse>(100_px, 0.2_pc, backend);
    ellipse->setColor(y11::Color(0, 255, 0));

    auto text = std::make_shared<Text>(32);
    text->setString("Hello World");

    auto column = std::make_shared<Column>();
    column
        ->setArrangement(Arrangement::CENTER)
        ->setAlignment(HorizontalAlignment::CENTER)
        ->setGap(20);

    column->height = 1.0_pc;

    column->addWidget(square);
    column->addWidget(ellipse);
    column->addWidget(text);
    column->addWidget(circle);

    auto row = std::make_shared<Row>();
    row
        ->setArrangement(Arrangement::SPACE_EVENLY)
        ->setAlignment(VerticalAlignment::CENTER);
    
    auto rc1 = std::make_shared<Rectangle>(100_px, 100_px);
    rc1->setColor(y11::Color(255, 0, 0));

    auto rc2 = std::make_shared<Rectangle>(200_px, 400_px);
    rc2->setColor(y11::Color(0, 255, 0));

    auto rc3 = std::make_shared<Rectangle>(100_px, 1.0_pc);
    rc3->setColor(y11::Color(0, 0, 255));

    row->addWidget(rc1);
    row->addWidget(rc2);
    row->addWidget(rc3);

    column->addWidget(row);

    widgetTree.addWidget(column);

    backend->render(widgetTree);
    sleep(2);
}
