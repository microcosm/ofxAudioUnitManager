#pragma once
#include "ofMain.h"
#include "aumPresets.h"
#include "aumUtils.h"
#include "aumMidi.h"
#include "aumManagedAudioUnit.h"

#ifdef __APPLE__
#include "ofxAudioUnit.h"
#endif

class aumAudioUnitChain {
    
public:
    virtual void setup(string _chainName, ofxAudioUnitMixer* _mixer, aumManagedAudioUnit* _compressor, int _mixerChannel, ofColor _waveColor);
    void loadPresets();
    void exit();
    aumAudioUnitChain& toMixer(ofxAudioUnit* chainEndpoint);
    aumAudioUnitChain& toMixer();
    aumAudioUnitChain& link(aumManagedAudioUnit* unit);
    aumAudioUnitChain& to(aumManagedAudioUnit* unit);
    void showUI(int chainIndex, int numChains);
    void showSynthUI(int chainIndex, int numChains);
    bool isSelected();
    void select();
    void deselect();
    void sendMidiOn(int midiNum);
    void sendMidiOff(int midiNum);
    void sendNoteOn(string note);
    void sendNoteOff(string note);
    ofxAudioUnitTap* tap();
    aumPresets* presets();
    string getUnitReport();
    string getMidiReport();
    string getClassName();
    string getName();
    ofColor getColor();
    ofxMidiOut midi;

protected:
    void loadUnit(aumManagedAudioUnit* unit);
    void loadSynth(aumManagedAudioUnit* synth);

    ofxAudioUnitTap tapUnit;
    ofPolyline waveform1, waveform2;
    vector<aumManagedAudioUnit*> units;
    ofxAudioUnit* unitEndpoint;
    ofxAudioUnitMixer* mixer;
    aumManagedAudioUnit* compressor;
    int mixerChannel;
    vector<string> midiEvents;
    
    aumPresets presetsHandler;
    aumUtils utils;
    aumMidi midiHandler;
    ofColor waveColor;
    bool selected;
    string chainName, className, report;
};
