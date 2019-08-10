#pragma once
#include "ofMain.h"
#include "aumMidi.h"

class aumUtils {
    
public:
    void setup();
    string executeMidiCommand(string command, ofxMidiOut *midi);
    int midiNote(string arg);
protected:
    void loadNotesMap();
    int octave, note;
    map<string, int> notes;
};
