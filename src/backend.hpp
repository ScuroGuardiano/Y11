#pragma once

#include "widgets/root.hpp"
#include "events/event.hpp"

namespace y11 {

class Backend {
public:
    virtual void init() = 0;
    virtual void render(widgets::Root& widgetTree) = 0;
    virtual ~Backend() = 0;
    virtual unsigned int getWidth() = 0;
    virtual unsigned int getHeight() = 0;
    virtual void renderRaw(short, short, short) = 0;
    
    // Events
    /**
     * If there's an event available to be polled it should be returned,
     * otherwise nullptr should be returned.
     */
    virtual std::unique_ptr<events::Event> pollEvent() = 0;
    virtual bool getKeyState(events::Key) = 0;

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
    inline bool getKeyState(events::Key) override {return false;};
    inline void renderRaw(short,short,short) override {return;}
    inline std::unique_ptr<events::Event> pollEvent() { return nullptr; }
};

}

