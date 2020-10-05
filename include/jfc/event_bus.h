// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_EVENT_BUS_H
#define JFC_EVENT_BUS_H

#include <vector>
#include <memory>
#include <functional>
#include <vector>

namespace jfc 
{
    /// \brief mechanism to message events to any number of observers
    template<class event_type_template>
    class event_bus final
    {
        public:
            using event_type = event_type_template;

            using observer_type = std::function<void(event_type)>;

            using observer_weak_ptr_type = std::weak_ptr<observer_type>;

            using observer_shared_ptr_type = std::shared_ptr<observer_type>;

        private:
            mutable std::vector<observer_weak_ptr_type> m_Observers;

        public:
            /// \brief notify all observers of the event
            /// \remark removes observers that are null
            void propagate_event(event_type e) const
            {
                for (size_t i(0); i < m_Observers.size(); ++i)
                {
                    if (auto p = m_Observers[i].lock())
                    {
                        (*p)(e);
                    }
                    else
                    {
                        m_Observers.erase(m_Observers.begin() + i);
                    }
                }
            }

            /// \brief adds an observer, to be notified when an event occurs
            void add_observer(observer_weak_ptr_type observer)
            {
                m_Observers.push_back(observer);
            }

            /// \brief explicit move semantics
            event_bus<event_type> &operator=(event_bus<event_type> &&) = default;
            /// \brief explicit move semantics
            event_bus(event_bus<event_type> &&) = default;

            /// \brief explicit copy semantics
            event_bus<event_type> &operator=(const event_bus<event_type> &) = default;
            /// \brief explicit copy semantics
            event_bus(const event_bus<event_type> &) = default;

            event_bus() = default;

            ~event_bus() = default;
    };
}

#endif

