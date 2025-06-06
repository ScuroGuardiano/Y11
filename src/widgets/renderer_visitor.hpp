#pragma once

#include "rectangle.hpp"
#include "ellipse.hpp"
#include "circle.hpp"
#include "layout_metadata.hpp"
#include "column.hpp"
#include "row.hpp"
#include "text.hpp"

namespace y11::widgets {

class RendererVisitor {
public:
    virtual void visit(Rectangle& rect, const LayoutMetadata& layoutMetadata) = 0;
    virtual void visit(Ellipse& ellipse, const LayoutMetadata& layoutMetadata) = 0;
    virtual void visit(Column& column, const LayoutMetadata& layoutMetadta) = 0;
    virtual void visit(Row& row, const LayoutMetadata& layoutMetadata) = 0;
    virtual void visit(Circle& circle, const LayoutMetadata& LayoutMetadata) = 0;
    virtual void visit(Text& text, const LayoutMetadata& LayoutMetadata) = 0;
    virtual ~RendererVisitor() {}
};

}

