#ifndef COBSERVER_H
#define COBSERVER_H

#include <map>
#include <functional>

namespace bu {

//////////////////////////////////////////////////////////////
///   This is the class for Observer/Subject design patter
///
template <typename TEvent>
class CObserver
{
public:

    void RegisterFunc(const TEvent& event_, std::function<void(void*)> func_) {
        m_observersFunc.insert(std::pair<TEvent, std::function<void(void*)> >(event_, func_));
    }

    void SignalFunc(const TEvent& event_, void* parameter_ = nullptr) {
        for (auto it = m_observersFunc.begin(); it != m_observersFunc.end(); ++it) {
            if (it->first == event_)
                it->second(parameter_);
        }
    }

    void UnregisterFunc(std::function<void(void*)> func_) {
        auto it = m_observersFunc.begin();
        while (it != m_observersFunc.end()) {
            if (it.second == func_) {
                auto nit = it;
                ++it;
                m_observersFunc.erase(nit);
            }
            else {
                ++it;
            }
        }
    }

private:

    std::map<TEvent, std::function<void(void*)> > m_observersFunc;
};

}

#endif
