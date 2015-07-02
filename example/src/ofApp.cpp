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
    chain1.link(&noiseMaker1)
          .to(&filter1)
          .to(&reverb1)
          .toMixer();
    
    //3. Read presets from disk (if any)
    manager.loadPresets(&chain1);
    //--------------
    
    //Now repeat for every chain you want to create
    manager.add(&chain2, "tal-two", ofColor::red);

    chain2.link(&noiseMaker2)       //If you want to use the same type of
          .to(&filter2, "filter2")  //unit more than once in a chain, you
          .to(&filter3, "filter3")  //should disambiguate by adding a name.
          .to(&reverb2)             //This allows you to keep using the same
          .toMixer();               //presets even if you later switch the
                                    //unit order.
    manager.loadPresets(&chain2);

    //Use ofxBpm to regularly schedule MIDI events
    ofAddListener(bpm.beatEvent, this, &ofApp::play);
    bpm.start();
}

void ofApp::play(void){
    if(playing) {
        chain1.sendMidiOn(note);
        chain2.sendMidiOn(note);
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        chain1.sendMidiOff(note);
        chain2.sendMidiOff(note);
    }
}

void ofApp::update(){
    
}

void ofApp::draw(){
    //When you use this in your projects, you may be drawing
    //your own stuff, like this:
    /*ofBackground(ofColor::black);
    ofSetLineWidth(30);
    ofSetColor(ofColor::white, 40);
    int size = 4000;

    ofRotateZ(45);
    for(int i = -size; i < size; i+=50) {
        ofLine(i, -size, i, size);
    }
    ofRotateZ(-90);
    for(int i = -size; i < size; i+=50) {
        ofLine(i, -size, i, size);
    }
    ofRotateZ(45);*/

    //And then you will always draw the manager last
    //(It can be hidden at runtime by pressing 'v')
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