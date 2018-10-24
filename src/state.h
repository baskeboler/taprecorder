#ifndef STATE_H
#define STATE_H

#include "ofMain.h"
#include <memory>

template <typename T>
class State: public std::enable_shared_from_this<State<T>>
{
public:
    enum Event {
        PUSH,
        RELEASE,
        UPDATE
    };
    State(std::shared_ptr<T> s): subject{s} {
        //    start_radius = scene->buttonRadius;
    }

    virtual std::shared_ptr<State<T>> update() = 0;

    virtual ~State() = default;
    std::shared_ptr<T> subject;
};


#endif // STATE_H
