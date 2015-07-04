#pragma once
#include "ofMain.h"

class ofxAudioUnitManagerUtils {
    
public:
    void setup();
    int midiNote(string arg);
protected:
    void loadNotesMap();
    int octave, note;
    map<string, int> notes;
};