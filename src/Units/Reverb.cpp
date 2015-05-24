#include "Reverb.h"

void Reverb::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_MatrixReverb);
    
    setParameter(kReverbParam_SmallLargeMix, 30);
    
    BaseUnit::setup();
}