#include "AlchemyChain.h"

void AlchemyChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "AlchemyChain";

    //Load unit(s) in the reverse order to which you will connect them
    //This ensures the UI is accurate
    load(&reverb);
    load(&filter);
    
    //Load synth or generating unit last
    load(&alchemy);

    //Connect units and pipe out to the mixer
    sendOut(&
        alchemy.getUnit()->
        connectTo(*filter.getUnit()).
        connectTo(*reverb.getUnit())
    );
}

AlchemyPlayer* AlchemyChain::getSynth() {
    return &alchemy;
}

LowPassFilter* AlchemyChain::getFilter(){
    return &filter;
}

Reverb* AlchemyChain::getReverb(){
    return &reverb;
}