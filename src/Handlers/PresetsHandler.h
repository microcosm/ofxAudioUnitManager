#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

class PresetsHandler{
    
public:
    void setup(string synthName);
    void load(int index);
    void add(ofxAudioUnit* unit);
    void save();
    void rename();
    void remove();
    void increment();
    void decrement();
    void select();
    void deselect();
    int currentIndex();
    string report();
    
protected:
    int indexOf(string presetName);
    void ensureValidIndex();
    void readFromDisk();
    vector<ofFile> dirContents(string path, string extensions);
    void clearPresets();

    ofxAudioUnit* synth;
    string chainName;
    vector<ofxAudioUnit*> units;
    vector< vector<ofFile> > presets;
    vector<string> presetNames;
    ofDirectory dir;
    int currentPreset;
    bool selected;
    string anyExtension, presetExtension;
};