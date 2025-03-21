#pragma once

#include "src/widgets/common.hpp"
#include "src/widgets/renderer_visitor.hpp"
#include "src/widgets/widget.hpp"
#include <memory>
#include <vector>

namespace y11::widgets {

class Column : public Widget {
public:
    Rect getBoundingRect() override;
    Point getPos() override;
    Size getSize() override;

    bool hasChildren() override;
    std::shared_ptr<Widget> getWidgetById(unsigned short id) override;
    bool removeWidget(const std::shared_ptr<Widget> widget) override;
    bool removeWidgetById(unsigned short id) override;

    void accept(RendererVisitor& visitor) override;

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
};

}

