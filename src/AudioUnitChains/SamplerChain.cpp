#include "SamplerChain.h"

void SamplerChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "SamplerChain";

    //Load unit(s) in the reverse order to which you will connect them
    //This ensures the UI is accurate
    load(&reverb);
    load(&filter);
    
    //Load synth or generating unit last
    load(&sampler);

    //Connect units and pipe out to the mixer
    sendOut(&
        sampler.get()->
        connectTo(*filter.get()).
        connectTo(*reverb.get())
    );
}

Sampler* SamplerChain::getSynth() {
    return &sampler;
}

LowPassFilter* SamplerChain::getFilter(){
    return &filter;
}

Reverb* SamplerChain::getReverb(){
    return &reverb;
}