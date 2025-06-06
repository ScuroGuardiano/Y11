#pragma once

#include "src/color.hpp"

namespace y11::animations {

class Keyframe {
public:
    Keyframe(unsigned short, float, Color);
    ~Keyframe();
    
    unsigned short duration{};
    float strength{0.5};
    Color target = y11::colors::black;
};

}
