#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class AudioUnitBase {

public:
    string getClassName();
    virtual void setup();
    void showUI();
    void set(int param, float value);
    void set(int param1, int param2, ofVec2f value);
    void set(int param1, int param2, int param3, ofVec3f value);
    ofxAudioUnit* get();
    AudioUnitType getType();
protected:
    ofxAudioUnit unit;
    AudioUnitType type;
    string className;
};