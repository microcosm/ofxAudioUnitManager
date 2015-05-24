#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitMidi.h"
#include "ofxMidi.h"

class MidiHandler{
    
public:
    void setup(ofxAudioUnit* synth, string midiPortId);
    ofxMidiOut* midi();
    void sendNoteOn(int note);
    void sendNoteOn(int note, int velocity);
    void sendNoteOff(int note);
    string report();
    void exit();
    
protected:
    
    ofxAudioUnit* synth;
    
    ofxAudioUnitMidiReceiver midiReceiver;
    ofxMidiOut midiOut;
    int channel, lastNote, lastVelocity;
};