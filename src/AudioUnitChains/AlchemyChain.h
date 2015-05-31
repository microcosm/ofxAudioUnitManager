#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "AlchemyPlayer.h"
#include "LowPassFilter.h"
#include "Reverb.h"
#include "Delay.h"

class AlchemyChain : public AudioUnitChain {
    
public:
    void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    AlchemyPlayer* getSynth();
    LowPassFilter* getFilter();
    Reverb* getReverb();
private:
    AlchemyPlayer alchemy;
    LowPassFilter filter;
    Reverb reverb;
};