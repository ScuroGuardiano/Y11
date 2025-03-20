#pragma once

#include "widgets/root.hpp"

namespace y11 {

class Backend {
public:
    virtual void init() = 0;
    virtual void render(widgets::Root& widgetTree) = 0;
    virtual ~Backend() = 0;

protected:
    Backend() = default;
};

inline Backend::~Backend() {}

}

