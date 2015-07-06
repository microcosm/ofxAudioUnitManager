#pragma once
#include "ofMain.h"
#include "AudioUnitBase.h"

class PresetsHandler{

public:
    void setup(string synthName);
    void load(int index);
    void add(AudioUnitBase* unit, string unitName);
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
    void loadPresetsInChainOrder(string presetName);
    vector<ofFile> dirContents(string path, string extensions);
    void clearPresets();
    string path(string presetName);
    string filename(AudioUnitBase* unit, string unitName);
    string trim(string presetName);
    void ensureDirectories();
    bool validateRename(string newPresetName);

    vector<string> presetNames;
    vector<AudioUnitBase*> units;
    vector<string> unitNames;
    vector< vector<ofFile> > presets;

    string chainName, storageDir;
    int currentPreset;
    bool selected;

    ofDirectory dir;
    string anyExtension, presetExtension;
};