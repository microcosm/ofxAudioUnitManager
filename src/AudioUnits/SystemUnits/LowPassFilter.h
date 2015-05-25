#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "AudioUnitBase.h"

class LowPassFilter : public AudioUnitBase {
    
public:
    void setup();
};