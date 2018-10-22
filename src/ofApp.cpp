#include "ofApp.h"
#include "ofxATK.hpp"

//--------------------------------------------------------------
void ofApp::setup(){

    scene = std::make_shared<Scene>();
    scene->init_state();
    setupGui();

    soundManager = std::make_shared<SoundManager>(scene);
    soundManager->init();
}

void ofApp::setupGui() {
    gui = std::make_shared<ofxDatGui>(ofxDatGuiAnchor::TOP_RIGHT);

    gui->addHeader("tap recorder");
    gui->addLabel("recorder controls");

    gui->addButton("exit")->onButtonEvent([&](ofxDatGuiButtonEvent evt) {
        ofExit();
    });

    gui->addFooter();
}
//--------------------------------------------------------------
void ofApp::update(){
    scene->update();
    soundManager->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    scene->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'r') {
        scene->resetTaps();
    } else if (key == 's') {
        scene->stopRecording();
        scene->stopPlaying();
    } else if (key == 'p') {
        scene->play();
    }else {
        scene->onKeyTapped();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    soundManager->tap();
    scene->onMousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    scene->onMouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
