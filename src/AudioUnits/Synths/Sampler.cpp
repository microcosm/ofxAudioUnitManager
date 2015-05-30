#include "Sampler.h"

void Sampler::setup() {
    unit = ofxAudioUnitSampler();
    type = AU_TYPE_SYNTH;
    className = "Sampler";
    AudioUnitBase::setup();
}