#include "tweenmanager.h"

std::shared_ptr<TweenManager> TweenManager::instance;

std::shared_ptr<TweenManager> TweenManager::getInstance()
{
    if (!instance) {
        instance.reset(new TweenManager);
    }
    return instance;
}

void TweenManager::removeTween(uint64_t tweenId) {
    ofLog() << "removing tween " << tweenId << " from active tweens";
    markedForDeletion.push_back(tweenId);

}

void TweenManager::onUpdate(ofEventArgs &arg) {
    for (auto &markedId: markedForDeletion){
        for (auto i = activeTweens.cbegin(); i != activeTweens.cend(); ) {
            if ((*i)->getId() == markedId) {
                i = activeTweens.erase(i);
            } else ++i;
        }
        std::remove_if(activeTweens.begin(), activeTweens.end(), [markedId](std::shared_ptr<Tween> t) {
            return t->getId() == markedId;
        });
    }
    markedForDeletion.clear();
    for (auto& t: activeTweens) {
        t->update();
    }
}

std::shared_ptr<TweenBuilder> TweenManager::newTween() {
    return std::make_shared<TweenBuilder>();
}

TweenManager::~TweenManager() {
    ofRemoveListener(ofEvents().update, this, &TweenManager::onUpdate);
    activeTweens.clear();
}

TweenManager::TweenManager()
{
    ofAddListener(ofEvents().update, this, &TweenManager::onUpdate);
}

void TweenManager::addTween(std::shared_ptr<Tween> t) {
    activeTweens.push_back(t);
}

std::shared_ptr<TweenBuilder> TweenBuilder::withGetter(tween_getter_t g) {
    getter = g;
    if (!from_value_set) {
        from_value = g();
    }
    return shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withSetter(tween_setter_t s) {
    setter = s;

    return this->shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withEasing(ofxeasing::function f) {
    easing = f;
    return shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withCallback(tween_callback_t c) {
    callback = c;
    return shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withAnimationLength(uint64_t millis) {
    animation_length_millis = millis;
    return shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withFromValue(float from) {
    from_value = from;
    from_value_set = true;
    return shared_from_this();
}

std::shared_ptr<TweenBuilder> TweenBuilder::withToValue(float to) {
    to_value = to;
    to_value_set = true;
    return shared_from_this();
}

std::shared_ptr<Tween> TweenBuilder::build() {
    auto t = std::make_shared<Tween>(animation_length_millis,setter, getter, callback, to_value, easing, from_value, yoyo);
    TweenManager::getInstance()->addTween(t);
    auto cb = t->getCallback();
    auto tId = t->getId();
    auto newCb = [tId, cb]() {
        TweenManager::getInstance()->removeTween(tId);
        cb();
    };
    t->setCallback(newCb);
    return t;

}
