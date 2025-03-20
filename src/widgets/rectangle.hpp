#pragma once

#include "../color.hpp"
#include "widget.hpp"

namespace y11::widgets {

class Rectangle : public Widget {
public:
    Rectangle(unsigned short width, unsigned short height);
    Rect getBoundingRect() override;
    Point getPos() override;
    Size getSize() override;

    void setPos(short x, short y);

    void accept(RendererVisitor& visitor) override;

    Color color = y11::colors::black;
    unsigned short width;
    unsigned short height;

private:
    short x{};
    short y{};
};

}

