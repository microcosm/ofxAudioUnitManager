#include "MidiHandler.h"

void MidiHandler::setup(ofxAudioUnit* synth, string midiPortId){
    this->synth = synth;
    
    midiReceiver.createMidiDestination(midiPortId);
    midiReceiver.routeMidiTo(*this->synth);
    midiOut.openPort(midiPortId);
}

ofxMidiOut* MidiHandler::midi() {
    return &midiOut;
}

void MidiHandler::exit() {
    midiOut.closePort();
}