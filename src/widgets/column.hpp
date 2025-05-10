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

    Column* setGap(unsigned short gap);
    Column* setAlignment(HorizontalAlignment alignment);
    Column* setArrangement(Arrangement arrangement);

private:
    short x{}, y{};
    unsigned short gap{};

    HorizontalAlignment alignment = HorizontalAlignment::LEFT;
    Arrangement arrangement = Arrangement::START;

    // =======================================
    // ======== Column layout Visitor ========
    // =======================================
    class ColumnLayoutVisitor : public LayoutVisitor
    {
    public:
        ColumnLayoutVisitor(const Column& column);
        void visit(Widget& widget, LayoutMetadata& metadata) override;
        short getUnusedVSpace();

    private:
        const Column& column;
        Rect innerRect{};

        // Grow axis is Y
        short currentY{};

        // Can hight grow or not
        // If the height can grow then children with % or expand height
        // will have their height set to minimum.
        // because it's problematic to calculate their height in that case
        bool heightGrow{};
        short freeVertPercSpace{};
        bool ignoreGap{};
    };

    friend ColumnLayoutVisitor;

    // ============================================
    // ======== Column arrangement Visitor ========
    // ============================================

    // Column arragement visitor applies arrangement to the elements.
    // Because arranging items requires knowledge of size of everything it was
    // the easiest way to just create another visitor.
    class ColumnArrangementVisitor : public LayoutVisitor
    {
    public:
        ColumnArrangementVisitor(short unusedVSpace, short childrenCount, Arrangement arrangement);
        void visit(Widget& widget, LayoutMetadata& metadata) override;

    private:
        short n{};
        short offset{};
        short childrenCount{};
        Arrangement arrangement{};
    };
};

}

