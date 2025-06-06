#pragma once

#include "../color.hpp"
#include "src/widgets/common.hpp"
#include "widget.hpp"

namespace y11::widgets {

class Ellipse : public Widget {
public:
    Ellipse(Dimension width, Dimension height);

    Ellipse* setColor(Color color) override;
    Color getColor() override;

    void accept(RendererVisitor& visitor) override;


private:
    Color color = y11::colors::black;
};

}

