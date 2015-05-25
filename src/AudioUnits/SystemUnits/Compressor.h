#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "AudioUnitBase.h"

class Compressor : public AudioUnitBase {
    
public:
    void setup();
};