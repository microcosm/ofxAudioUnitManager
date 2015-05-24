#include "MidiHandler.h"

void MidiHandler::setup(ofxAudioUnit* synth, string midiPortId){
    this->synth = synth;
    
    channel = 1;
    velocity = 64;
    note = 60;
    
    midiReceiver.createMidiDestination(midiPortId);
    midiReceiver.routeMidiTo(*this->synth);
    midiOut.openPort(midiPortId);
}

void MidiHandler::sendNoteOn() {
    midiOut.sendNoteOn(channel, note, velocity);
}

void MidiHandler::sendNoteOff() {
    midiOut.sendNoteOff(channel, note, velocity);
}

string MidiHandler::report() {
    stringstream report;
    report << "MIDI" << endl << endl
    << "port " << midiOut.getPort()
    << " \"" << midiOut.getName() << "\"" << endl
    << "virtual? " << midiOut.isVirtual() << endl
    << "channel " << channel << endl
    << "note " << note << endl
    << "velocity " << velocity << endl;
    return report.str();
}

void MidiHandler::exit() {
    midiOut.closePort();
}

void MidiHandler::incrementNote() {
    midiOut.sendNoteOff(channel, note, velocity);
    if(note == 127) note = 0;
    else note += 1;
}

void MidiHandler::decrementNote() {
    midiOut.sendNoteOff(channel, note, velocity);
    if(note == 0) note = 127;
    else note -= 1;
}