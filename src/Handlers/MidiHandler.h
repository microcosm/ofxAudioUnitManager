#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitMidi.h"
#include "ofxMidi.h"

class MidiHandler{
    
public:
    void setup(ofxAudioUnit* synth, string midiPortId);
    void sendNoteOn();
    void sendNoteOff();
    string report();
    void exit();
    void incrementNote();
    void decrementNote();
    void toggleNote();
    
protected:
    
    ofxAudioUnit* synth;
    
    ofxAudioUnitMidiReceiver midiReceiver;
    ofxMidiOut midiOut;
    int note, channel, velocity;
};