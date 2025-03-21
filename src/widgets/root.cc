#include "root.hpp"
#include "src/widgets/widget.hpp"
#include <memory>

namespace y11::widgets {

bool Root::removeWidget(const std::shared_ptr<Widget> widget) {
    // Depth first search
    if (widgets.empty()) return false;

    for (auto it = widgets.begin(); it < widgets.end(); it++) {
        if (*it == widget) {
            widgets.erase(it);
            return true;
        }

        if ((*it)->removeWidget(widget)) {
            return true;
        }
    }

    return false;
}

bool Root::removeWidgetById(unsigned short id) {
    if (widgets.empty()) return false;

    for (auto it = widgets.begin(); it < widgets.end(); it++) {
        if ((*it)->id == id) {
            widgets.erase(it);
            return true;
        }

        if ((*it)->removeWidgetById(id)) {
            return true;
        }
    }

    return false;
}

std::shared_ptr<Widget> Root::getWidgetById(unsigned short id) {
    for (auto it = widgets.begin(); it < widgets.end(); it++) {
        if ((*it)->id == id) {
            return *it;
        }

        if (auto found = (*it)->getWidgetById(id)) {
            return found;
        }
    }

    return nullptr;
}

void Root::foreach(const std::function<void (Widget&)>& f) {
    for (std::shared_ptr<Widget>& w : widgets) {
        f(*w);
    }
}

}
