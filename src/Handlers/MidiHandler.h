#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitMidi.h"
#include "ofxMidi.h"

class MidiHandler{
    
public:
    void setup(ofxAudioUnit* synth, string midiPortId);
    ofxMidiOut* midi();
    string report();
    void exit();
    
protected:
    
    ofxAudioUnit* synth;
    
    ofxAudioUnitMidiReceiver midiReceiver;
    ofxMidiOut midiOut;
    int channel, lastNote, lastVelocity;
};