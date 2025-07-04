#pragma once

namespace y11 {

struct Padding {
    inline Padding() : Padding(0) {};

    inline Padding(short all) : top(all), right(all), bottom(all), left(all) {}

    inline Padding(short vertical, short horizontal)
    : top(vertical), right(horizontal), bottom(vertical), left(horizontal) {}
    
    inline Padding(short top, short right, short bottom, short left)
    : top(top), right(right), bottom(bottom), left(left) {}

    inline unsigned short totalHorizontal() const {
        return left + right;
    }

    inline unsigned short totalVertical() const {
        return top + bottom;
    }

    unsigned short top{}, right{}, bottom{}, left{};
};

}

