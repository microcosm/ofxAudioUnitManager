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
    void delayTime(float val);
    void reverbDryWet(float val);
    void filterCutoff(float val);
    
protected:
    Sampler sampler;
    LowPassFilter filter;
    Reverb reverb;
};