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
        noiseMaker.getUnit()->
        connectTo(*filter.getUnit()).
        connectTo(*reverb.getUnit())
    );
}

TALNoiseMaker* TALNoiseMakerChain::getSynth() {
    return &noiseMaker;
}

LowPassFilter* TALNoiseMakerChain::getFilter(){
    return &filter;
}

Reverb* TALNoiseMakerChain::getReverb(){
    return &reverb;
}