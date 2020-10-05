// © 2020 Joseph Cameron - All Rights Reserved

#include <string>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/event_bus.h>

TEST_CASE("event_bus", "[jfc::event_bus]")
{
    SECTION("add an observer and observe an event")
    {
        struct event
        {
            int info;
        };
        
        jfc::event_bus<event> bus; 

        int val(0);

        auto pObserver = std::make_shared<decltype(bus)::observer_type>([&val](event e)
            {
                val = e.info;
            });

        bus.add_observer(pObserver);

        bus.propagate_event({1});

        REQUIRE(val == 1);
    }

    SECTION("an observer that has fallen out of scope will be ignored by the bus")
    {
        struct event
        {
            int info;
        };
        
        jfc::event_bus<event> bus; 

        int val(0);

        {
            auto pObserver = std::make_shared<decltype(bus)::observer_type>([&val](event e)
                {
                    val = e.info;
                });

            bus.add_observer(pObserver);
        }

        bus.propagate_event({1});

        REQUIRE(val == 0);
    }

    SECTION("copy semantics work")
    {
        struct event
        {
            int info;
        };
        
        jfc::event_bus<event> a;

        int val(0);
        
        auto pObserver = std::make_shared<decltype(a)::observer_type>([&val](event e)
            {
                val = e.info;
            });

        a.add_observer(pObserver);

        decltype(a) b(a);

        b.propagate_event({1});

        REQUIRE(val == 1);
    }
    
    SECTION("move semantics work")
    {
        struct event
        {
            int info;
        };
        
        jfc::event_bus<event> a;

        int val(0);
        
        auto pObserver = std::make_shared<decltype(a)::observer_type>([&val](event e)
            {
                val = e.info;
            });

        a.add_observer(pObserver);

        decltype(a) b(std::move(a));

        b.propagate_event({1});

        REQUIRE(val == 1);
    }
}

