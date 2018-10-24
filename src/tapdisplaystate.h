#ifndef TAPDISPLAYSTATE_H
#define TAPDISPLAYSTATE_H
#include "state.h"
#include "tapdisplay.h"

extern template class State<TapDisplay>;


class TapDisplayState: public State<TapDisplay>
{
public:
    TapDisplayState(std::shared_ptr<TapDisplay> d);
    virtual std::shared_ptr<State<TapDisplay>> update() = 0;
    virtual ~TapDisplayState() = default;
};

class TapDisplayInitState: public TapDisplayState{


    // TapDisplayState interface
public:
    TapDisplayInitState(std::shared_ptr<TapDisplay> d);

    void onStartPlayer(TapRecorderEvent&);
    void onStartRecorder(TapRecorderEvent& );
    virtual ~TapDisplayInitState();
    std::shared_ptr<State<TapDisplay> > update();

private:
    bool playerStarted = false;
    bool recorderStarted = false;
};

class TapDisplayPlayingState: public TapDisplayState {
public:
    TapDisplayPlayingState(std::shared_ptr<TapDisplay> d);

    void onStop(TapRecorderEvent& e);
    void onPause(TapRecorderEvent& e);
    virtual ~TapDisplayPlayingState();
    std::shared_ptr<State<TapDisplay> > update();

private:
    bool stopped = false, paused = false;
};


class TapDisplayRecordingState: public TapDisplayState {
public:
    TapDisplayRecordingState(std::shared_ptr<TapDisplay> d);

    void onStop(TapRecorderEvent& e);
    void onPause(TapRecorderEvent& e);
    virtual ~TapDisplayRecordingState();
    std::shared_ptr<State<TapDisplay> > update();

private:
    bool stopped = false, paused = false;
};

#endif // TAPDISPLAYSTATE_H
