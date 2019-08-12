#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitManager.h"
#include "aumUnit_TALNoiseMaker.h"
#include "aumUnit_Generic.h"
#include "ofxBpm.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void play();
    void togglePlaying();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxAudioUnitManager manager;
    aumAudioUnitChain myChain, chain2, chain3;
    aumUnit_TALNoiseMaker mySynth, noiseMaker2;
    aumUnit_Generic myFilter, filter2, filter3;
    aumUnit_Generic myReverb, reverb2;

    bool playing, on;
    int note;
};
