#pragma once
#include "ofMain.h"
#include "aumManagedAudioUnit.h"

class aumPresets{

public:
    void setup(string _chainName, ofxAudioUnitMixer* _mixer, aumManagedAudioUnit* _compressor);
    void load(int index);
    void add(aumManagedAudioUnit* unit);
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
    string filename(string unitSlug);
    string trim(string presetName);
    void ensureDirectories();
    bool validateName(string newPresetName, int alertDialogException=-1);
    void save(string presetName);
    void saveMasterUnits();
    void loadMasterUnits();

    vector<string> presetNames;
    vector<aumManagedAudioUnit*> units;
    vector<string> unitSlugs;
    vector< vector<ofFile> > presets;
    ofxAudioUnitMixer* mixer;
    aumManagedAudioUnit* compressor;

    string chainName, storageDir, storagePath, trashDir, mixerName;
    int currentPreset, lastSaved, lastSaveTimer, lastSaveTimeout;
    bool selected;

    ofDirectory dir;
    string anyExtension, presetExtension;
};
