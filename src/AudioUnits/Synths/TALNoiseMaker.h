#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxManagedAudioUnit.h"

class TALNoiseMaker : public ofxManagedAudioUnit {

public:
    void setup();
};

const static int TALNoiseMaker_volume = 1;
const static int TALNoiseMaker_filtertype = 2;
const static int TALNoiseMaker_cutoff = 3;
const static int TALNoiseMaker_resonance = 4;
const static int TALNoiseMaker_keyfollow = 5;
const static int TALNoiseMaker_filtercontour = 6;
const static int TALNoiseMaker_filterattack = 7;
const static int TALNoiseMaker_filterdecay = 8;
const static int TALNoiseMaker_filtersustain = 9;
const static int TALNoiseMaker_filterrelease = 10;
const static int TALNoiseMaker_ampattack = 11;
const static int TALNoiseMaker_ampdecay = 12;
const static int TALNoiseMaker_ampsustain = 13;
const static int TALNoiseMaker_amprelease = 14;
const static int TALNoiseMaker_osc1volume = 15;
const static int TALNoiseMaker_osc2volume = 16;
const static int TALNoiseMaker_osc3volume = 17;
const static int TALNoiseMaker_oscmastertune = 18;
const static int TALNoiseMaker_osc1tune = 19;
const static int TALNoiseMaker_osc2tune = 20;
const static int TALNoiseMaker_osc1finetune = 21;
const static int TALNoiseMaker_osc2finetune = 22;
const static int TALNoiseMaker_osc1waveform = 23;
const static int TALNoiseMaker_osc2waveform = 24;
const static int TALNoiseMaker_oscsync = 25;
const static int TALNoiseMaker_lfo1waveform = 26;
const static int TALNoiseMaker_lfo2waveform = 27;
const static int TALNoiseMaker_lfo1rate = 28;
const static int TALNoiseMaker_lfo2rate = 29;
const static int TALNoiseMaker_lfo1amount = 30;
const static int TALNoiseMaker_lfo2amount = 31;
const static int TALNoiseMaker_lfo1destination = 32;
const static int TALNoiseMaker_lfo2destination = 33;
const static int TALNoiseMaker_lfo1phase = 34;
const static int TALNoiseMaker_lfo2phase = 35;
const static int TALNoiseMaker_osc2fm = 36;
const static int TALNoiseMaker_osc2phase = 37;
const static int TALNoiseMaker_osc1pw = 38;
const static int TALNoiseMaker_osc1phase = 39;
const static int TALNoiseMaker_transpose = 40;
const static int TALNoiseMaker_freeadattack = 41;
const static int TALNoiseMaker_freeaddecay = 42;
const static int TALNoiseMaker_freeadamount = 43;
const static int TALNoiseMaker_freeaddestination = 44;
const static int TALNoiseMaker_lfo1sync = 45;
const static int TALNoiseMaker_lfo1keytrigger = 46;
const static int TALNoiseMaker_lfo2sync = 47;
const static int TALNoiseMaker_lfo2keytrigger = 48;
const static int TALNoiseMaker_portamento = 49;
const static int TALNoiseMaker_portamentomode = 50;
const static int TALNoiseMaker_voices = 51;
const static int TALNoiseMaker_velocityvolume = 52;
const static int TALNoiseMaker_velocitycontour = 53;
const static int TALNoiseMaker_velocitycutoff = 54;
const static int TALNoiseMaker_pitchwheelcutoff = 55;
const static int TALNoiseMaker_pitchwheelpitch = 56;
const static int TALNoiseMaker_ringmodulation = 57;
const static int TALNoiseMaker_chorus1enable = 58;
const static int TALNoiseMaker_chorus2enable = 59;
const static int TALNoiseMaker_reverbwet = 60;
const static int TALNoiseMaker_reverbdecay = 61;
const static int TALNoiseMaker_reverbpredelay = 62;
const static int TALNoiseMaker_reverbhighcut = 63;
const static int TALNoiseMaker_reverblowcut = 64;
const static int TALNoiseMaker_oscbitcrusher = 65;
const static int TALNoiseMaker_highpass = 66;
const static int TALNoiseMaker_detune = 67;
const static int TALNoiseMaker_vintagenoise = 68;
const static int TALNoiseMaker_envelopeeditordest1 = 71;
const static int TALNoiseMaker_envelopeeditorspeed = 72;
const static int TALNoiseMaker_envelopeeditoramount = 73;
const static int TALNoiseMaker_envelopeoneshot = 74;
const static int TALNoiseMaker_envelopefixtempo = 75;
const static int TALNoiseMaker_filterdrive = 81;
const static int TALNoiseMaker_delaywet = 82;
const static int TALNoiseMaker_delaytime = 83;
const static int TALNoiseMaker_delaysync = 84;
const static int TALNoiseMaker_delayfactorl = 85;
const static int TALNoiseMaker_delayfactorr = 86;
const static int TALNoiseMaker_delayhighshelf = 87;
const static int TALNoiseMaker_delaylowshelf = 88;
const static int TALNoiseMaker_delayfeedback = 89;