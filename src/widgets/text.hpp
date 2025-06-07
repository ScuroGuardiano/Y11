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

    unsigned short getLetterHeight();
    Text* setLetterHeight( unsigned short );
    Color getColor() override;
    Text* setColor( Color ) override;
    std::string getString();
    Text* setString( std::string );

    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    void accept(RendererVisitor& visitor) override;

private:
    Color color = y11::colors::white;
    unsigned short lH{14};
    std::string stuff{};
};

}

