#include "AudioUnitBase.h"

string AudioUnitBase::getClassName() {
    return className;
}

void AudioUnitBase::setup() {}

void AudioUnitBase::showUI() {
    unit.showUI();
}

void AudioUnitBase::set(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void AudioUnitBase::set(int param1, int param2, ofVec2f value) {
    set(param1, value.x);
    set(param2, value.y);
}

void AudioUnitBase::set(int param1, int param2, int param3, ofVec3f value) {
    set(param1, value.x);
    set(param2, value.y);
    set(param3, value.z);
}

ofxAudioUnit* AudioUnitBase::get() {
    return &unit;
}

AudioUnitType AudioUnitBase::getType() {
    return type;
}