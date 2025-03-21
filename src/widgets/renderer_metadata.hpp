#pragma once

#include "src/point.hpp"
#include "src/rect.hpp"
#include "src/size.hpp"
namespace y11::widgets {

class RendererMetadata {
public:
    virtual Size getSize() = 0;
    virtual Point getPos() = 0;
    virtual Rect getBoudingRect() = 0;
};

}

