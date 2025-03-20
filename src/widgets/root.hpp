#pragma once

#include "widget.hpp"
#include <functional>
#include <vector>
#include <memory>

namespace y11::widgets {

class Root {
public:
    void addWidget(std::shared_ptr<Widget> widget);
    bool removeWidget(const std::shared_ptr<Widget> widget);
    bool removeWidgetById(unsigned short id);
    std::shared_ptr<Widget> getWidgetById(unsigned short id);
    void foreach(const std::function<void (Widget&)>& f);

private:
    std::vector<std::shared_ptr<Widget>> widgets;
};

}

