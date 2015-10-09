#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitParams.h"

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class ofxManagedAudioUnit {

public:
    void setup(string _unitName, ofxAudioUnitDevice device, string _className="");
    void setup(string _unitName, OSType type, OSType subType, OSType manufacturer=kAudioUnitManufacturer_Apple, string _className="");
    void showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits);
    void set(int param, float value);
    void set(int param1, int param2, ofVec2f value);
    void set(int param1, int param2, int param3, ofVec3f value);
    ofxAudioUnit* getUnit();
    AudioUnitType getType();
    string getUnitName();
    string getUnitSlug();
    string getClassName();
    bool isSynth();
    void printParamsAsConstants(string unitPrefix);
protected:
    string stringify(OSType type, OSType subType, OSType manufacturer);
    string stringify(OSType code);
    ofxAudioUnit unit;
    AudioUnitType type;
    ofxAudioUnitParams audioUnitParams;
    string className, unitName, unitSlug;
    int x, y;
    int unnamedCount;
};