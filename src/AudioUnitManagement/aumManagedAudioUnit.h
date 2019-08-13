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
    void setup(string _unitName, OSType _osType, OSType _osSubType, OSType _osManufacturer=kAudioUnitManufacturer_Apple, string _className="");
    void update(ofEventArgs& args);
    virtual void update() = 0;

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
protected:
    string stringify(OSType _osType, OSType _osSubType, OSType _osManufacturer);
    string stringify(OSType code);
    OSType osType, osSubType, osManufacturer;
    ofxAudioUnit unit;
    AudioUnitType type;
    aumParams audioUnitParams;
    string className, unitName, unitSlug;
    int x, y;
};
