#pragma once

#include <limits>

namespace y11::widgets {

enum class HorizontalAlignment : short {
    LEFT,
    CENTER,
    RIGHT
};

enum class VerticalAlignment : short {
    TOP,
    CENTER,
    BOTTOM
};

enum class Arrangement : short {
    START,
    CENTER,
    END,
    SPACE_BETWEEN,
    SPACE_AROUND,
    SPACE_EVENLY
};

enum class DimensionUnit : short {
    PIXEL,
    PERCENT,
    AUTO
};

enum class AutoSizeHint {
    FIT_CONTENT,
    EXPAND
};

class Dimension {
public:
    constexpr Dimension() : value(0.f), unit(DimensionUnit::AUTO) {}

    constexpr static Dimension pixels(short value) {
        return Dimension(DimensionUnit::PIXEL, value);
    };

    constexpr static Dimension percent(float value) {
        return Dimension(DimensionUnit::PERCENT, value);
    };

    constexpr static Dimension automatic() {
        return Dimension();
    }

    short getPixelValue(short totalPixels) const;
    float getValue() const;
    DimensionUnit getUnit() const;
    Dimension operator-() const;

    // Dimension operator*(float scalar) const;
    // Dimension operator*(short scalar) const;
    // Dimension operator+(const Dimension& other) const;
    // Dimension operator-(const Dimension& other) const;

private:
    constexpr Dimension(DimensionUnit unit, float value) : value(value), unit(unit) {};
    short safeMultiply(short scalar) const;

    float value;
    DimensionUnit unit;
};

namespace literals {

constexpr Dimension operator""_px(const unsigned long long x) {
    constexpr short max = std::numeric_limits<short>::max();

    if (x > max) {
        return Dimension::pixels(max);
    }

    return Dimension::pixels(x);
}

constexpr Dimension operator""_pc(long double x) {
    constexpr float max = std::numeric_limits<float>::max();

    if (x > max) {
        return Dimension::percent(max);
    }

    return Dimension::percent(x);
}

}

}

