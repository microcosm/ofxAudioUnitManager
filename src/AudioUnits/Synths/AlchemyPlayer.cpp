#include "AlchemyPlayer.h"

void AlchemyPlayer::setup() {
    unit = ofxAudioUnit('aumu', 'CaC2', 'CamA');
    type = AU_TYPE_SYNTH;
    className = "AlchemyPlayer";
    ofxManagedAudioUnit::setup();
}