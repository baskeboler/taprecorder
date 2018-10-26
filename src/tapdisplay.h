#ifndef TAPDISPLAY_H
#define TAPDISPLAY_H

#include "sceneelement.h"
#include "taprecorderevent.h"

class TapDisplay: public SceneElement, public enable_shared_from_this<TapDisplay>
{
public:
    TapDisplay(ScenePtr scene);

    void init();
    virtual ~TapDisplay();
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
    void update();
    void draw();

    glm::vec2 getSize() const;
    void setSize(const glm::vec2 &value);

    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2 &value);

    std::string getRightLabel() const;
    void setRightLabel(const std::string &value);

    std::string getLeftLabel() const;
    void setLeftLabel(const std::string &value);

    uint64_t getTimePlayerStart() const;
    void setTimePlayerStart(const uint64_t &value);

    uint64_t getTimeRecordingStart() const;
    void setTimeRecordingStart(const uint64_t &value);

    uint64_t getTimeRecordingStop() const;
    void setTimeRecordingStop(const uint64_t &value);

    uint64_t getTimeElapsed() const;
    void setTimeElapsed(const uint64_t &value);

    std::string getStatusLabel() const;
    void setStatusLabel(const std::string &value);

private:
    std::vector<double> getTaps() const;
    glm::vec2 position;
    glm::vec2 size;
    float recPos = 0;
    float playPos = 0;
    uint64_t timePlayerStart;
    uint64_t timeRecordingStart;
    uint64_t timeRecordingStop;
    uint64_t timeElapsed = 0;
    std::string leftLabel = "0", rightLabel = "0", statusLabel = "idle";
    std::shared_ptr<State<TapDisplay>> state;
};

#endif // TAPDISPLAY_H
