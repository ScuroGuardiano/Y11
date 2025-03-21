#include "common.hpp"

#include <cmath>
#include <limits>

namespace y11::widgets {

DimensionUnit Dimension::getUnit() const {
    return unit;
}

float Dimension::getValue() const {
    return value;
}

short Dimension::getPixelValue(short totalPixels) const {
    switch (this->unit) {
        case DimensionUnit::PIXEL:
            return (short)this->value;

        case DimensionUnit::PERCENT:
            return safeMultiply(totalPixels);

        case DimensionUnit::AUTO:
            return 0;
    }
};

Dimension Dimension::operator-() const {
    return Dimension(unit, -value);
};


short Dimension::safeMultiply(short scalar) const {
    float res = std::round(value * scalar);
    constexpr auto max = std::numeric_limits<short>::max();
    constexpr auto min = std::numeric_limits<short>::min();

    if (res < min) {
        return min;
    }

    if (res > max) {
        return max;
    }

    return res;
};

} // namespace y11::widgets
