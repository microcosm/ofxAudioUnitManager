#pragma once
#include "ofMain.h"
#include "aumParams.h"

#ifdef __APPLE__
#include "ofxAudioUnit.h"
#endif

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class aumManagedAudioUnit {

public:
    void setup(string _unitName, aumAudioUnitDevice device, string _className="");
    void setup(string _unitName, OSType type, OSType subType, OSType manufacturer=kAudioUnitManufacturer_Apple, string _className="");
    void showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits);
    AudioUnitParameterValue get(int param);
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
    aumParams audioUnitParams;
    string className, unitName, unitSlug;
    int x, y;
    int unnamedCount;
};
