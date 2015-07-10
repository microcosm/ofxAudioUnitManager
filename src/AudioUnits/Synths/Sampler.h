#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxManagedAudioUnit.h"

class Sampler : public ofxManagedAudioUnit {

public:
    void setup();
};