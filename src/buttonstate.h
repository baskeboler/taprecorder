#ifndef BUTTONSTATE_H
#define BUTTONSTATE_H
#include "ofMain.h"
#include "state.h"
#include "ofxEasing.h"

#include "tapbutton.h"
//class TapButton;

extern template class State<TapButton>;

class ButtonState: public State<TapButton> {
  public:
    explicit ButtonState(std::shared_ptr<TapButton> btn);
    virtual std::shared_ptr<State<TapButton>> update() = 0;
    virtual ~ButtonState() = default;
};

class InitState: public ButtonState {

    // State interface
public:
    InitState(std::shared_ptr<TapButton> btn);

    virtual std::shared_ptr<State<TapButton>> update();

    virtual ~InitState(){
//        ButtonState::~State();
        ofRemoveListener(ofEvents().mousePressed, this, &InitState::onMousePress);
    }

    void onMousePress(ofMouseEventArgs& evt) {
        if (subject->hitTest(evt)) {
            pressed = true;
        }
    }

private:
    double start_time = 0;
    ofColor startColor;
    bool pressed = false;
    float start_radius;
    float  animation_length = 250;
};

class PushedState: public ButtonState {

    // State interface
public:
    PushedState(std::shared_ptr<TapButton> scene);
    virtual std::shared_ptr<State<TapButton>> update();

    virtual ~PushedState(){
//        ButtonState::~State();

        ofRemoveListener(ofEvents().mousePressed, this, &PushedState::onMouseRelease);
    }

    void onMouseRelease(ofMouseEventArgs& evt) {
        released = true;
    }

private:
    double start_time = 0;
    ofColor startColor;
    float start_radius;
    float  animation_length = 250;
    bool released = false;
};


#endif // BUTTONSTATE_H
