#include "tapdisplaystate.h"

template class State<TapDisplay>;

TapDisplayState::TapDisplayState(std::shared_ptr<TapDisplay> d): State{d} {}

TapDisplayInitState::TapDisplayInitState(std::shared_ptr<TapDisplay> d): TapDisplayState(d) {

    ofAddListener(TapRecorderEvent::START_PLAYER, this, &TapDisplayInitState::onStartPlayer);
    ofAddListener(TapRecorderEvent::START_RECORDING, this, &TapDisplayInitState::onStartRecorder);
}

void TapDisplayInitState::onStartPlayer(TapRecorderEvent &) {
    playerStarted = true;
}

void TapDisplayInitState::onStartRecorder(TapRecorderEvent &) {
    recorderStarted = true;
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
    ofAddListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplayPlayingState::onPause);
    ofAddListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplayPlayingState::onStop);
}

void TapDisplayPlayingState::onStop(TapRecorderEvent &e) {
    stopped = true;
}

void TapDisplayPlayingState::onPause(TapRecorderEvent &e) {
    paused = true;
}

TapDisplayPlayingState::~TapDisplayPlayingState() {
    ofRemoveListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplayPlayingState::onPause);
    ofRemoveListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplayPlayingState::onStop);

}

std::shared_ptr<State<TapDisplay> > TapDisplayPlayingState::update() {
    if (stopped) {
        return std::make_shared<TapDisplayInitState>(subject);
    }
    return shared_from_this();
}

TapDisplayRecordingState::TapDisplayRecordingState(std::shared_ptr<TapDisplay> d): TapDisplayState(d){
    ofAddListener(TapRecorderEvent::PAUSE_RECORDING, this, &TapDisplayRecordingState::onPause);
    ofAddListener(TapRecorderEvent::RESET_RECORDING, this, &TapDisplayRecordingState::onStop);
}

void TapDisplayRecordingState::onStop(TapRecorderEvent &e) {
    stopped = true;
}

void TapDisplayRecordingState::onPause(TapRecorderEvent &e) {
    paused = true;
}

TapDisplayRecordingState::~TapDisplayRecordingState() {
    ofRemoveListener(TapRecorderEvent::PAUSE_RECORDING, this, &TapDisplayRecordingState::onPause);
    ofRemoveListener(TapRecorderEvent::RESET_RECORDING, this, &TapDisplayRecordingState::onStop);

}

std::shared_ptr<State<TapDisplay> > TapDisplayRecordingState::update() {
    if (stopped) {
        return std::make_shared<TapDisplayInitState>(subject);
    }
    return shared_from_this();
}
