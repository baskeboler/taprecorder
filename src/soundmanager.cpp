#include "soundmanager.h"

SoundManager::SoundManager(ScenePtr scene): scene{scene}
{

}

void SoundManager::init() {
    envelope = std::make_shared<CTEnvelope>(20, 140, 0.285, 100);
    frequency = std::make_shared<SmoothValue>();
    frequency->currentValue = frequency->targetValue = 110;
//    frequency->smoother = new ParameterSmoother(40);

    wave = std::make_shared<WTSawtooth>(frequency->currentValue);

//    ofSoundStreamSettings soundSettings;
//    soundSettings.bufferSize = 512;
//    soundSettings.setOutListener(this);
//    soundSettings.sampleRate = 48000;
//    soundSettings.numBuffers = 4;
//    soundSettings.numInputChannels = 0;
//    soundSettings.numOutputChannels = 2;
//    ofSoundStreamSetup(soundSettings);
    //        ofSoundStreamSetup(2, 0, 48000, 512,4);

    tapPlayer = std::make_shared<ofSoundPlayer>();
    tapPlayer->load("snare.wav");
    tapPlayer->setSpeed(2.0);

}

void SoundManager::update() {
//    auto now = ofGetCurrentTime().getAsMilliseconds();
//    if (now - last_tap > TAP_THRESHOLD) {
//        envelope->setGate(0);
//    }

}

void SoundManager::tap() {
//    auto now = ofGetCurrentTime().getAsMilliseconds();
//    last_tap = now;
//    envelope->setGate(1);
    tapPlayer->play();
}

void SoundManager::audioOut(ofSoundBuffer &buf) {


//    for(unsigned int i = 0; i < buf.size(); ++i) {
//        envelope->process();
//        wave->process();

//        float v = wave->getSample() * envelope->getValue();
//        buf[i * buf.getNumChannels() + 0] = v;
//        buf[i * buf.getNumChannels() + 1] = v;
//    }
}

SoundManager::~SoundManager() {
    ofLog() << "Destroying sound manager";
//    ofSoundStreamStop();
//    ofSoundStreamClose();
}
