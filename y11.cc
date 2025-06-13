#include "src/backend.hpp"
#include "src/color.hpp"
#include "src/events/event.hpp"
#include "src/padding.hpp"
#include "src/widgets/column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/ellipse.hpp"
#include "src/widgets/rectangle.hpp"
#include "src/widgets/circle.hpp"
#include "src/widgets/text.hpp"
#include "src/widgets/root.hpp"
#include "src/widgets/row.hpp"
#include "src/animations/animation.hpp"
#include "src/animations/keyframe.hpp"
#include "src/events/cursor.hpp"

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
    using namespace y11::animations;
    using namespace y11::widgets::literals;

    const auto backend = createBackend();
    backend->init();

    Root widgetTree;

    auto square = std::make_shared<Rectangle>(100_px, 50_px);
    square->setColor(y11::Color(0, 255, 0));

    auto circle = std::make_shared<Circle>(0.2_pc);
    
    auto ellipse = std::make_shared<Ellipse>(100_px, 50_px);
    ellipse->setColor(y11::Color(0, 255, 0));

    auto text = std::make_shared<Text>("HelloWorld");
    text->setLetterHeight(32);

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
    
    auto rc1 = std::make_shared<Rectangle>(20_px, 30_px);
    rc1->setColor(y11::Color(255, 0, 0));

    auto rc2 = std::make_shared<Rectangle>(40_px, 50_px);
    rc2->setColor(y11::Color(0, 255, 0));

    auto rc3 = std::make_shared<Rectangle>(0.1_pc, 10_px);
    rc3->setColor(y11::Color(0, 0, 255));

    row->addWidget(rc1);
    row->addWidget(rc2);
    row->addWidget(rc3);

    column->addWidget(row);

    widgetTree.addWidget(column);

    auto a0 = std::make_shared<Animation>();
    auto k0 = std::make_shared<Keyframe>(30,0.05,y11::Color(255,0,0),1.05,1.0);
    auto k1 = std::make_shared<Keyframe>(30,0.05,y11::Color(0,255,0),1.0, 1.05);
    auto k2 = std::make_shared<Keyframe>(30,0.05,y11::Color(0,0,255), 1.0/1.05, 1.0/1.05);
    a0->addKeyframe(k0);
    a0->addKeyframe(k1);
    a0->addKeyframe(k2);


    auto cursor = std::make_unique<y11::Cursor>();
    
    for (unsigned short i = 0; i<320; i++) {
        backend->render(widgetTree);
        cursor->evaluate(backend);
        a0->evaluate(ellipse);
        a0->evaluate(square);
        a0->advance();


        if ( backend->getKeyState(y11::Key::Esc) ) {return 2;}
    }
}
