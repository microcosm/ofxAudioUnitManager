#include "BaseUnit.h"

void BaseUnit::setup() {}

void BaseUnit::showUI() {
    unit.showUI();
}

void BaseUnit::setParameter(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void BaseUnit::setParameters(int param1, int param2, ofVec2f value) {
    setParameter(param1, value.x);
    setParameter(param2, value.y);
}

ofxAudioUnit* BaseUnit::get() {
    return &unit;
}