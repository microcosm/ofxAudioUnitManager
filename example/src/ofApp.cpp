#include "ofApp.h"

void ofApp::setup(){
    manager.setup();
    manager.add(&leftChain, "left-chain", ofColor::blue);
    manager.add(&rightChain, "right-chain", ofColor::red);
    
    playing = showDebugUI = false;
    note = 60;
    
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        leftChain.sendMidiOn(note);
        rightChain.sendMidiOn(note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        leftChain.sendMidiOff(note);
        rightChain.sendMidiOff(note);
    }
}

void ofApp::toggleDebugUI() {
    showDebugUI = !showDebugUI;
}

void ofApp::update(){
    leftChain.update();
    rightChain.update();
}

void ofApp::draw(){
    ofBackground(0);
    leftChain.draw();
    rightChain.draw();
}

void ofApp::exit() {
    leftChain.exit();
    rightChain.exit();
}

void ofApp::keyPressed(int key){
    AlchemyChain* selectedChain;
    selectedChain = leftChain.isSelected() ? &leftChain : &rightChain;
    
    if (key == 'u') {
        selectedChain->showAlchemyUI();
    } else if(key == 'r') {
        selectedChain->showReverbUI();
    } else if(key == 'f') {
        selectedChain->showFilterUI();
    } else if(key == 'd') {
        toggleDebugUI();
    } else if(key == 's') {
        selectedChain->savePresets();
    } else if(key == ']') {
        togglePlaying();
        note--;
        togglePlaying();
    } else if(key == '[') {
        togglePlaying();
        note++;
        togglePlaying();
    } else if(key == 359) {
        selectedChain->incrementPreset();
    } else if(key == 357) {
        selectedChain->decrementPreset();
    } else if(key == ' ') {
        togglePlaying();
    } else if(key == 358 || key == 356) {
        leftChain.toggleSelected();
        rightChain.toggleSelected();
    } else if(key == 13) {
        ofToggleFullscreen();
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