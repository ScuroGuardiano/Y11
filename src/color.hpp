#pragma once

namespace y11 {

struct Color {
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    inline Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) 
        : a(a), r(r), g(g), b(b) {}

    inline Color(unsigned char r, unsigned char g, unsigned char b) 
        : Color(255, r, g, b) {}

    inline Color(unsigned int raw) 
        : a((raw >> 24) & 0xFF), 
          r((raw >> 16) & 0xFF), 
          g((raw >> 8) & 0xFF), 
          b(raw & 0xFF) {}

    inline Color() : Color(255, 255, 0, 0) {}

    inline unsigned int raw() const {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

namespace colors {

static const Color black(0, 0, 0);
static const Color white(255, 255, 255);

}

};

