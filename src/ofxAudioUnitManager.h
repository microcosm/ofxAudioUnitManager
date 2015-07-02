#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "Compressor.h"
#include "UIHandler.h"

class ofxAudioUnitManager {
public:
    void setup();
    void add(AudioUnitChain *chain, string name, ofColor color);
    void loadPresets(AudioUnitChain *chain);
    void draw();
    void exit();
    void keyPressed(int key);
    void toggleDebugUI();
    void incrementSelectedChain();
    void decrementSelectedChain();

protected:
    void selectChain(int index);
    void selectChain(AudioUnitChain *chain);
    void showSelectedChainUI();
    void showAllUIs();
    
    Compressor compressor;
    UIHandler userInterface;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    vector<AudioUnitChain*> chains;
    AudioUnitChain* selectedChain;
    bool showDebugUI;
    int selectedChainIndex;
};