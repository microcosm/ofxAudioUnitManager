#include "TALNoiseMaker.h"

void TALNoiseMaker::setup() {
    unit = ofxAudioUnit('aumu', 'ncut', 'TOGU');
    type = AU_TYPE_SYNTH;
    className = "TALNoiseMaker";
    ofxManagedAudioUnit::setup();
}