#include "tapdisplaystate.h"

template class State<TapDisplay>;

TapDisplayState::TapDisplayState(std::shared_ptr<TapDisplay> d): State{d} {}

TapDisplayInitState::TapDisplayInitState(std::shared_ptr<TapDisplay> d): TapDisplayState(d) {

    ofAddListener(TapRecorderEvent::START_PLAYER, this, &TapDisplayInitState::onStartPlayer);
    ofAddListener(TapRecorderEvent::START_RECORDING, this, &TapDisplayInitState::onStartRecorder);
    subject->setStatusLabel("idle");
}

void TapDisplayInitState::onStartPlayer(TapRecorderEvent &) {
    playerStarted = true;
    subject->setTimePlayerStart(ofGetCurrentTime().getAsMilliseconds());
}

void TapDisplayInitState::onStartRecorder(TapRecorderEvent &) {
    recorderStarted = true;
    subject->setTimeRecordingStart(ofGetCurrentTime().getAsMilliseconds());
}

TapDisplayInitState::~TapDisplayInitState() {
    ofRemoveListener(TapRecorderEvent::START_PLAYER, this, &TapDisplayInitState::onStartPlayer);
    ofRemoveListener(TapRecorderEvent::START_RECORDING, this, &TapDisplayInitState::onStartRecorder);

}

std::shared_ptr<State<TapDisplay> > TapDisplayInitState::update(){
    if (playerStarted) {
        return std::make_shared<TapDisplayPlayingState>(subject);
    }
    if (recorderStarted) {
        return std::make_shared<TapDisplayRecordingState>(subject);
    }
    return shared_from_this();
}

TapDisplayPlayingState::TapDisplayPlayingState(std::shared_ptr<TapDisplay> d): TapDisplayState(d){
    ofAddListener(TapRecorderEvent::TOGGLE_PAUSE, this, &TapDisplayPlayingState::onPause);
    ofAddListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplayPlayingState::onStop);
    subject->setStatusLabel("playing");
}

void TapDisplayPlayingState::onStop(TapRecorderEvent &e) {
    stopped = true;
}

void TapDisplayPlayingState::onPause(TapRecorderEvent &e) {
    paused = !paused;
    if (paused) subject->setStatusLabel("playing paused");
    else subject->setStatusLabel("playing");
}

TapDisplayPlayingState::~TapDisplayPlayingState() {
    ofRemoveListener(TapRecorderEvent::TOGGLE_PAUSE, this, &TapDisplayPlayingState::onPause);
    ofRemoveListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplayPlayingState::onStop);

}

std::shared_ptr<State<TapDisplay> > TapDisplayPlayingState::update() {
    if (stopped) {
        return std::make_shared<TapDisplayInitState>(subject);
    }
    return shared_from_this();
}

TapDisplayRecordingState::TapDisplayRecordingState(std::shared_ptr<TapDisplay> d): TapDisplayState(d){
    ofAddListener(TapRecorderEvent::TOGGLE_PAUSE, this, &TapDisplayRecordingState::onPause);
    ofAddListener(TapRecorderEvent::RESET_RECORDING, this, &TapDisplayRecordingState::onStop);
    subject->setStatusLabel("recording");
}

void TapDisplayRecordingState::onStop(TapRecorderEvent &e) {
    stopped = true;
}

void TapDisplayRecordingState::onPause(TapRecorderEvent &e) {
    paused = !pause;
    if (pause ) subject->setStatusLabel("recording paused");
    else subject->setStatusLabel("recording");
}

TapDisplayRecordingState::~TapDisplayRecordingState() {
    ofRemoveListener(TapRecorderEvent::TOGGLE_PAUSE, this, &TapDisplayRecordingState::onPause);
    ofRemoveListener(TapRecorderEvent::RESET_RECORDING, this, &TapDisplayRecordingState::onStop);

}

std::shared_ptr<State<TapDisplay> > TapDisplayRecordingState::update() {
    if (stopped) {
        return std::make_shared<TapDisplayInitState>(subject);
    }
    if (!paused) {

        auto start = subject->getTimeRecordingStart();

        auto now = ofGetCurrentTime().getAsMilliseconds();
        auto elapsed = now - start;
        subject->setTimeElapsed(elapsed);
        std::stringstream ss;
        ss << std::fixed << 0.001 * elapsed << " s";
        subject->setRightLabel(ss.str());
    }
    return shared_from_this();
}
