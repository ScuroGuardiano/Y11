#pragma once

#include "point.hpp"
#include "size.hpp"

namespace y11 {

struct Rect : public Point, public Size {
    inline Rect() : Point(), Size() {}
    inline Rect(
        short x,
        short y,
        unsigned short width,
        unsigned short height
    ) : Point(x, y), Size(width, height) {}
};

}

