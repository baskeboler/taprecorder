#include "buttonstate.h"
#include "tapbutton.h"
#include "ofxEasing.h"
#include "state.h"




template class State<TapButton>;


ButtonState::ButtonState(std::shared_ptr<TapButton> btn): State<TapButton>::State(btn) {}


InitState::InitState(std::shared_ptr<TapButton> btn): ButtonState (btn) {

    ofAddListener(ofEvents().mousePressed, this, &InitState::onMousePress);
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = subject->buttonColor;
    start_radius = subject->buttonRadius;
    animation_length = 250;
}

std::shared_ptr<State<TapButton>> InitState::update() {

    if (pressed) {

        auto ptr = std::make_shared<PushedState>(subject);
        return std::dynamic_pointer_cast<ButtonState>(ptr);
    }
    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto targetColor = subject->primaryColor;

    float r, g,b;
    subject->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, 100, ofxeasing::bounce::easeIn);
    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
    subject->buttonColor = ofColor(r, g, b);

    return this->shared_from_this();

}

PushedState::PushedState(std::shared_ptr<TapButton> scene): ButtonState (scene){
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = scene->buttonColor;
    start_radius = scene->buttonRadius;

    ofAddListener(ofEvents().mouseReleased, this, &PushedState::onMouseRelease);
}

std::shared_ptr<State<TapButton>> PushedState::update() {

    if (released)
        return std::dynamic_pointer_cast<ButtonState>(std::make_shared<InitState>(subject));

    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto targetColor = subject->activeColor;

    float  r, g,b;
    subject->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, 120, ofxeasing::bounce::easeIn);
    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
    subject->buttonColor = ofColor(r, g, b);

    return shared_from_this();
}
