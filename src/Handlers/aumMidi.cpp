#include "aumMidi.h"

void aumMidi::setup(ofxAudioUnit* synth, ofxMidiOut* midiOut, string midiPortId){
    this->synth = synth;
    
    midiReceiver.createMidiDestination(midiPortId);
    midiReceiver.routeMidiTo(*this->synth);
    midiOut->openPort(midiPortId);
}

void aumMidi::exit(){
    //midiOut->closePort();
}
