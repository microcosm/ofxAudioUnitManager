#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitManager.h"
#include "ofxBpm.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void play();
    void togglePlaying();
    void exit();

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
    ofxAudioUnitChain chain1, chain2;
    ofxManagedAudioUnit noiseMaker1, noiseMaker2;
    ofxManagedAudioUnit filter1, filter2, filter3;
    ofxManagedAudioUnit reverb1, reverb2;

    ofxBpm bpm;
    bool playing;
    int note;
};