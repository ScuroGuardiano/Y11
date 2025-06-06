#pragma once

#include "src/backend.hpp"
#include "widget.hpp"
#include "../color.hpp"
#include "src/widgets/common.hpp"

namespace y11::widgets {

class Circle : public Widget {
public:
    Circle(Dimension radius);
    Circle(Dimension radius, const std::unique_ptr<y11::Backend>& backend);

    Circle* setColor(Color color) override;
    Color getColor() override;
    Circle* setRadius(Dimension radius);
    Circle* setRadius(Dimension radius, const std::unique_ptr<y11::Backend>& backend);
    short getRadius();

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;

    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
    short radius{};
};

}
