#ifndef TWEENMANAGER_H
#define TWEENMANAGER_H
#include "ofMain.h"
#include "tween.h"
#include "ofxEasing.h"

class TweenBuilder;
class TweenManager
{
public:
    static std::shared_ptr<TweenManager> getInstance();
    void addTween(std::shared_ptr<Tween> t);

    void removeTween(uint64_t tweenId);
    void onUpdate(ofEventArgs& arg);
    std::shared_ptr<TweenBuilder> newTween();
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

    std::shared_ptr<TweenBuilder> withYoyo(bool yoyo) {
        this->yoyo = yoyo;
        return shared_from_this();
    }

    std::shared_ptr<Tween> build();
    virtual ~TweenBuilder() = default;
private:
    ofxeasing::function easing = ofxeasing::linear::easeInOut;
    tween_setter_t setter;
    tween_getter_t getter;
    std::function<void()> callback = [](){};
    uint64_t start_time;
    uint64_t animation_length_millis;
    float from_value;
    bool from_value_set = false;
    float to_value;
    bool to_value_set = false;
    bool yoyo = false;
};

#endif // TWEENMANAGER_H
