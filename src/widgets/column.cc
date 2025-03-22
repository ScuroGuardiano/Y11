#include "column.hpp"

namespace y11::widgets {

void Column::accept(RendererVisitor& visitor) {
    // TODO
}

void Column::accept(LayoutVisitor& layoutVisitor) {
    layoutVisitor.visit(*this, layoutMetadata);
}

bool Column::hasChildren() {
  return !children.empty();
}

} // namespace y11::widgets

