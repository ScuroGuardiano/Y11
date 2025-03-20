#pragma once

namespace y11 {

struct Point {
    inline Point() : x(0), y(0) {}
    inline Point(short x, short y) : x(x), y(y) {}

    short x, y;
};

}

