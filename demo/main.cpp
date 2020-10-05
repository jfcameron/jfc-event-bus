// © 2020 Joseph Cameron - All Rights Reserved

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <jfc/event_bus.h>

int main(int count, char **args)
{
    struct event
    {
        int info;
    };

    jfc::event_bus<event> bus; 

    auto pObserver = std::make_shared<decltype(bus)::observer_type>([](event e)
    {
        std::cout << "observing: " << e.info << "\n";
    });

    bus.add_observer(pObserver);

    bus.propagate_event({1});

    return EXIT_SUCCESS;
}

