#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    drawDarkOverlay = false;
    numUnmanagedInputs = 0;
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

void ofxAudioUnitManager::setupDark() {
    setup();
    drawDarkOverlay = true;
}

void ofxAudioUnitManager::onlyFocusOnCommand() {
    focusOnCommand = true;
    isFocused = false;
    userInterface.setFocus(isFocused);
}

aumAudioUnitChain& ofxAudioUnitManager::createChain(aumAudioUnitChain *chain, string name, aumManagedAudioUnitMixer* altMixer, ofColor color) {
    userInterface.addChain();
    chains.push_back(chain);
    name = name == "" ? "chain" + ofToString(chains.size()) : name;

    ofxAudioUnitMixer* targetMixer = altMixer == NULL ? &mixer : altMixer->getUnit();
    int mixerBusIndex = nextMixerBusIndex(targetMixer);
    targetMixer->setInputBusCount(mixerBusIndex + 1);
    chain->setup(name, targetMixer, &compressor, mixerBusIndex, color);

    selectChain(chains.size() - 1);
    return *chain;
}

void ofxAudioUnitManager::addUnmanagedUnit(ofxAudioUnit* unit){
    numUnmanagedInputs++;
    int mixerBusIndex = nextMixerBusIndex(&mixer);
    mixer.setInputBusCount(mixerBusIndex + 1);
    unit->connectTo(mixer, mixerBusIndex);
}

void ofxAudioUnitManager::loadPresets(aumAudioUnitChain *chain) {
    chain->loadPresets();
    selectChain(chain);
}

void ofxAudioUnitManager::draw(ofEventArgs& args) {
    if(ofGetFrameNum() == 0) {
        selectChain(0);
    }
    if(showDebugUI) {
        if(drawDarkOverlay){
            ofSetColor(ofColor::black, 180);
            ofFill();
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
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
        } else if(args.key == OF_KEY_DOWN) {
            selectedChain->presets()->increment();
        } else if(args.key == OF_KEY_UP) {
            selectedChain->presets()->decrement();
        } else if(args.key == OF_KEY_RIGHT) {
            incrementSelectedChain();
        } else if(args.key == OF_KEY_LEFT) {
            decrementSelectedChain();
        }
    }
}

void ofxAudioUnitManager::toggleDebugUI() {
    showDebugUI = !showDebugUI;
}

void ofxAudioUnitManager::enableDebugUI(bool show) {
    showDebugUI = show;
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

vector<aumAudioUnitChain*> ofxAudioUnitManager::allChains() {
    return chains;
}

aumAudioUnitChain* ofxAudioUnitManager::getChain(int chainId) {
    return chains.at(chainId);
}

void ofxAudioUnitManager::selectChain(int index) {
    for(int i = 0; i < chains.size(); i++) {
        i == index ? chains.at(i)->select() : chains.at(i)->deselect();
    }
    selectedChainIndex = index;
    selectedChain = chains.at(index);
}

void ofxAudioUnitManager::selectChain(aumAudioUnitChain *chain) {
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

int ofxAudioUnitManager::nextMixerBusIndex(ofxAudioUnitMixer* mixer) {
    if(mixersToBusCounts.find(mixer) == mixersToBusCounts.end()) {
        mixersToBusCounts[mixer] = 0;
    } else {
        mixersToBusCounts[mixer]++;
    }
    return mixersToBusCounts[mixer];
}
