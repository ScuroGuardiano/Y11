#pragma once

namespace y11 {

struct Size {
    inline Size() : width(0), height(0) {}
    inline Size(unsigned short width, unsigned short height)
    : width(width), height(height) {}

    unsigned short width, height;
};

}

