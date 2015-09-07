#include "MidiHandler.h"

void MidiHandler::setup(ofxAudioUnit* synth, ofxMidiOut* midiOut, string midiPortId){
    this->synth = synth;
    
    midiReceiver.createMidiDestination(midiPortId);
    midiReceiver.routeMidiTo(*this->synth);
    midiOut->openPort(midiPortId);
}

void MidiHandler::exit() {
    midiOut->closePort();
}