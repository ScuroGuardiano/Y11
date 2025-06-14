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
#include "src/widgets/button.hpp"
#include "src/animations/animation.hpp"
#include "src/animations/keyframe.hpp"
#include "src/events/cursor.hpp"
#include "src/events/event_loop.hpp"

#include <memory>
#include <unistd.h>
#include <locale.h>

#ifdef Y11_BACKEND_USE_SFML
#include "src/backends/sfml/sfml_backend.hpp"

std::unique_ptr<y11::Backend> createBackend() {
    return std::make_unique<y11::SfmlBackend>(1200, 800);
}

#else

std::unique_ptr<y11::Backend> createBackend() {
    return std::make_unique<y11::BlankBackend>();
}

#endif


int main() {
    using namespace y11::widgets;
    using namespace y11::animations;
    using namespace y11::widgets::literals;
    using namespace y11::events;

    setlocale(LC_ALL, "");

    const auto backend = createBackend();
    backend->init();

    Root widgetTree;

    auto square = std::make_shared<Rectangle>(100_px, 50_px);
    square->setColor(y11::Color(0, 255, 0));

    auto circle = std::make_shared<Circle>(0.2_pc);
    
    auto ellipse = std::make_shared<Ellipse>(100_px, 50_px);
    ellipse->setColor(y11::Color(0, 255, 0));

    auto text = std::make_shared<Text>("Hello World");
    text->setLetterHeight(32);
    
    auto button = std::make_shared<Button>(200_px, 100_px);
    button->setColor(y11::Color(64, 128, 0));

    auto column = std::make_shared<Column>();
    column
        ->setArrangement(Arrangement::CENTER)
        ->setAlignment(HorizontalAlignment::CENTER)
        ->setGap(20);

    column->height = 1.0_pc;

    auto innerColumn = std::make_shared<Column>();
    innerColumn
        ->setArrangement(Arrangement::CENTER)
        ->setAlignment(HorizontalAlignment::CENTER)
        ->setGap(20)
        ->setDims(Dimension::automatic(), 300_px);

    innerColumn->addWidget(square);
    innerColumn->addWidget(ellipse);

    column->addWidget(text);
    column->addWidget(innerColumn);
    column->addWidget(circle);
    column->addWidget(button);

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
    auto k0 = std::make_shared<Keyframe>(100,0.01,y11::Color(255,0,0),1.01,1.0);
    auto k1 = std::make_shared<Keyframe>(100,0.01,y11::Color(0,255,0),1.0, 1.01);
    auto k2 = std::make_shared<Keyframe>(100,0.01,y11::Color(0,0,255), 1.0/1.01, 1.0/1.01);
    a0->addKeyframe(k0);
    a0->addKeyframe(k1);
    a0->addKeyframe(k2);


    auto cursor = std::make_unique<y11::Cursor>();
    

    backend->render(widgetTree);

    std::vector<std::string> texts {
        "UwU ->",
        "<- Hello World ->",
        "<- Nienawidzę C++ ->",
        "<- C++ śmierdzi ->",
        "<- C# the best <3 ->",
        "<- Naura"
    };

    size_t textidx = 1;

    text->setString(texts[textidx]);

    EventLoop eventLoop{};
    eventLoop.bind(backend.get());

    eventLoop.addEventListener(EventType::KeyDown, [&](Event& evt) {
        KeyEvent& kevt = dynamic_cast<KeyEvent&>(evt);
        
        if (kevt.key == Key::Esc) {
            eventLoop.stop();
        }

        if (kevt.key == Key::Left) {
            if (textidx == 0) {
                textidx = texts.size() - 1;
            }
            else {
                textidx -= 1;
            }

            text->setString(texts[textidx]);
        }

        if (kevt.key == Key::Right) {
            if (textidx >= (texts.size() - 1)) {
                textidx = 0;
            }
            else {
                textidx += 1;
            }
            text->setString(texts[textidx]);
        }
    });

    eventLoop.addEventListener(EventType::Quit, [&](Event& evt) {
        eventLoop.stop();
    });

    eventLoop.addEventListener(EventType::AnimationFrame, [&](Event& evt) {
        a0->evaluate(ellipse);
        a0->evaluate(square);
        a0->advance();

        backend->render(widgetTree);
    });

    eventLoop.run();
}
