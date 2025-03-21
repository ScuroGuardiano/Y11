#include "sfml_widget_metadata.hpp"
#include "src/rect.hpp"

namespace y11 {

Size SfmlWidgetMetadata::getSize() {
    return { width, height };
}

Point SfmlWidgetMetadata::getPos() {
    return { x, y };
}

Rect SfmlWidgetMetadata::getBoudingRect() {
    return { x, y, width, height };
}

}
