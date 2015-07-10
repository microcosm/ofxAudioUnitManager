#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxManagedAudioUnit.h"

class Compressor : public ofxManagedAudioUnit {
    
public:
    void setup();
};