#include "buttonstate.h"
#include "tapbutton.h"
#include "ofxEasing.h"
#include "state.h"
#include "tweenmanager.h"


template class State<TapButton>;


ButtonState::ButtonState(std::shared_ptr<TapButton> btn): State<TapButton>::State(btn) {}


InitState::InitState(std::shared_ptr<TapButton> btn): ButtonState (btn) {

    ofAddListener(ofEvents().mousePressed, this, &InitState::onMousePress);
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = subject->buttonColor;
    start_radius = subject->buttonRadius;
    animation_length = 250;

    TweenManager::getInstance()->newTween()
            ->withAnimationLength(animation_length)
            ->withGetter([&](){return subject->getScale();})
            ->withSetter([&](float v) {subject->setScale(v);})
            ->withToValue(1.0)
            ->withYoyo(false)
            ->build();

    TweenManager::getInstance()->newTween()
            ->withAnimationLength(animation_length)
            ->withGetter([&](){return subject->label->getScale();})
            ->withSetter([&](float v) {subject->label->setScale(v);})
            ->withToValue(1.0)
            ->withYoyo(false)
            ->build();

    TweenManager::getInstance()->newColorTween()
            ->withAnimationLength(animation_length)
            ->withToValue(subject->primaryColor)
            ->withGetter([&](){ return subject->buttonColor; })
            ->withSetter([&](ofColor c) { subject->buttonColor = c; })
            ->build();
}

std::shared_ptr<State<TapButton>> InitState::update() {

    if (pressed) {

        auto ptr = std::make_shared<PushedState>(subject);
        return std::dynamic_pointer_cast<ButtonState>(ptr);
    }
//    auto now = ofGetCurrentTime().getAsMilliseconds();
//    auto targetColor = subject->primaryColor;

//    float r, g,b;
//    subject->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, 100, ofxeasing::quad::easeInOut);
//    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
//    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
//    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
//    subject->buttonColor = ofColor(r, g, b);

    return this->shared_from_this();

}

PushedState::PushedState(std::shared_ptr<TapButton> scene): ButtonState (scene){
    start_time = ofGetCurrentTime().getAsMilliseconds();
    startColor = scene->buttonColor;
    start_radius = scene->buttonRadius;

    TweenManager::getInstance()->newTween()
            ->withAnimationLength(animation_length)
            ->withGetter([&](){return subject->getScale();})
            ->withSetter([&](float v) {subject->setScale(v);})
            ->withToValue(1.1)
            ->withYoyo(false)
            ->build();

    TweenManager::getInstance()->newTween()
            ->withAnimationLength(animation_length)
            ->withGetter([&](){return subject->label->getScale();})
            ->withSetter([&](float v) {subject->label->setScale(v);})
            ->withToValue(1.5)
            ->withYoyo(false)
            ->build();

    TweenManager::getInstance()->newColorTween()
            ->withAnimationLength(animation_length)
            ->withToValue(subject->activeColor)
            ->withGetter([&](){ return subject->buttonColor; })
            ->withSetter([&](ofColor c) { subject->buttonColor = c; })
            ->build();
    ofAddListener(ofEvents().mouseReleased, this, &PushedState::onMouseRelease);
}

std::shared_ptr<State<TapButton>> PushedState::update() {

    if (released)
        return std::dynamic_pointer_cast<ButtonState>(std::make_shared<InitState>(subject));

//    auto now = ofGetCurrentTime().getAsMilliseconds();
//    auto targetColor = subject->activeColor;

//    float  r, g,b;
//    subject->buttonRadius = ofxeasing::map_clamp(now, start_time, start_time + animation_length, start_radius, start_radius * 1.1, ofxeasing::quad::easeInOut);
//    r = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.r, targetColor.r, ofxeasing::linear::easeIn);
//    g = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.g, targetColor.g, ofxeasing::linear::easeIn);
//    b = ofxeasing::map_clamp(now, start_time, start_time + animation_length, startColor.b, targetColor.b, ofxeasing::linear::easeIn);
//    subject->buttonColor = ofColor(r, g, b);

    return shared_from_this();
}
