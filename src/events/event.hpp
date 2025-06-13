#pragma once

#include "../widgets/widget.hpp" // Zakładam, że Widget tam jest

namespace y11::events {

enum class EventType {
    KeyUp,
    KeyDown,
    MouseDown,
    MouseUp,
    MouseMove,
    Click,
    Hover,
    Timeout,
    Interval,
    AnimationFrame,
    Quit
};

class Event {
public:
    virtual inline ~Event() {};
    
    EventType getType() {
        return eventType;
    }

    virtual widgets::Widget* getTarget() {
        return nullptr;
    }

protected:
    inline Event(EventType evtType) : eventType(evtType) {}

private:
    EventType eventType;
};

// --- Key events ---

enum class Key {
    Up, Down, Left, Right,
    A, B, C, D, E, F,
    G, H, I, J, K, L,
    M, N, O, P, Q, R,
    S, T, U, W, V, X,
    Y, Z,
    Esc, LAlt, RAlt,
    LCtrl, RCtrl, Space,
    LShift, RShift, Enter,
    Grave, Tab, BSpace,
    N0, N1, N2, N3, N4,
    N5, N6, N7, N8, N9,
    Unknown
};

struct KeyEvent : public Event {
    inline KeyEvent(EventType type, Key key) : Event(type), key(key) {}

    Key key;
};

using KeyDownEvent = KeyEvent;
using KeyUpEvent = KeyEvent;

// --- Mouse events ---

enum class MouseButton {
    Left,
    Right,
    Middle,
    Other
};

struct MouseButtonEvent : public Event {
    inline MouseButtonEvent(EventType type, int x, int y, MouseButton btn)
        : Event(type), x(x), y(y), button(btn) {}

    int x;
    int y;
    MouseButton button;
};

using MouseDownEvent = MouseButtonEvent;
using MouseUpEvent = MouseButtonEvent;

struct MouseMoveEvent : public Event {
    inline MouseMoveEvent(int x, int y, int dx, int dy)
        : Event(EventType::MouseMove), x(x), y(y), dx(dx), dy(dy) {}

    int x;
    int y;
    int dx;
    int dy;
};

struct ClickEvent : public Event {
    inline ClickEvent(int x, int y, MouseButton button)
        : Event(EventType::Click), x(x), y(y), button(button) {}

    int x;
    int y;
    MouseButton button;
};

struct HoverEvent : public Event {
    inline HoverEvent(widgets::Widget* widget)
        : Event(EventType::Hover), widget(widget) {}

    widgets::Widget* getTarget() override {
        return widget;
    }

private:
    widgets::Widget* widget;
};

// --- Timer events ---

struct TimeoutEvent : public Event {
    inline TimeoutEvent(unsigned long long timeoutDue, unsigned long long actualTriggerTime)
        : Event(EventType::Timeout), timeoutDue(timeoutDue), actualTriggerTime(actualTriggerTime) {}

    unsigned long long timeoutDue{};
    unsigned long long actualTriggerTime{};
};

struct IntervalEvent : public Event {
    inline IntervalEvent(unsigned long long plannedExecution, unsigned long long actualTriggerTime)
        : Event(EventType::Interval), plannedExecution(plannedExecution), actualTriggerTime(actualTriggerTime) {}

    unsigned long long plannedExecution{};
    unsigned long long actualTriggerTime{};
};

// --- AnimationFrame ---

struct AnimationFrameEvent : public Event {
    inline AnimationFrameEvent(unsigned long long timestamp)
        : Event(EventType::AnimationFrame), timestamp(timestamp) {}

    unsigned long long timestamp{};
};

// --- Quit ---

struct QuitEvent : public Event {
    inline QuitEvent() : Event(EventType::Quit) {}
};

} // namespace y11::events
