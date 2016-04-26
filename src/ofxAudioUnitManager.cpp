#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    userInterface.setup();
    compressor.setup("Main Compressor", kAudioUnitType_Effect, kAudioUnitSubType_DynamicsProcessor);
    mixer.connectTo(*compressor.getUnit()).connectTo(output);
    output.start();
    focusOnCommand = false;
    isFocused = true;
    ofAddListener(ofEvents().draw, this, &ofxAudioUnitManager::draw);
    ofAddListener(ofEvents().exit, this, &ofxAudioUnitManager::exit);
    ofAddListener(ofEvents().keyPressed, this, &ofxAudioUnitManager::keyPressed);
}

void ofxAudioUnitManager::onlyFocusOnCommand() {
    focusOnCommand = true;
    isFocused = false;
    userInterface.setFocus(isFocused);
}

ofxAudioUnitChain& ofxAudioUnitManager::createChain(ofxAudioUnitChain *chain, string name, ofColor color) {
    int index = chains.size();
    if(name == "") {
        name = "chain" + ofToString(index + 1);
    }
    chain->setup(name, &mixer, &compressor, index, color);
    chains.push_back(chain);
    userInterface.addChain();
    mixer.setInputBusCount(index + 1);
    selectChain(index);
    return *chain;
}

void ofxAudioUnitManager::loadPresets(ofxAudioUnitChain *chain) {
    chain->loadPresets();
    selectChain(chain);
}

void ofxAudioUnitManager::draw(ofEventArgs& args) {
    if(ofGetFrameNum() == 0) {
        selectChain(0);
    }
    if(showDebugUI) {
        ofSetColor(ofColor::black, 180);
        ofFill();
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        userInterface.drawChains(chains);
        userInterface.drawControls();
    }
}

void ofxAudioUnitManager::exit(ofEventArgs& args) {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->exit();
    }
}

void ofxAudioUnitManager::keyPressed(ofKeyEventArgs& args) {
    //Toggle focus on command
    if(focusOnCommand && args.key == 4352) {
        isFocused = !isFocused;
        userInterface.setFocus(isFocused);
    }

    if((focusOnCommand && isFocused) || !focusOnCommand) {
        if (args.key == 'u') {
            showSelectedChainUI();
        } else if (args.key == 'A') {
            showAllUIs();
        } else if (args.key == 'a') {
            showAllSynthUIs();
        } else if (args.key == 'm') {
            showMixerUI();
            showCompressorUI();
        } else if(args.key == 'v') {
            toggleDebugUI();
        } else if(args.key == 'S') {
            selectedChain->presets()->saveOverwrite();
        } else if(args.key == 's') {
            selectedChain->presets()->saveNew();
        } else if(args.key == 'r') {
            selectedChain->presets()->rename();
        } else if(args.key == 't') {
            selectedChain->presets()->trash();
        } else if(args.key == 359) {
            selectedChain->presets()->increment();
        } else if(args.key == 357) {
            selectedChain->presets()->decrement();
        } else if(args.key == 358) {
            incrementSelectedChain();
        } else if(args.key == 356) {
            decrementSelectedChain();
        }
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

ofxAudioUnitMixer* ofxAudioUnitManager::getMixer() {
    return &mixer;
}

vector<ofxAudioUnitChain*> ofxAudioUnitManager::allChains() {
    return chains;
}

ofxAudioUnitChain* ofxAudioUnitManager::getChain(int chainId) {
    return chains.at(chainId);
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

void ofxAudioUnitManager::showCompressorUI() {
    compressor.getUnit()->showUI("Compressor", ofGetScreenWidth() * 0.25, ofGetScreenHeight() * 0.5);
}