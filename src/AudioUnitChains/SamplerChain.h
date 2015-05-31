#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "Sampler.h"
#include "LowPassFilter.h"
#include "Reverb.h"
#include "Delay.h"

class SamplerChain : public AudioUnitChain {
    
public:
    void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    Sampler* getSynth();
    LowPassFilter* getFilter();
    Reverb* getReverb();
private:
    Sampler sampler;
    LowPassFilter filter;
    Reverb reverb;
};