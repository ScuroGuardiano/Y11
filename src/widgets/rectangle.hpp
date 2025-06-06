#pragma once

#include "../color.hpp"
#include "src/widgets/common.hpp"
#include "widget.hpp"

namespace y11::widgets {

class Rectangle : public Widget {
public:
    Rectangle(Dimension width, Dimension height);

    Rectangle* setColor(Color color) override;
    Color getColor() override;
    Rectangle* setSize(Dimension width, Dimension height);

    void accept(RendererVisitor& visitor) override;

    Color color = y11::colors::black;
};

}

