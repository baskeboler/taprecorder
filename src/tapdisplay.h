#ifndef TAPDISPLAY_H
#define TAPDISPLAY_H

#include "sceneelement.h"
#include "taprecorderevent.h"

class TapDisplay: public SceneElement
{
public:
    TapDisplay(ScenePtr scene): SceneElement{scene} {

        ofAddListener(TapRecorderEvent::START_PLAYER, this, &TapDisplay::onPlayerStart);
        ofAddListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplay::onPlayerPause);
        ofAddListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplay::onPlayerReset);
    }

    virtual ~TapDisplay() {
        ofRemoveListener(TapRecorderEvent::START_PLAYER, this, &TapDisplay::onPlayerStart);
        ofRemoveListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplay::onPlayerPause);
        ofRemoveListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplay::onPlayerReset);

    }
    void onPlayerStart(TapRecorderEvent& ){
        ofLog() << "player start";
    }
    void onPlayerPause(TapRecorderEvent& ){
        ofLog() << "player pause";
    }
    void onPlayerReset(TapRecorderEvent& ){
        ofLog() << "player reset";
    }

    // SceneElement interface
public:
    void update() {

    }
    void draw() {


    }

    glm::vec2 getSize() const;
    void setSize(const glm::vec2 &value);

    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2 &value);

private:
    glm::vec2 position;
    glm::vec2 size;
};

#endif // TAPDISPLAY_H
