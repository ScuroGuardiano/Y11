#pragma once

#include "src/widgets/widget.hpp"
#include "src/widgets/layout_metadata.hpp"

namespace y11::widgets {

class Root;

class Layout : public Widget {
public:
    /*
    * Applies layout to it's children
    */
    virtual void applyLayout() = 0;
    virtual void accept(RendererVisitor& visitor) override = 0;
    virtual void accept(LayoutVisitor& visitor) override;
};


class LayoutVisitor {
public:
    virtual void visit(Widget& widget, LayoutMetadata& metadata) = 0;
    virtual ~LayoutVisitor() {}
};

class DefaultLayoutVisitor : public LayoutVisitor {
public:
    DefaultLayoutVisitor();
    DefaultLayoutVisitor(const LayoutVisitor& other) = delete;
    DefaultLayoutVisitor(const Rect& rect);
    void setLayoutRect(const Rect& rect);

    void visit(Widget &widget, LayoutMetadata &metadata) override;

private:
    Rect rect{};
    Point currentPos{};
};

}

