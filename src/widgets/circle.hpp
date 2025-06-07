#pragma once

#include "widget.hpp"
#include "../color.hpp"
#include "src/widgets/common.hpp"

namespace y11::widgets {

class Circle : public Widget {
public:
    Circle(Dimension radius);

    Circle* setColor(Color color) override;
    Color getColor() override;
    Circle* setRadius(Dimension radius);
    Dimension getRadius();

    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
};

}
