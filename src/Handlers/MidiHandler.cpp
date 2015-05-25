#include "MidiHandler.h"

void MidiHandler::setup(ofxAudioUnit* synth, string midiPortId){
    this->synth = synth;
    
    channel = 1;
    lastVelocity = -1;
    lastNote = -1;
    
    midiReceiver.createMidiDestination(midiPortId);
    midiReceiver.routeMidiTo(*this->synth);
    midiOut.openPort(midiPortId);
}

ofxMidiOut* MidiHandler::midi() {
    return &midiOut;
}

string MidiHandler::report() {
    stringstream report;
    report << "MIDI" << endl << endl
    << "port " << midiOut.getPort()
    << " \"" << midiOut.getName() << "\"" << endl
    << "virtual? " << midiOut.isVirtual();
    return report.str();
}

void MidiHandler::exit() {
    midiOut.closePort();
}