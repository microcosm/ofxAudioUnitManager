#pragma once
#include "ofMain.h"
#include "ofxAudioUnitChain.h"
#include "ofxBpm.h"
#include "UIHandler.h"
#include "ofxAudioUnitParams.h"

class ofxAudioUnitManager {
public:
    void setup();
    void onlyFocusOnCommand();
    ofxAudioUnitChain& createChain(ofxAudioUnitChain *chain, string name="", ofColor color=ofColor::blue);
    void loadPresets(ofxAudioUnitChain *chain);
    void draw();
    void exit();
    void keyPressed(int key);
    void toggleDebugUI();
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
    
    UIHandler userInterface;
    ofxAudioUnitMixer mixer;
    ofxManagedAudioUnit compressor;
    ofxAudioUnitOutput output;
    vector<ofxAudioUnitChain*> chains;
    ofxAudioUnitChain* selectedChain;
    bool showDebugUI, focusOnCommand, isFocused;
    int selectedChainIndex;
};