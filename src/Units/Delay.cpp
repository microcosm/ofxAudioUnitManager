#include "Delay.h"

void Delay::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_SampleDelay);
    
    BaseUnit::setup();
}