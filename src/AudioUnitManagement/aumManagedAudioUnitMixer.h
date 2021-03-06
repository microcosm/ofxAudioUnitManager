#pragma once
#include "ofMain.h"

#ifdef __APPLE__
#include "ofxAudioUnit.h"
#endif

class aumManagedAudioUnitMixer {

public:
    void setup(string _name);
    string getName();
    ofxAudioUnitMixer* getUnit();
protected:
    ofxAudioUnitMixer unit;
    string name;
};
