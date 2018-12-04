#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include "timer.h"

class timer
{
public:
    template <class callable, class... arguments>
    timer(int after, bool async, callable&& f, arguments&&... args) {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async) {
            std::thread([after, task]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }).detach();
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }
};