#include "tween.h"

uint64_t Tween::tween_id = 1000;
Tween::Tween()
{

    id = nextTweenId();
}

Tween::Tween(uint64_t millis, tween_setter_t setter, tween_getter_t getter, tween_callback_t cb, float to, ofxeasing::function easing, float from, bool yoyo):
    id{Tween::nextTweenId()},
    setter{setter},
    getter{getter},
    to_value{to},
    from_value{from},
    callback{cb},
    animation_length_millis{millis},
    easing{easing},
    yoyo{yoyo}
{
    start_time = ofGetCurrentTime().getAsMilliseconds();
}

void Tween::update() {
    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto newVal = ofxeasing::map_clamp(now, start_time, start_time + animation_length_millis, from_value, to_value, easing);

    setter(newVal);
    if (newVal == to_value) {
        if (yoyo) {
            std::swap(to_value, from_value);
            start_time = ofGetCurrentTime().getAsMilliseconds();
        } else {
            if (callback) callback();
        }
    }
}

uint64_t Tween::getId() const
{
    return id;
}

std::function<void ()> Tween::getCallback() const
{
    return callback;
}

void Tween::setCallback(const std::function<void ()> &value)
{
    callback = value;
}

bool Tween::getYoyo() const
{
    return yoyo;
}

void Tween::setYoyo(bool value)
{
    yoyo = value;
}

uint64_t Tween::nextTweenId()
{
    return tween_id++;
}
