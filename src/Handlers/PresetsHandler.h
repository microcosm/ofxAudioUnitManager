#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

class PresetsHandler{
    
public:
    void setup(string synthName, ofxAudioUnit* synth);
    void load(int index);
    void save();
    void remove();
    void increment();
    void decrement();
    void select();
    void deselect();
    void readFromDisk();
    int currentIndex();
    string report();
    
protected:
    int indexOf(string presetName);
    ofxAudioUnit* synth;
    string synthName;
    vector<ofFile> presets;
    int currentPreset;
    bool selected;
};