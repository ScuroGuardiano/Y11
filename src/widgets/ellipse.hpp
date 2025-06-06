#pragma once

#include "../color.hpp"
#include "src/backend.hpp"
#include "src/widgets/common.hpp"
#include "widget.hpp"

namespace y11::widgets {

class Ellipse : public Widget {
public:
    Ellipse(Dimension width, Dimension height);
    Ellipse(Dimension width, Dimension height, const std::unique_ptr<y11::Backend>& backend);

    Ellipse* setColor(Color color) override;
    Color getColor() override;
    Ellipse* setDims(Dimension radius_x, Dimension radius_y);
    Ellipse* setDims(Dimension radius_x, Dimension radius_y, const std::unique_ptr<y11::Backend>& backend);
    short getRadiusX();
    short getRadiusY();

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    void accept(RendererVisitor& visitor) override;


private:
    Color color = y11::colors::black;
    short radius_x{};
    short radius_y{};
};

}

