#pragma once

#include "src/widgets/common.hpp"
#include "src/widgets/layout.hpp"
#include "src/widgets/renderer_visitor.hpp"
#include "src/widgets/widget.hpp"
#include <memory>
#include <vector>

namespace y11::widgets {

class Column : public Layout {
public:
    // Rect getBoundingRect() override;
    // Point getPos() override;
    // Size getSize() override;

    bool hasChildren() override;
    std::shared_ptr<Widget> getWidgetById(unsigned short id) override;
    bool removeWidget(const std::shared_ptr<Widget> widget) override;
    bool removeWidgetById(unsigned short id) override;

    void accept(RendererVisitor& visitor) override;
    void accept(LayoutVisitor& visitor) override;
    void applyLayout() override;

    Column* setInnerPadding(Padding padding);
    Column* addChild(std::shared_ptr<Widget> widget);
    Column* setGap(unsigned short gap);
    Column* setAlignment(HorizontalAlignment alignment);
    Column* setArrangement(Arrangement arrangement);

private:
    Padding innerPadding{};
    short x, y;
    unsigned short width, height;
    unsigned short gap;

    std::vector<std::shared_ptr<Widget>> children;
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

