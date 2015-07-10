#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxManagedAudioUnit.h"

class LowPassFilter : public ofxManagedAudioUnit {
    
public:
    void setup();
};