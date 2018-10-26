#ifndef TAPRECORDEREVENTARGS_H
#define TAPRECORDEREVENTARGS_H

#include "ofMain.h"

class TapRecorderEvent: public ofEventArgs
{
public:

    static std::shared_ptr<TapRecorderEvent> getInstance();

    void startRecording() {
        ofNotifyEvent(START_RECORDING, *this);
    }

    void pauseRecording() {
        ofNotifyEvent(PAUSE_RECORDING, *this);
    }
    void resetRecording() {
        ofNotifyEvent(RESET_RECORDING, *this);
    }

    void startPlaying() {
        ofNotifyEvent(START_PLAYER, *this);
    }

    void pausePlaying() {
        ofNotifyEvent(PAUSE_PLAYER, *this);

    }
    void resetPlaying() {
        ofNotifyEvent(RESET_PLAYER, *this);
    }

    void togglePause() {
        ofNotifyEvent(TOGGLE_PAUSE, *this);
    }
    static ofEvent<TapRecorderEvent> START_RECORDING;
    static ofEvent<TapRecorderEvent> PAUSE_RECORDING;
    static ofEvent<TapRecorderEvent> RESET_RECORDING;

    static ofEvent<TapRecorderEvent> START_PLAYER;
    static ofEvent<TapRecorderEvent> PAUSE_PLAYER;
    static ofEvent<TapRecorderEvent> RESET_PLAYER;

    static ofEvent<TapRecorderEvent> TOGGLE_PAUSE;
private:
    static std::shared_ptr<TapRecorderEvent> instance;
    TapRecorderEvent() = default;
};



#endif // TAPRECORDEREVENTARGS_H
