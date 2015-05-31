#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "TALNoiseMaker.h"
#include "LowPassFilter.h"
#include "Reverb.h"
#include "Delay.h"

class TALNoiseMakerChain : public AudioUnitChain {
    
public:
    void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    void delayTime(float val);
    void reverbDryWet(float val);
    void filterCutoff(float val);
    void showFilterUI();
    void showReverbUI();
    
protected:
    TALNoiseMaker noiseMaker;
    LowPassFilter filter;
    Reverb reverb;
};