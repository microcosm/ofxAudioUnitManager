#pragma once
#include "ofMain.h"
#include "BaseChain.h"
#include "AlchemyPlayer.h"
#include "LowPassFilter.h"
#include "Reverb.h"
#include "Delay.h"

class AlchemyChain : public BaseChain {
    
public:
    void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    void delayTime(float val);
    void reverbDryWet(float val);
    void filterCutoff(float val);
    void alchemyRemixX(float val);
    void alchemyRemixY(float val);
    void showAlchemyUI();
    void showFilterUI();
    void showReverbUI();
    
protected:
    AlchemyPlayer alchemy;
    LowPassFilter filter;
    class Delay delay;
    Reverb reverb;
};