#pragma once
#include "ofMain.h"
#include "ofxAudioUnitChain.h"
#include "Compressor.h"
#include "UIHandler.h"

class ofxAudioUnitManager {
public:
    void setup();
    void add(ofxAudioUnitChain *chain, string name, ofColor color=ofColor::blue);
    void loadPresets(ofxAudioUnitChain *chain);
    void draw();
    void exit();
    void keyPressed(int key);
    void toggleDebugUI();
    void incrementSelectedChain();
    void decrementSelectedChain();
    vector<ofxAudioUnitChain*> allChains();

protected:
    void selectChain(int index);
    void selectChain(ofxAudioUnitChain *chain);
    void showSelectedChainUI();
    void showAllSynthUIs();
    void showAllUIs();
    void showMixerUI();
    
    Compressor compressor;
    UIHandler userInterface;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    vector<ofxAudioUnitChain*> chains;
    ofxAudioUnitChain* selectedChain;
    bool showDebugUI;
    int selectedChainIndex;
};