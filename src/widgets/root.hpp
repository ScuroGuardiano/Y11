#pragma once

#include "src/widgets/composite.hpp"
#include "src/widgets/layout.hpp"

namespace y11::widgets {

class Root : public Composite {
public:
    void setLayoutRect(const Rect& rect);
    void applyLayout();

private:
    DefaultLayoutVisitor layoutVisitor;
};

}

