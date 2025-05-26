#pragma once

#include "widgets/root.hpp"

namespace y11 {

class Backend {
public:
    virtual void init() = 0;
    virtual void render(widgets::Root& widgetTree) = 0;
    virtual ~Backend() = 0;
    virtual unsigned int getWidth() = 0;
    virtual unsigned int getHeight() = 0;

protected:
    Backend() = default;
};

inline Backend::~Backend() {}

class BlankBackend : public Backend {
public:
    inline void init() override {}
    inline void render(widgets::Root&) override {}
    inline unsigned int getWidth() override {return 0;};
    inline unsigned int getHeight() override {return 0;};
};

}

