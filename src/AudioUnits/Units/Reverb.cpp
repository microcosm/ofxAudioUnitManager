#include "Reverb.h"

void Reverb::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_MatrixReverb);

    type = AU_TYPE_UNIT;
    className = "Reverb";
    AudioUnitBase::setup();
}