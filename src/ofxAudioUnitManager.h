#pragma once
#include "ofMain.h"
#include "ofxAudioUnitChain.h"
#include "ofxManagedAudioUnitMixer.h"
#include "ofxBpm.h"
#include "UIHandler.h"
#include "ofxAudioUnitParams.h"

class ofxAudioUnitManager {
public:
    void setup();
    void onlyFocusOnCommand();
    ofxAudioUnitChain& createChain(ofxAudioUnitChain *chain, string name="", ofxManagedAudioUnitMixer* altMixer=NULL, ofColor color=ofColor::blue);
    void addUnmanagedUnit(ofxAudioUnit* unit);
    void loadPresets(ofxAudioUnitChain* chain);
    void draw(ofEventArgs& args);
    void exit(ofEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void toggleDebugUI();
    void enableDebugUI(bool show);
    void incrementSelectedChain();
    void decrementSelectedChain();
    ofxAudioUnitMixer* getMixer();
    vector<ofxAudioUnitChain*> allChains();
    ofxAudioUnitChain* getChain(int chainId);
    ofxBpm bpm;

protected:
    void selectChain(int index);
    void selectChain(ofxAudioUnitChain *chain);
    void showSelectedChainUI();
    void showAllSynthUIs();
    void showAllUIs();
    void showMixerUI();
    void showCompressorUI();
    int nextMixerBusIndex(ofxAudioUnitMixer* mixer);

    UIHandler userInterface;
    ofxAudioUnitMixer mixer;
    ofxManagedAudioUnit compressor;
    ofxAudioUnitOutput output;
    vector<ofxAudioUnitChain*> chains;
    ofxAudioUnitChain* selectedChain;
    bool showDebugUI, focusOnCommand, isFocused;
    int selectedChainIndex, numUnmanagedInputs;
    map<ofxAudioUnitMixer*, int> mixersToBusCounts;
};
