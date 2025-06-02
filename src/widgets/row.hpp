#pragma once

#include "src/widgets/common.hpp"
#include "src/widgets/composite.hpp"
#include "src/widgets/layout.hpp"
#include "src/widgets/widget.hpp"

namespace y11::widgets {

class Row : public Layout, public Composite {
public:
    AutoSizeHint getWidthAutoSizeHint() override;
    unsigned short measureWidth() override;
    unsigned short measureHeight() override;
    
    void accept(RendererVisitor& visitor) override;
    void accept(LayoutVisitor& visitor) override;
    void applyLayout() override;

    Row* setGap(unsigned short gap);
    Row* setAlignment(VerticalAlignment alignment);
    Row* setArrangement(Arrangement arrangement);

private:
    short x{}, y{};
    unsigned short gap{};

    VerticalAlignment alignment = VerticalAlignment::TOP;
    Arrangement arrangement = Arrangement::START;


    // ====================================
    // ======== Row layout Visitor ========
    // ====================================
    class RowLayoutVisitor : public LayoutVisitor
    {
    public:
        RowLayoutVisitor(const Row& row);
        void visit(Widget& widget, LayoutMetadata& metadata) override;
        short getUnusedHSpace();

    private:
        const Row& row;
        Rect innerRect{};

        // Grow axis is X
        short currentX{};

        // Can width grow or not
        // If the width can grow then children with % or expand width
        // will have their widths set to minimum.
        // because it's problematic to calculate their width in that case
        bool widthGrow{};
        short freeHorizontalPercSpace{};
        bool ignoreGap{};
    };

    friend RowLayoutVisitor;

    // =========================================
    // ======== Row arrangement Visitor ========
    // =========================================

    // Row arrangement visitor applies arrangement to the elements.
    // Because arranging items required knowledge of size of everything it was
    // the easiest way to just create another visitor
    class RowArrangementVisitor : public LayoutVisitor
    {
    public:
        // ColumnArrangementVisitor(short unusedVSpace, short childrenCount, Arrangement arrangement);
        RowArrangementVisitor(short unusedHSpace, short childrenCount, Arrangement arrangement);
        void visit(Widget& widget, LayoutMetadata& metadata) override;

    private:
        short n{};
        short offset{};
        short childrenCount{};
        Arrangement arrangement{};
    };
};

} // y11::widgets
