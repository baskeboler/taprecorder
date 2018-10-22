#ifndef STATE_H
#define STATE_H

#include "ofMain.h"
#include <memory>

class Scene;


typedef std::shared_ptr<Scene> ScenePtr;
class State: public std::enable_shared_from_this<State>
{
public:
    enum Event {
        PUSH,
        RELEASE,
        UPDATE
    };
    State(ScenePtr scene);

    virtual std::shared_ptr<State> update(Event evt, std::shared_ptr<Scene> scene) = 0;

    virtual ~State();
    std::shared_ptr<Scene> scene;
    float start_radius;
    float  animation_length = 250;
    static std::shared_ptr<State> defaultState(ScenePtr scene);
};

class PushedState;

class InitState: public State {

    // State interface
public:
    InitState(ScenePtr scene);
    std::shared_ptr<State> update(Event evt, std::shared_ptr<Scene> scene);

    virtual ~InitState(){}

private:
    double start_time = 0;
    ofColor startColor;
};

class PushedState: public State {

    // State interface
public:
    PushedState(ScenePtr scene);
    std::shared_ptr<State> update(Event evt, std::shared_ptr<Scene> scene);

    virtual ~PushedState(){}

private:
    double start_time = 0;
    ofColor startColor;
};



#endif // STATE_H
