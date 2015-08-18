#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    userInterface.setup();
    compressor.setup();
    mixer.connectTo(*compressor.getUnit()).connectTo(output);
    output.start();
}

void ofxAudioUnitManager::add(ofxAudioUnitChain *chain, string name, ofColor color) {
    int index = chains.size();
    if(name == "") {
        name = "chain" + ofToString(index + 1);
    }
    chain->setup(name, &mixer, index, color);
    chains.push_back(chain);
    userInterface.addChain();
    mixer.setInputBusCount(index + 1);
    selectChain(index);
}

void ofxAudioUnitManager::loadPresets(ofxAudioUnitChain *chain) {
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
        showSelectedChainUI();
    } else if (key == 'a') {
        showAllUIs();
    } else if (key == 'A') {
        showAllSynthUIs();
    } else if (key == 'm') {
        showMixerUI();
    } else if(key == 'v') {
        toggleDebugUI();
    } else if(key == 's') {
        selectedChain->presets()->saveOverwrite();
    } else if(key == 'S') {
        selectedChain->presets()->saveNew();
    } else if(key == 'r') {
        selectedChain->presets()->rename();
    } else if(key == 't') {
        selectedChain->presets()->trash();
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

vector<ofxAudioUnitChain*> ofxAudioUnitManager::allChains() {
    return chains;
}

void ofxAudioUnitManager::selectChain(int index) {
    for(int i = 0; i < chains.size(); i++) {
        i == index ? chains.at(i)->select() : chains.at(i)->deselect();
    }
    selectedChainIndex = index;
    selectedChain = chains.at(index);
}

void ofxAudioUnitManager::selectChain(ofxAudioUnitChain *chain) {
    for(int i = 0; i < chains.size(); i++) {
        if(chains.at(i) == chain) {
            selectedChainIndex = i;
        }
    }
    chain->select();
    selectedChain = chain;
}

void ofxAudioUnitManager::showSelectedChainUI() {
    selectedChain->showUI(selectedChainIndex, chains.size());
}

void ofxAudioUnitManager::showAllSynthUIs() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->showSynthUI(i, chains.size());
    }
}

void ofxAudioUnitManager::showAllUIs() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->showUI(i, chains.size());
    }
}

void ofxAudioUnitManager::showMixerUI() {
    mixer.showUI("Mixer", ofGetScreenWidth() * 0.25, ofGetScreenHeight() * 0.25);
}