#include "ofApp.h"

void ofApp::setup(){
    manager.setup();

    //Since this is a demo, let's start with the UI open
    manager.toggleDebugUI();
    
    //Have the manager init the chain
    manager.add(&chain1, "tal-one", ofColor::blue);
    
    //Load units in order
    chain1.load(&noiseMaker1);
    chain1.load(&filter1);
    chain1.load(&reverb1);
    chain1.sendOut();
    
    //Read presets from disk
    chain1.loadPresets();
    
    //Have the manager init the chain
    manager.add(&chain2, "tal-two", ofColor::red);
    
    //Load units in order
    chain2.load(&noiseMaker2);
    chain2.load(&filter2);
    chain2.load(&reverb2);
    chain2.sendOut();
    
    //Read presets from disk
    chain2.loadPresets();

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