#pragma once
#include "ofMain.h"
#include "aumAudioUnitChain.h"
#include "aumUnit_Generic.h"
#include "aumManagedAudioUnitMixer.h"
#include "ofxBpm.h"
#include "aumUserInterface.h"
#include "aumParams.h"

class ofxAudioUnitManager {
public:
    void setup();
    void setupDark();
    void onlyFocusOnCommand();
    aumAudioUnitChain& createChain(aumAudioUnitChain *chain, string name="", aumManagedAudioUnitMixer* altMixer=NULL, ofColor color=ofColor::blue);
    void addUnmanagedUnit(ofxAudioUnit* unit);
    void loadPresets(aumAudioUnitChain* chain);
    void draw(ofEventArgs& args);
    void exit(ofEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void toggleDebugUI();
    void enableDebugUI(bool show);
    void incrementSelectedChain();
    void decrementSelectedChain();
    ofxAudioUnitMixer* getMixer();
    vector<aumAudioUnitChain*> allChains();
    aumAudioUnitChain* getChain(int chainId);
    ofxBpm bpm;

protected:
    void selectChain(int index);
    void selectChain(aumAudioUnitChain *chain);
    void showSelectedChainUI();
    void showAllSynthUIs();
    void showAllUIs();
    void showMixerUI();
    void showCompressorUI();
    int nextMixerBusIndex(ofxAudioUnitMixer* mixer);

    aumUserInterface userInterface;
    ofxAudioUnitMixer mixer;
    aumUnit_Generic compressor;
    ofxAudioUnitOutput output;
    vector<aumAudioUnitChain*> chains;
    aumAudioUnitChain* selectedChain;
    bool showDebugUI, drawDarkOverlay, focusOnCommand, isFocused;
    int selectedChainIndex, numUnmanagedInputs;
    map<ofxAudioUnitMixer*, int> mixersToBusCounts;
};
