#pragma once
#include "ofMain.h"
#include "AudioUnitBase.h"

class Delay : public AudioUnitBase {
    
public:
    void setup();
};

const static int DelayTime = 0; //[0 : 4410 : 0]