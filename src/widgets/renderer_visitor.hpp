#pragma once

#include "rectangle.hpp"
#include "layout_metadata.hpp"
#include "column.hpp"

namespace y11::widgets {

class RendererVisitor {
public:
    virtual void visit(Rectangle& rect, const LayoutMetadata& layoutMetadata) = 0;
    virtual void visit(Column& column, const LayoutMetadata& layoutMetadta) = 0;
    virtual ~RendererVisitor() {}
};

}

