#ifndef TWEENMANAGER_H
#define TWEENMANAGER_H
#include "ofMain.h"
#include "tween.h"
#include "ofxEasing.h"

class TweenBuilder;
class ColorTweenBuilder;
class TweenManager
{
public:
    static std::shared_ptr<TweenManager> getInstance();
    void addTween(std::shared_ptr<Tween> t);

    void removeTween(uint64_t tweenId);
    void onUpdate(ofEventArgs& arg);
    std::shared_ptr<TweenBuilder> newTween();
    std::shared_ptr<ColorTweenBuilder> newColorTween();
    virtual ~TweenManager();
private:
    static std::shared_ptr<TweenManager> instance;
    TweenManager();
    std::vector<uint64_t> markedForDeletion;
    std::vector<std::shared_ptr<Tween>> activeTweens;
};



class TweenBuilder: public std::enable_shared_from_this<TweenBuilder> {
public:
    TweenBuilder() = default;
    std::shared_ptr<TweenBuilder> withGetter(tween_getter_t g);
    std::shared_ptr<TweenBuilder> withSetter(tween_setter_t s);
    std::shared_ptr<TweenBuilder> withEasing(ofxeasing::function f);
    std::shared_ptr<TweenBuilder> withCallback(tween_callback_t c);
    std::shared_ptr<TweenBuilder> withAnimationLength(uint64_t millis);
    std::shared_ptr<TweenBuilder> withFromValue(float from);

    std::shared_ptr<TweenBuilder> withToValue(float to);

    std::shared_ptr<TweenBuilder> withYoyo(bool yoyo);

    std::shared_ptr<Tween> build();
    virtual ~TweenBuilder() = default;
protected:
    ofxeasing::function easing = ofxeasing::linear::easeInOut;
    tween_setter_t setter;
    tween_getter_t getter;
    std::function<void()> callback = [](){};
    uint64_t start_time;
    uint64_t animation_length_millis;
    float from_value,to_value;
    bool from_value_set = false, to_value_set = false, yoyo = false;
};

class ColorTweenBuilder:  public enable_shared_from_this<ColorTweenBuilder> {
public:
    ColorTweenBuilder() =default;
    std::shared_ptr<ColorTweenBuilder> withEasing(ofxeasing::function f);
    std::shared_ptr<ColorTweenBuilder> withCallback(tween_callback_t c);
    std::shared_ptr<ColorTweenBuilder> withAnimationLength(uint64_t millis);

    std::shared_ptr<ColorTweenBuilder> withGetter(color_tween_getter_t g);
    std::shared_ptr<ColorTweenBuilder> withSetter(color_tween_setter_t s);
    std::shared_ptr<ColorTweenBuilder> withFromValue(ofColor from);

    std::shared_ptr<ColorTweenBuilder> withToValue(ofColor to);
    std::shared_ptr<ColorTweenBuilder> withYoyo(bool yoyo);

    std::shared_ptr<Tween> build();

    virtual ~ColorTweenBuilder() = default;
protected:
    color_tween_setter_t setter;
    color_tween_getter_t getter;
    ofColor from_value, to_value;
    ofxeasing::function easing = ofxeasing::linear::easeInOut;
    std::function<void()> callback = [](){};
    uint64_t start_time;
    uint64_t animation_length_millis;
    bool from_value_set = false, to_value_set = false, yoyo = false;
    };

#endif // TWEENMANAGER_H
