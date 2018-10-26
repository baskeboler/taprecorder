#include "taprecorderevent.h"


std::shared_ptr<TapRecorderEvent> TapRecorderEvent::instance = nullptr;


ofEvent<TapRecorderEvent> TapRecorderEvent::START_RECORDING;
ofEvent<TapRecorderEvent> TapRecorderEvent::PAUSE_RECORDING;
ofEvent<TapRecorderEvent> TapRecorderEvent::RESET_RECORDING;

ofEvent<TapRecorderEvent> TapRecorderEvent::START_PLAYER;
ofEvent<TapRecorderEvent> TapRecorderEvent::PAUSE_PLAYER;
ofEvent<TapRecorderEvent> TapRecorderEvent::RESET_PLAYER;

ofEvent<TapRecorderEvent> TapRecorderEvent::TOGGLE_PAUSE;
std::shared_ptr<TapRecorderEvent> TapRecorderEvent::getInstance()
{
    if (!instance) {
        instance.reset(new TapRecorderEvent);
    }
    return instance;
}
