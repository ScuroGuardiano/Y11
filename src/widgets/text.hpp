#pragma once

#include "../color.hpp"
#include "src/backend.hpp"
#include "src/widgets/common.hpp"
#include "widget.hpp"
#include <string>

namespace y11::widgets {

// font in backend
class Text : public Widget {
public:
    Text( unsigned short height );

    Color getColor();
    unsigned short getHeight();
    Text* setColor(Color color);
    Text* setString(std::string);
    Text* setWidth(float);
    std::string getString();

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
    unsigned short height{};
    float width{100};
    std::string stuff{};
};

}

