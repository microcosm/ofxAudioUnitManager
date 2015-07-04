#pragma once
#include "ofMain.h"
#include "MidiHandler.h"

class ofxAudioUnitManagerUtils {
    
public:
    void setup();
    void executeMidiCommand(string command, ofxMidiOut *midi);
    int midiNote(string arg);
protected:
    void loadNotesMap();
    int octave, note;
    map<string, int> notes;
};