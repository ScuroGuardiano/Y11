#pragma once

#include "src/widgets/layout.hpp"
#include "widget.hpp"
#include <functional>
#include <vector>
#include <memory>

namespace y11::widgets {

class Root {
public:
    template <class T>
    std::shared_ptr<T> addWidget(std::shared_ptr<T> widget) {
        static_assert(std::is_base_of<Widget, T>::value, "T must inherit from Widget");

        widgets.push_back(widget);
        return widget;
    };

    void setLayoutRect(const Rect& rect);
    void applyLayout();

    bool removeWidget(std::shared_ptr<Widget> widget);
    bool removeWidgetById(unsigned short id);
    std::shared_ptr<Widget> getWidgetById(unsigned short id);
    void foreach(const std::function<void (Widget&)>& f);

private:
    std::vector<std::shared_ptr<Widget>> widgets;
    DefaultLayoutVisitor layoutVisitor;
};

}

