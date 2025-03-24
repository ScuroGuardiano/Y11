#pragma once

#include "src/widgets/common.hpp"
#include "src/widgets/composite.hpp"
#include "src/widgets/layout.hpp"
#include "src/widgets/widget.hpp"

namespace y11::widgets {

class Column : public Layout, public Composite {
public:
    // Rect getBoundingRect() override;
    // Point getPos() override;
    // Size getSize() override;

    AutoSizeHint getWidthAutoSizeHint() override;
    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    
    void accept(RendererVisitor& visitor) override;
    void accept(LayoutVisitor& visitor) override;
    void applyLayout() override;

    Column* setInnerPadding(Padding padding);
    Column* setGap(unsigned short gap);
    Column* setAlignment(HorizontalAlignment alignment);
    Column* setArrangement(Arrangement arrangement);

private:
    Padding innerPadding{};
    short x, y;
    unsigned short gap;

    HorizontalAlignment alignment = HorizontalAlignment::LEFT;
    Arrangement arrangement = Arrangement::START;

    class ColumnLayoutVisitor : public LayoutVisitor {
    public:
        ColumnLayoutVisitor(Column& column);
        void visit(Widget& widget, LayoutMetadata& metadata) override;
        void visit(Layout& layout, LayoutMetadata& metadata) override;

    private:
        Column& column; 
    };

    friend ColumnLayoutVisitor;
};

}

