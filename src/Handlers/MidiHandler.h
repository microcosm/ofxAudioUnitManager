#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitMidi.h"
#include "ofxMidi.h"

class MidiHandler{

public:
    void setup(ofxAudioUnit* synth, ofxMidiOut* midiOut, string midiPortId);
    ofxMidiOut* midi();
    void exit();
protected:
    ofxAudioUnit* synth;
    ofxAudioUnitMidiReceiver midiReceiver;
    ofxMidiOut* midiOut;
};