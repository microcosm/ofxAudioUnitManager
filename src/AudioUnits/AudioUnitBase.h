#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

enum AudioUnitType {
    AU_TYPE_SYNTH,
    AU_TYPE_UNIT
};

class AudioUnitBase {

public:
    string getID();
    string getName();
    void setID(string _ID);
    virtual void setup();
    void showUI();
    void setParameter(int param, float value);
    void setParameters(int param1, int param2, ofVec2f value);
    ofxAudioUnit* get();
    AudioUnitType getType();
protected:
    string generateID();
    ofxAudioUnit unit;
    AudioUnitType type;
    string ID, name;
};