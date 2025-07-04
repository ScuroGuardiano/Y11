#pragma once

#include "../color.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/text.hpp"
#include "widget.hpp"

namespace y11::widgets {

class Button : public Widget {
public:
    Button(Dimension width, Dimension height);
    Button* setText(Text);

    Button* setColor(Color color) override;
    Color getColor() override;

    void accept(RendererVisitor& visitor) override;

    Color color = y11::colors::black;
    Text text = Text("XOXO");
};

}

