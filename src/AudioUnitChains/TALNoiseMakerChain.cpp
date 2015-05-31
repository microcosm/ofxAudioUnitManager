#include "TALNoiseMakerChain.h"

void TALNoiseMakerChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "TALNoiseMakerChain";

    //Load unit(s) in the reverse order to which you will connect them
    //This ensures the UI is accurate
    load(&reverb);
    load(&filter);
    
    //Load synth or generating unit last
    load(&noiseMaker);

    //Connect units and pipe out to the mixer
    sendOut(&
        noiseMaker.get()->
        connectTo(*filter.get()).
        connectTo(*reverb.get())
    );
}

void TALNoiseMakerChain::delayTime(float val) {
    reverb.setParameter(DelayTime, val);
}

void TALNoiseMakerChain::reverbDryWet(float val) {
    reverb.setParameter(kReverbParam_DryWetMix, val);
}

void TALNoiseMakerChain::filterCutoff(float val) {
    filter.setParameter(kLowPassParam_CutoffFrequency, val);
}

void TALNoiseMakerChain::showFilterUI() {
    filter.showUI();
}

void TALNoiseMakerChain::showReverbUI() {
    reverb.showUI();
}