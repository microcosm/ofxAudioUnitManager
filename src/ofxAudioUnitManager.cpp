#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    //playing = false;
    //showDebugUI = false;

    compressor.setup();
    mixer.connectTo(*compressor.get()).connectTo(output);
    output.start();
}

void ofxAudioUnitManager::add(BaseChain *chain, string name, ofColor color) {
    chains.push_back(chain);
    mixer.setInputBusCount(chains.size());
    chain->setup(name, &mixer, chains.size() - 1, color);
    chain->select();
}

void ofxAudioUnitManager::update() {

}

void ofxAudioUnitManager::draw() {

}