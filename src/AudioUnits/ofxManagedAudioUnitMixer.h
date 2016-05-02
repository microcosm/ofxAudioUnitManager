#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

class ofxManagedAudioUnitMixer {

public:
    void setup(string _name);
    string getName();
    ofxAudioUnitMixer* getUnit();
protected:
    ofxAudioUnitMixer unit;
    string name;
};