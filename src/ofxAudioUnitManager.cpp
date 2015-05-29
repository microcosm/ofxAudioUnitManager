#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    userInterface.setup();
    compressor.setup();
    mixer.connectTo(*compressor.get()).connectTo(output);
    output.start();
}

void ofxAudioUnitManager::add(AudioUnitChain *chain, string name, ofColor color) {
    int index = chains.size();
    chain->setup(name, &mixer, index, color);
    chains.push_back(chain);
    mixer.setInputBusCount(index + 1);
    selectChain(index);
}

void ofxAudioUnitManager::update() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->update();
    }
}

void ofxAudioUnitManager::draw() {
    if(showDebugUI) {
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
        selectedChain->showUI();
    } else if(key == 'v') {
        toggleDebugUI();
    } else if(key == 's') {
        selectedChain->savePresets();
    } else if(key == 'd') {
        selectedChain->deletePreset();
    } else if(key == 359) {
        selectedChain->incrementPreset();
    } else if(key == 357) {
        selectedChain->decrementPreset();
    } else if(key == 358) {
        incrementSelected();
    } else if(key == 356) {
        decrementSelected();
    }
}

void ofxAudioUnitManager::toggleDebugUI() {
    showDebugUI = !showDebugUI;
}

void ofxAudioUnitManager::incrementSelected() {
    int index = selectedChainIndex + 1 >= chains.size() ? 0 : selectedChainIndex + 1;
    selectChain(index);
}

void ofxAudioUnitManager::decrementSelected() {
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