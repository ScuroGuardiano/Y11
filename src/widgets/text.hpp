#pragma once

#include "../color.hpp"
#include "widget.hpp"
#include <string>

#if defined(Y11_BACKEND_USE_SFML)
#include <SFML/Graphics.hpp>
#endif

namespace y11::widgets {

// font in backend
class Text : public Widget {
public:
    Text( std::string );

    unsigned short getHeight();
    Text* setHeight( unsigned short );
    Color getColor() override;
    Text* setColor( Color ) override;
    std::string getString();
    Text* setString( std::string );

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
    unsigned short height{14};
    std::string stuff{};
};

}

