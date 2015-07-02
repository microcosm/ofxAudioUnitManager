#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string _chainName, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor);
    void loadPresets();
    void exit();
    void toMixer(ofxAudioUnit* chainEndpoint);
    void toMixer();
    AudioUnitChain& link(AudioUnitBase* unit);
    AudioUnitChain& link(AudioUnitBase* unit, string unitName);
    AudioUnitChain& to(AudioUnitBase* unit);
    AudioUnitChain& to(AudioUnitBase* unit, string unitName);
    void showUI(int chainIndex, int numChains);
    void showSynthUI(int chainIndex, int numChains);
    bool isSelected();
    void select();
    void deselect();
    ofxMidiOut* midi();
    void sendMidiOn(int note);
    void sendMidiOff(int note);
    ofxAudioUnitTap* tap();
    PresetsHandler* presets();
    string getUnitReport();
    string getMidiReport();
    string getClassName();
    string getName();
    ofColor getColor();

protected:
    void loadUnit(AudioUnitBase* unit, string unitName);
    void loadSynth(AudioUnitBase* synth, string unitName);

    ofxAudioUnitTap tapUnit;
    ofPolyline waveform1, waveform2;
    vector<AudioUnitBase*> units;
    ofxAudioUnit* unitEndpoint;
    ofxAudioUnitMixer* mixer;
    int mixerChannel;
    vector<string> midiEvents;
    
    PresetsHandler presetsHandler;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string chainName, className, report;
};