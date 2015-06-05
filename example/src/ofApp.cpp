#include "ofApp.h"

void ofApp::setup(){
    playing = false;
    note = 60;

    //Setup the manager, and since this is a demo, let's start
    //with the debug UI toggled on
    manager.setup();
    manager.toggleDebugUI();

    //For each chain:
    //--------------
    //1. Have the manager init the chain with a name & color
    manager.add(&chain1, "tal-one", ofColor::blue);
    
    //2. Load units in order
    chain1.load(&noiseMaker1)
          .load(&filter1)
          .load(&reverb1)
          .sendOut();
    
    //3. Read presets from disk (if any)
    manager.loadPresets(&chain1);
    //--------------
    
    //Now repeat for every chain you want to create
    manager.add(&chain2, "tal-two", ofColor::red);

    chain2.load(&noiseMaker2)
          .load(&filter2)
          .load(&reverb2)
          .sendOut();

    manager.loadPresets(&chain2);

    //Use ofxBpm to regularly schedule MIDI events
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