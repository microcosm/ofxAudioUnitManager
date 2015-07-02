#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    userInterface.setup();
    compressor.setup();
    mixer.connectTo(*compressor.getUnit()).connectTo(output);
    output.start();
}

void ofxAudioUnitManager::add(AudioUnitChain *chain, string name, ofColor color) {
    int index = chains.size();
    chain->setup(name, &mixer, index, color);
    chains.push_back(chain);
    mixer.setInputBusCount(index + 1);
    selectChain(index);
}

void ofxAudioUnitManager::loadPresets(AudioUnitChain *chain) {
    chain->loadPresets();
    selectChain(chain);
}

void ofxAudioUnitManager::draw() {
    if(showDebugUI) {
        ofSetColor(ofColor::black, 180);
        ofFill();
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        userInterface.drawChains(chains);
        userInterface.drawControls();
    }
}

void ofxAudioUnitManager::exit() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->exit();
    }
}

void ofxAudioUnitManager::keyPressed(int key) {
    if (key == 'u') {
        selectedChain->showUI(selectedChainIndex, chains.size());
    } else if(key == 'v') {
        toggleDebugUI();
    } else if(key == 's') {
        selectedChain->presets()->save();
    } else if(key == 'r') {
        selectedChain->presets()->rename();
    } else if(key == 'd') {
        selectedChain->presets()->remove();
    } else if(key == 359) {
        selectedChain->presets()->increment();
    } else if(key == 357) {
        selectedChain->presets()->decrement();
    } else if(key == 358) {
        incrementSelectedChain();
    } else if(key == 356) {
        decrementSelectedChain();
    }
}

void ofxAudioUnitManager::toggleDebugUI() {
    showDebugUI = !showDebugUI;
}

void ofxAudioUnitManager::incrementSelectedChain() {
    int index = selectedChainIndex + 1 >= chains.size() ? 0 : selectedChainIndex + 1;
    selectChain(index);
}

void ofxAudioUnitManager::decrementSelectedChain() {
    int index = selectedChainIndex - 1 < 0 ? chains.size() - 1 : selectedChainIndex - 1;
    selectChain(index);
}

void ofxAudioUnitManager::selectChain(int index) {
    for(int i = 0; i < chains.size(); i++) {
        i == index ? chains.at(i)->select() : chains.at(i)->deselect();
    }
    selectedChainIndex = index;
    selectedChain = chains.at(index);
}

void ofxAudioUnitManager::selectChain(AudioUnitChain *chain) {
    for(int i = 0; i < chains.size(); i++) {
        if(chains.at(i) == chain) {
            selectedChainIndex = i;
        }
    }
    chain->select();
    selectedChain = chain;
}