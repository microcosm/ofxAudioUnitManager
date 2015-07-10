#pragma once
#include "ofMain.h"
#include "ofxManagedAudioUnit.h"

class PresetsHandler{

public:
    void setup(string synthName);
    void load(int index);
    void add(ofxManagedAudioUnit* unit, string unitName);
    void saveNew();
    void saveOverwrite();
    void rename();
    void trash();
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
    string newTrashPath(string presetName);
    string filename(ofxManagedAudioUnit* unit, string unitName);
    string trim(string presetName);
    void ensureDirectories();
    bool validateName(string newPresetName, int alertDialogException=-1);
    void save(string presetName);

    vector<string> presetNames;
    vector<ofxManagedAudioUnit*> units;
    vector<string> unitNames;
    vector< vector<ofFile> > presets;

    string chainName, storageDir, trashDir;
    int currentPreset, lastSaved, lastSaveTimer, lastSaveTimeout;
    bool selected;

    ofDirectory dir;
    string anyExtension, presetExtension;
};