#include "ofApp.h"

void ofApp::setup(){
    playing = false;
    on = true;
    note = 60;

    //Setup the manager, and since this is a demo, let's start
    //with the debug UI toggled on
    manager.setup();
    manager.toggleDebugUI();

    //For each chain:
    //--------------
    //1. Setup some units
    mySynth.setup("My Synth", 'aumu', 'ncut', 'TOGU');
    myFilter.setup("My Filter", kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    myReverb.setup("My Reverb", kAudioUnitType_Effect, kAudioUnitSubType_MatrixReverb);
    mySynth.printParamChanges();

    //2. Have the manager init the chain with a name
    manager.createChain(&myChain)
           .link(&mySynth)
           .to(&myFilter)
           .to(&myReverb)
           .toMixer();

    //That's it!
    
    //Now repeat for every chain you want to create
    noiseMaker2.setup("Noise 2", 'aumu', 'ncut', 'TOGU');
    filter2.setup("Filter 2", kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    filter3.setup("Filter 3", kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    reverb2.setup("Reverb 2", kAudioUnitType_Effect, kAudioUnitSubType_MatrixReverb);

    manager.createChain(&chain2)
           .link(&noiseMaker2)
           .to(&filter2)   //Note you can have two units of
           .to(&filter3)   //the same type in the same chain
           .to(&reverb2)
           .toMixer();

    //Use ofxBpm to regularly schedule MIDI events
    ofAddListener(manager.bpm.beatEvent, this, &ofApp::play);
    manager.bpm.start();
}

void ofApp::play(void){
    if(playing) {
        if(on) {
            myChain.sendMidiOn(note);
            on = false;
        } else {
            chain2.sendMidiOn(note);
            on = true;
        }
    }
}

void ofApp::togglePlaying() {
    playing = !playing;
    if(!playing) {
        myChain.sendMidiOff(note);
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
