#include "composite.hpp"

namespace y11::widgets {

std::shared_ptr<Widget> Composite::getWidgetById(unsigned short id) {
    for (auto it = children.begin(); it < children.end(); it++) {
        if ((*it)->id == id) {
            return *it;
        }

        // Meanwhile in C#: if (el is Composite composite) XD
        if (Composite* composite = dynamic_cast<Composite*>((*it).get())) {
            if (auto found = composite->getWidgetById(id)) {
                return found;
            }
        }
    }

    return nullptr;
}

bool Composite::removeWidget(const std::shared_ptr<Widget> widget) {
    // Depth first search
    if (children.empty()) return false;

    for (auto it = children.begin(); it < children.end(); it++) {
        if (*it == widget) {
            children.erase(it);
            return true;
        }

        if (Composite* composite = dynamic_cast<Composite*>((*it).get())) {
            if (composite->removeWidget(widget)) {
                return true;
            }
        }
    }

    return false;
}

bool Composite::removeWidgetById(unsigned short id) {
    if (children.empty()) return false;

    for (auto it = children.begin(); it < children.end(); it++) {
        if ((*it)->id == id) {
            children.erase(it);
            return true;
        }

        if (Composite* composite = dynamic_cast<Composite*>((*it).get())) {
            if (composite->removeWidgetById(id)) {
                return true;
            }
        }
    }

    return false;
}

void Composite::foreach(const std::function<void (Widget&)>& f) {
    for (std::shared_ptr<Widget>& w : children) {
        f(*w);
    }
}

}
