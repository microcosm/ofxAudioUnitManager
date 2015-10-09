#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "ofxManagedAudioUnit.h"

class ofxAudioUnitChain {
    
public:
    virtual void setup(string _chainName, ofxAudioUnitMixer* _mixer, ofxManagedAudioUnit* _compressor, int _mixerChannel, ofColor _waveColor);
    void loadPresets();
    void exit();
    ofxAudioUnitChain& toMixer(ofxAudioUnit* chainEndpoint);
    ofxAudioUnitChain& toMixer();
    ofxAudioUnitChain& link(ofxManagedAudioUnit* unit);
    ofxAudioUnitChain& to(ofxManagedAudioUnit* unit);
    void showUI(int chainIndex, int numChains);
    void showSynthUI(int chainIndex, int numChains);
    bool isSelected();
    void select();
    void deselect();
    void sendMidiOn(int note);
    void sendMidiOff(int note);
    ofxAudioUnitTap* tap();
    PresetsHandler* presets();
    string getUnitReport();
    string getMidiReport();
    string getClassName();
    string getName();
    ofColor getColor();
    ofxMidiOut midi;

protected:
    void loadUnit(ofxManagedAudioUnit* unit);
    void loadSynth(ofxManagedAudioUnit* synth);

    ofxAudioUnitTap tapUnit;
    ofPolyline waveform1, waveform2;
    vector<ofxManagedAudioUnit*> units;
    ofxAudioUnit* unitEndpoint;
    ofxAudioUnitMixer* mixer;
    ofxManagedAudioUnit* compressor;
    int mixerChannel;
    vector<string> midiEvents;
    
    PresetsHandler presetsHandler;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string chainName, className, report;
};