#include "ofApp.h"

void ofApp::setup(){
    manager.setup();
    manager.toggleDebugUI();
    manager.add(&chain1, "chain-one", ofColor::blue);
    manager.add(&chain2, "chain-two", ofColor::red);
    
    playing = false;
    note = 60;
    
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        chain1.midi()->sendNoteOn(1, note);
        chain2.midi()->sendNoteOn(1, note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.midi()->sendNoteOff(1, note);
        chain2.midi()->sendNoteOff(1, note);
    }
}

void ofApp::update(){
    manager.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    manager.draw();
}

void ofApp::exit() {
    manager.exit();
}

void ofApp::keyPressed(int key){
    if(key == ' ') {
        togglePlaying();
    } else if(key == '[') {
        togglePlaying();
        note--;
        togglePlaying();
    } else if(key == ']') {
        togglePlaying();
        note++;
        togglePlaying();
    } else {
        manager.keyPressed(key);
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}