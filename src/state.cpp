#include "state.h"
#include "scene.h"
#include "ofxEasing.h"

State::State(ScenePtr scene): scene{scene} {
    start_radius = scene->buttonRadius;
}

State::~State() {}

std::shared_ptr<State> State::defaultState(ScenePtr scene)
{
    return std::make_shared<InitState>(scene);
}


InitState::InitState(ScenePtr scene): State{scene} {
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = scene->buttonColor;
}

std::shared_ptr<State> InitState::update(State::Event evt, std::shared_ptr<Scene> scene) {

    if (evt == PUSH) {

        auto ptr = std::make_shared<PushedState>(scene);
        return std::dynamic_pointer_cast<State>(ptr);
    }
    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto targetColor = ofColor::red;

    float r, g,b;
    scene->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, 100, ofxeasing::bounce::easeIn);
    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
    scene->buttonColor = ofColor(r, g, b);

    return this->shared_from_this();

}

std::shared_ptr<State> PushedState::update(State::Event evt, std::shared_ptr<Scene> scene) {

    if (evt == RELEASE)
        return std::dynamic_pointer_cast<State>(std::make_shared<InitState>(scene));

    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto targetColor = ofColor::darkRed;

    float  r, g,b;
    scene->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, 120, ofxeasing::bounce::easeIn);
    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
    scene->buttonColor = ofColor(r, g, b);

    return shared_from_this();
}

PushedState::PushedState(ScenePtr scene): State{scene} {
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = scene->buttonColor;
}
