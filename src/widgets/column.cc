#include "column.hpp"
#include "src/widgets/common.hpp"
#include "src/widgets/renderer_visitor.hpp"

namespace y11::widgets {

AutoSizeHint Column::getAutoSizeHint() {
    return AutoSizeHint::EXPAND;
}

bool Column::hasChildren() {
  return !children.empty();
}

void Column::accept(RendererVisitor& visitor) {
    visitor.visit(*this, layoutMetadata);
    this->applyLayout();
}

void Column::accept(LayoutVisitor& layoutVisitor) {
    layoutVisitor.visit(*this, layoutMetadata);
}

} // namespace y11::widgets

