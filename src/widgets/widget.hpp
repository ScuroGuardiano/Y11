#pragma once

#include "../rect.hpp"
#include "../padding.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/layout_metadata.hpp"

namespace y11::widgets {

class RendererVisitor;
class LayoutVisitor;

class Widget {
public:
    /*
    * Returns area occupied by widget on the render plane
    */
    virtual Rect getBoundingRect();
    
    /*
    * Returns position of a widget on the render plane
    */
    virtual Point getPos();

    /*
    * Returns size of a widget on the render plane
    */
    virtual Size getSize();

    /*
    * How autosize should behave for width
    */
    virtual AutoSizeHint getWidthAutoSizeHint();

    /*
    * How autosize should behave for height
    */
    virtual AutoSizeHint getHeightAutoSizeHint();

    /*
    * Tries to tell size needed for a widget in pixels.
    * If it's impossible to tell size without layout context then it'll return size of 0 
    */
    virtual Size measure();

    /*
    * Tries to tell needed width for a widget in pixels.
    * If it's impossible to tell size without layout context then it'll return size of 0
    */
    virtual unsigned short measureWidth();

    /*
    * Tries to tell needed height for a widget in pixels.
    * If it's impossible to tell size without layout context then it'll return size of 0
    */
    virtual unsigned short measureHeight();


    virtual Widget* setPadding(Padding padding);
    
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

