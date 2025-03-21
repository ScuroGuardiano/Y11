#pragma once

#include "rectangle.hpp"
#include "src/widgets/layout_metadata.hpp"

namespace y11::widgets {

class RendererVisitor {
public:
    virtual void visit(Rectangle& rect, const LayoutMetadata& layoutMetadata) = 0;
};

}

