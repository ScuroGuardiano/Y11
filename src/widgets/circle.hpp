#pragma once

#include "widget.hpp"
#include "../color.hpp"
#include "src/widgets/common.hpp"

namespace y11::widgets {

class Circle : public Widget {
public:
    Circle(short radius);

    Circle* setColor(Color color);
    Color getColor();
    Circle* setRadius(short radius);
    short getRadius();

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;

    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
    short radius{};
};

}
