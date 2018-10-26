#ifndef TWEEN_H
#define TWEEN_H
#include "ofMain.h"
#include "ofxEasing.h"

typedef  std::function<void(double)> tween_setter_t;
typedef std::function<double()> tween_getter_t;
typedef std::function<void()> tween_callback_t;

class Tween
{
public:
    Tween();
    Tween(uint64_t millis, tween_setter_t setter, tween_getter_t getter,
          tween_callback_t cb, float to, ofxeasing::function easing,
          float from, bool yoyo );
    void update();
    uint64_t getId() const;

    std::function<void ()> getCallback() const;
    void setCallback(const std::function<void ()> &value);

    bool getYoyo() const;
    void setYoyo(bool value);

protected:
    bool yoyo = false;
    uint64_t id;
    ofxeasing::function easing = ofxeasing::linear::easeInOut;
    std::function<void(double)> setter;
    std::function<double()> getter;
    std::function<void()> callback;
    uint64_t start_time;
    uint64_t animation_length_millis;
    float from_value;
    float to_value;

    static uint64_t tween_id;
    static uint64_t nextTweenId();
};

#endif // TWEEN_H
