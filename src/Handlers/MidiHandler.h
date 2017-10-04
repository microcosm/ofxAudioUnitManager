#pragma once
#include "ofMain.h"
#include "ofxAudioUnitMidi.h"
#include "ofxMidi.h"

#ifdef __APPLE__
#include "ofxAudioUnit.h"
#endif

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
