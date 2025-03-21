#pragma once

#include "src/widgets/renderer_metadata.hpp"
namespace y11 {

class SfmlWidgetMetadata : public widgets::RendererMetadata {
public:
    Size getSize() override;
    Point getPos() override;
    Rect getBoudingRect() override;

    short x{}, y{};
    unsigned short width{}, height{};
};

}

