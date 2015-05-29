#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class AudioUnitBase {

public:
    virtual void setup();
    void showUI();
    void setParameter(int param, float value);
    void setParameters(int param1, int param2, ofVec2f value);
    ofxAudioUnit* get();
    AudioUnitType getType();
protected:
    ofxAudioUnit unit;
    AudioUnitType type;
};