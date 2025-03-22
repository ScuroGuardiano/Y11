#pragma once

#include "../rect.hpp"
#include "../padding.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/layout_metadata.hpp"
#include <memory>

namespace y11::widgets {

class RendererVisitor;
class LayoutVisitor;

class Widget {
public:
    virtual Rect getBoundingRect();
    virtual Point getPos();
    virtual Size getSize();
    virtual AutoSizeHint getAutoSizeHint();
    virtual Widget* setPadding(Padding padding);
    
    virtual bool hasChildren();
    virtual std::shared_ptr<Widget> getWidgetById(unsigned short id);
    virtual bool removeWidget(const std::shared_ptr<Widget> widget);
    virtual bool removeWidgetById(unsigned short id);

    virtual void accept(RendererVisitor& visitor) = 0;
    virtual void accept(LayoutVisitor& visitor);

    virtual ~Widget() = 0;

    Padding padding{};

    Dimension width{};
    Dimension height{};

    unsigned short id{};

protected:
    LayoutMetadata layoutMetadata;
};

}

