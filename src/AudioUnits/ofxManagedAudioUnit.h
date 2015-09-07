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
    void setup(string _unitName, OSType type, OSType subType, OSType manufacturer=kAudioUnitManufacturer_Apple, string _className="");
    void setup(OSType type, OSType subType, OSType manufacturer=kAudioUnitManufacturer_Apple, string _className="");
    void setup(OSType type, OSType subType, OSType manufacturer, AudioUnitType _type, string _className="");
    void showUI(string chainname, int chainIndex, int numChains, int unitIndex, int numUnits);
    void setUnitName(string name);
    void set(int param, float value);
    void set(int param1, int param2, ofVec2f value);
    void set(int param1, int param2, int param3, ofVec3f value);
    ofxAudioUnit* getUnit();
    AudioUnitType getType();
    bool isSynth();
protected:
    string stringify(OSType type, OSType subType, OSType manufacturer);
    string stringify(OSType code);
    ofxAudioUnit unit;
    AudioUnitType type;
    string className, unitName;
    int x, y;
};