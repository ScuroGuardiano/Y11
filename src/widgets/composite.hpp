#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <vector>
#include "widget.hpp"

namespace y11::widgets {

class Composite {
public:
    template <class T>
    std::shared_ptr<T> addWidget(std::shared_ptr<T> widget) {
        static_assert(std::is_base_of<Widget, T>::value, "T must inherit from Widget");

        children.push_back(widget);
        return widget;
    }

    std::shared_ptr<Widget> getWidgetById(unsigned short id);
    bool removeWidget(std::shared_ptr<Widget> widget);
    bool removeWidgetById(unsigned short id);
    void foreach(const std::function<void (Widget&)>& f);

protected:
    std::vector<std::shared_ptr<Widget>> children;

};

}

