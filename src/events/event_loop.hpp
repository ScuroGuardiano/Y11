#pragma once

#include "../backend.hpp"
#include "event.hpp"
#include <map>
#include <functional>

namespace y11::events {

class EventLoop {
public:
    void bind(Backend* backend);
    void addEventListener(EventType eventType, std::function<void (Event&)> callback);
    void addEventListener(EventType eventType, widgets::Widget* target, std::function<void (Event&)> callback);
    int setTimeout(unsigned int ms, std::function<void (Event&)> callback);
    void clearTimeout(int id);
    int setInterval(unsigned int ms, std::function<void (Event&)> callback);
    void clearInterval(int id);

    void run();
    void stop();

private:
    struct EventListener {
        std::function<void (Event&)> callback;
        widgets::Widget* target;
    };

    struct Timeout {
        unsigned long long timeoutDue{};
        std::function<void (Event&)> callback; 
    };

    struct Interval {
        unsigned long long nextExecution{};
        unsigned int interval{};
        std::function<void (Event&)> callback;
    };

    bool running{};

    int lastHandle{};
    std::map<int, Timeout> timeouts{};
    std::map<int, Interval> intervals{};

    // Fun
    std::map<EventType, std::vector<EventListener>> eventListeners{};

    // Animations
    int animationIntervalInMs = 10;
    unsigned long long lastAnimationTime{};

    // Yeah, just an ordinary pointer beucase I need weak pointer
    // and I don't have time to mess with std::weak_ptr
    Backend* backend = nullptr;
};

}
