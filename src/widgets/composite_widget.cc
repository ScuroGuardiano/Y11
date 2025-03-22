#include "composite_widget.hpp"
#include <memory>

namespace y11::widgets {

std::shared_ptr<Widget> CompositeWidget::getWidgetById(unsigned short id) {
    for (auto it = children.begin(); it < children.end(); it++) {
        if ((*it)->id == id) {
            return *it;
        }

        if (auto found = (*it)->getWidgetById(id)) {
            return found;
        }
    }

    return nullptr;
}

bool CompositeWidget::removeWidget(const std::shared_ptr<Widget> widget) {
    // Depth first search
    if (children.empty()) return false;

    for (auto it = children.begin(); it < children.end(); it++) {
        if (*it == widget) {
            children.erase(it);
            return true;
        }

        if ((*it)->removeWidget(widget)) {
            return true;
        }
    }

    return false;
}

bool CompositeWidget::removeWidgetById(unsigned short id) {
    if (children.empty()) return false;

    for (auto it = children.begin(); it < children.end(); it++) {
        if ((*it)->id == id) {
            children.erase(it);
            return true;
        }

        if ((*it)->removeWidgetById(id)) {
            return true;
        }
    }

    return false;
}

void CompositeWidget::foreach(const std::function<void (Widget&)>& f) {
    for (std::shared_ptr<Widget>& w : children) {
        f(*w);
    }
}

}
