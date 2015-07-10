#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class ofxManagedAudioUnit {

public:
    string getClassName();
    virtual void setup();
    void showUI(string chainname, int chainIndex, int numChains, int unitIndex, int numUnits);
    void setUnitName(string name);
    void set(int param, float value);
    void set(int param1, int param2, ofVec2f value);
    void set(int param1, int param2, int param3, ofVec3f value);
    ofxAudioUnit* getUnit();
    AudioUnitType getType();
    bool isSynth();
protected:
    ofxAudioUnit unit;
    AudioUnitType type;
    string className, unitName;
    int x, y;
};