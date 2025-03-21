#include "column.hpp"

namespace y11::widgets {

Rect Column::getBoundingRect() {
    // TODO
}

Point Column::getPos() {

}

Size Column::getSize() {
    return {0, 0};
}

bool Column::hasChildren() {
  return !children.empty();
}

} // namespace y11::widgets
