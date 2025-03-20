#pragma once

#include "rectangle.hpp"

namespace y11::widgets {

class RendererVisitor {
public:
    virtual void visit(Rectangle& rect) = 0;
};

}

