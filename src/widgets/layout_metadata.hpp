#pragma once

namespace y11::widgets {

struct LayoutMetadata {
    short x{}, y{};
    short contentX{}, contentY{};
    unsigned short width{}, height{};
    unsigned short contentWidth{}, contentHeight{};
    bool overflow = false;
};

}
