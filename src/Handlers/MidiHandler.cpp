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

void MidiHandler::sendNoteOn(int note) {
    sendNoteOn(note, 64);
}

void MidiHandler::sendNoteOn(int note, int velocity) {
    midiOut.sendNoteOn(channel, note, velocity);
}

void MidiHandler::sendNoteOff(int note) {
    midiOut.sendNoteOff(channel, note);
}

string MidiHandler::report() {
    stringstream report;
    report << "MIDI" << endl << endl
    << "port " << midiOut.getPort()
    << " \"" << midiOut.getName() << "\"" << endl
    << "virtual? " << midiOut.isVirtual() << endl
    << "channel " << channel << endl
    << "note " << lastNote << endl
    << "velocity " << lastVelocity << endl;
    return report.str();
}

void MidiHandler::exit() {
    midiOut.closePort();
}