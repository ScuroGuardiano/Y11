#include "event_loop.hpp"
#include <chrono>
#include <thread>

namespace y11::events {

void EventLoop::bind(Backend* backend) {
    this->backend = backend;
}

void EventLoop::addEventListener(EventType eventType, std::function<void (Event&)> callback) {
    EventListener listener {
        .callback = callback,
        .target = nullptr
    };

    this->eventListeners[eventType].push_back(listener);
}

void EventLoop::addEventListener(EventType eventType, widgets::Widget* target, std::function<void (Event&)> callback) {
    EventListener listener {
        .callback = callback,
        .target = target
    };

    this->eventListeners[eventType].push_back(listener);
}

int EventLoop::setTimeout(unsigned int ms, std::function<void (Event&)> callback) {
    using namespace std::chrono;

    auto now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();


    Timeout timeout {
        .timeoutDue = now + ms,
        .callback = callback
    };

    timeouts[++lastHandle] = timeout;

    return lastHandle;
}

void EventLoop::clearTimeout(int id) {
    timeouts.erase(id);
}

int EventLoop::setInterval(unsigned int ms, std::function<void (Event&)> callback) {
    using namespace std::chrono;

    auto now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();

    Interval interval {
        .nextExecution = now + ms,
        .interval = ms,
        .callback = callback
    };

    intervals[++lastHandle] = interval;
}

void EventLoop::clearInterval(int id) {
    intervals.erase(id);
}

void EventLoop::run() {
    using namespace std::chrono;

    running = true;
    lastAnimationTime = duration_cast<milliseconds>(
                            system_clock::now().time_since_epoch())
                            .count();

    while (running) {
        auto now = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        ).count();

        // First check any timeouts and intervals
        // as we want them to be as precise as possible

        for (auto& [id, timeout] : timeouts) {
            if (timeout.timeoutDue >= now) {
                TimeoutEvent timeoutEvt{ timeout.timeoutDue, now };
                timeout.callback(timeoutEvt);

                timeouts.erase(id);

                // One timeout per iteration because if user cleared another timeout
                // in callback it would cause undefined behaviour
                // It's a workaround because I have no time for better solution XD
                break;
            }
        }

        for (auto& [_, interval] : intervals) {
            if (interval.nextExecution >= now) {
                IntervalEvent intervalEvt{ interval.nextExecution, now };
                interval.nextExecution = now + interval.interval;

                interval.callback(intervalEvt);

                // One interval per iteration because if user cleared another interval
                // in callback it would cause undefined behaviour
                // It's a workaround because I have no time for better solution XD
                break;
            }
        }

        if ((lastAnimationTime + animationIntervalInMs) >= now) {
            AnimationFrameEvent evt{ now };

            auto& listeners = eventListeners[EventType::AnimationFrame];

            for (auto& l : listeners) {
                l.callback(evt);
            }

            lastAnimationTime = now;
        }

        if (backend != nullptr) {
            while (auto evt = backend->pollEvent()) {
                EventType t = evt->getType();

                auto& listeners = eventListeners[t];

                for (auto& l : listeners) {
                    if (l.target == evt->getTarget()) {
                        l.callback(*evt);
                    }
                    else if (l.target == nullptr) {
                        l.callback(*evt);
                    }
                }
            }
        }
        
        // 10000 iterations per second should be fine. Ideally we wouldn't have to do that at all
        // But again, I have no time to mess with epoll and other non-blocking event stuff xD
        std::this_thread::sleep_for(microseconds(100));
    }
}

void EventLoop::stop() {
    running = false;
}

}
