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
    virtual void update();
    uint64_t getId() const;

    std::function<void ()> getCallback() const;
    void setCallback(const std::function<void ()> &value);

    bool getYoyo() const;
    void setYoyo(bool value);
    virtual ~Tween() = default;
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

typedef  std::function<void(ofColor)> color_tween_setter_t;
typedef std::function<ofColor()> color_tween_getter_t;
typedef std::function<void()> color_tween_callback_t;


class ColorTween :public Tween{
public:
    ColorTween(uint64_t millis, color_tween_setter_t setter, color_tween_getter_t getter,
          tween_callback_t cb, ofColor to, ofxeasing::function easing,
          ofColor from, bool yoyo ):
        Tween(millis, [](float){}, [](){return 0.0;}, cb, 0, easing,0, yoyo),
        from_value{from},
        to_value{to},
        getter{getter},
        setter{setter}

    {}

    virtual void update();
    virtual ~ColorTween()=default;
protected:
    ofColor from_value, to_value;
    color_tween_getter_t getter;
    color_tween_setter_t setter;

};

#endif // TWEEN_H
