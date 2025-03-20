#include "widget.hpp"

namespace y11::widgets {

Widget::~Widget() {}

bool Widget::hasChilds() {
    return false;
}

std::shared_ptr<Widget> Widget::getWidgetById(unsigned short _) {
    return nullptr;
}

bool Widget::removeWidget(const std::shared_ptr<Widget> _) {
    return false;
}
bool Widget::removeWidgetById(unsigned short _) {
    return false;
}

}

