#include "row.hpp"
#include "renderer_visitor.hpp"
#include <iostream>

namespace y11::widgets {

AutoSizeHint Row::getWidthAutoSizeHint()
{
    return AutoSizeHint::EXPAND;
}

unsigned short Row::measureWidth()
{
    unsigned short width = 0;
    Sizing horizontalSizing = this->getHorizontalSizing();

    if (horizontalSizing == Sizing::PIXEL)
    {
        width = std::max<short>(0, this->width.getPixelValue(2137));
    }
    else if (horizontalSizing == Sizing::FIT_CONTENT)
    {
        unsigned short childrenWidthSum = 0;

        for (auto& w : children)
        {
            childrenWidthSum += w->measureWidth();
        }

        return padding.totalHorizontal()
            + gap * (children.size() - 1)
            + childrenWidthSum;
    }

    return std::max<unsigned short>(padding.totalHorizontal(), width);
}

unsigned short Row::measureHeight()
{
    unsigned short height = 0;

    if (this->height.getUnit() == DimensionUnit::PIXEL)
    {
        height = std::max<short>(0, this->height.getPixelValue(2137));
    }
    else if (this->getVerticalSizing() == Sizing::FIT_CONTENT)
    {
        unsigned short maxHeight = 0;
        for (auto& w : children)
        {
            auto measurement = w->measureHeight();
            if (measurement > maxHeight)
            {
                maxHeight = measurement;
            }
        }

        return padding.totalVertical() + maxHeight;
    }

    return std::max<unsigned short>(padding.totalVertical(), height);
}

void Row::accept(RendererVisitor& visitor)
{
    visitor.visit(*this, layoutMetadata);
}

void Row::accept(LayoutVisitor& layoutVisitor)
{
    layoutVisitor.visit(*this, layoutMetadata);
    this->applyLayout();
}

void Row::applyLayout()
{
    RowLayoutVisitor visitor(*this);

    for (auto& w : children)
    {
        w->accept(visitor);
    }

    short hsp = visitor.getUnusedHSpace();
    if (hsp <= 0)
    {
        return;
    }

    RowArrangementVisitor arrangementVisitor(hsp, children.size(), arrangement);

    for (auto& w : children)
    {
        w->accept(arrangementVisitor);
    }
}

Row* Row::setGap(unsigned short gap)
{
    this->gap = gap;
    return this;
}

Row* Row::setAlignment(VerticalAlignment alignment)
{
    this->alignment = alignment;
    return this;
}

Row* Row::setArrangement(Arrangement arrangement)
{
    this->arrangement = arrangement;
    return this;
}


Row::RowLayoutVisitor::RowLayoutVisitor(const Row& row)
: row(row)
{
    innerRect.x = row.layoutMetadata.contentX;
    innerRect.y = row.layoutMetadata.contentY;

    innerRect.width = row.layoutMetadata.contentWidth;
    innerRect.height = row.layoutMetadata.contentHeight;

    currentX = innerRect.x;

    // Fo this arrangements ignore gaps because it could mess with exact positioning
    ignoreGap = row.arrangement == Arrangement::SPACE_BETWEEN
        || row.arrangement == Arrangement::SPACE_EVENLY
        || row.arrangement == Arrangement::SPACE_AROUND;

    // For now width can only grow if row is set to fit content
    widthGrow = row.width.isFitContent();

    if (!widthGrow)
    {
        // We have absolute width set, we need to calculate free space for % content
        short childrenWidthSum = 0;

        for (auto& w : row.children)
        {
            childrenWidthSum += w->measureWidth();
        }

        freeHorizontalPercSpace = innerRect.width
            - childrenWidthSum
            - row.gap * (row.children.size() - 1);

        // We have also to divide it by total percentage of percent sized elements
        // Because the space needs to be divided between all elements, similar to
        // what it's done by browser engines. If we have 2 elements with 100% size,
        // each will have only 50% of space available
        // ----------------------
        // |      |      |      |
        // | 6px  | 100% | 100% |
        // |      |      |      |
        // ----------------------
        // (image is for row XD)
        // It won't be perfect because CSS calculates it a little bit differently
        // but good enough

        float totalPerc = 0;

        for (auto& w : row.children)
        {
            if (w->width.getUnit() == DimensionUnit::PERCENT)
            {
                totalPerc += w->width.getValue();
            }
            else if (w->getVerticalSizing() == Sizing::EXPAND)
            {
                totalPerc += 1.0;
            }
        }

        if (totalPerc > 1.0)
        {
            float sp = freeHorizontalPercSpace;
            sp /= totalPerc;
            freeHorizontalPercSpace = (short)sp;
        }
    }
}

void Row::RowLayoutVisitor::visit(Widget& widget, LayoutMetadata& metadata)
{
    // y pos and height
    // as y is easier in case of row

    Sizing vSizing = widget.getVerticalSizing();
    short h = 0;

    if (vSizing == Sizing::FIT_CONTENT)
    {
        h = widget.measureHeight();
    }
    else if (vSizing == Sizing::EXPAND)
    {
        h = innerRect.height;
    }
    else
    {
        h = widget.height.getPixelValue(innerRect.height);
    }

    if (h > innerRect.height)
    {
        metadata.overflow = true;
    }

    metadata.y = innerRect.y;
    metadata.contentY = innerRect.y + widget.padding.top;
    metadata.height = std::max<short>(0, h);
    metadata.contentHeight = std::max<short>(0, metadata.height - widget.padding.totalVertical());


    // alignment
    switch (row.alignment)
    {
    case VerticalAlignment::TOP:
        break;
    case VerticalAlignment::BOTTOM:
        metadata.y = innerRect.y + innerRect.height - metadata.height;
        metadata.contentY = metadata.y + widget.padding.top;
        break;
    case VerticalAlignment::CENTER:
        metadata.y = innerRect.y + (innerRect.height - metadata.height) / 2;
        metadata.contentY = metadata.y + widget.padding.top;
        break;
    }

    // x pos and width
    // Now it's fun!

    if (widthGrow)
    {
        // If width is growing then all percent values and expand values are 0, because we can't calculate them reliably.

        short w = widget.measureWidth();

        metadata.x = currentX;
        metadata.contentX = metadata.x + widget.padding.left;
        metadata.width = w;
        metadata.contentWidth = std::max<short>(0, metadata.width - widget.padding.totalHorizontal());
    }
    else
    {
        metadata.x = currentX;
        metadata.contentX = metadata.x + widget.padding.left;

        short w = widget.measureWidth();

        if (widget.getHorizontalSizing() == Sizing::PERCENT)
        {
            w = widget.width.getPixelValue(freeHorizontalPercSpace);
        }
        else if (widget.getHorizontalSizing() == Sizing::EXPAND)
        {
            w = Dimension::percent(1.0).getPixelValue(freeHorizontalPercSpace);
        }

        metadata.width = w;
        metadata.contentWidth = std::max<short>(0, metadata.width - widget.padding.totalHorizontal());
    }

    currentX += metadata.width + (ignoreGap ? 0 : row.gap);

}

short Row::RowLayoutVisitor::getUnusedHSpace()
{
    short hsp = innerRect.width - currentX;

    if (!ignoreGap)
    {
        // Cancel leading gap
        hsp += row.gap;
    }

    return std::max<short>(0, hsp);
}

Row::RowArrangementVisitor::RowArrangementVisitor(
    short unusedHSpace,
    short childrenCount,
    Arrangement arrangement
) : childrenCount(childrenCount), arrangement(arrangement)
{
    switch (arrangement)
    {
        case Arrangement::START:
            break;
        case Arrangement::END:
            offset = unusedHSpace;
            break;
        case Arrangement::CENTER:
            offset = unusedHSpace / 2;
            break;
        case Arrangement::SPACE_BETWEEN:
            offset = unusedHSpace / (childrenCount - 1);
            break;
        case Arrangement::SPACE_EVENLY:
            offset = unusedHSpace / (childrenCount + 1);
            break;
        case Arrangement::SPACE_AROUND:
            offset = unusedHSpace / (childrenCount * 2);
            break;
        
        default:
            break;
    }
}

void Row::RowArrangementVisitor::visit(Widget& widget, LayoutMetadata& metadata)
{
    switch (arrangement)
    {
        case Arrangement::START:
            break;
        case Arrangement::END:
        case Arrangement::CENTER:
            metadata.x += offset;
            metadata.contentX += offset;
            break;
        
        case Arrangement::SPACE_BETWEEN:
            metadata.x += offset * n;
            metadata.contentX += offset * n;
            break;
        
        case Arrangement::SPACE_EVENLY:
            metadata.x += offset + offset * n;
            metadata.contentX += offset + offset * n;
            break;

        case Arrangement::SPACE_AROUND:
            metadata.x += offset + offset * n * 2;
            metadata.contentX += offset + offset * n * 2;
            break;

        default:
            break;
    }

    n++;
}

} // y11
