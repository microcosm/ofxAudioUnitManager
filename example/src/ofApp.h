#pragma once

#include "ofMain.h"
#include "ofxBpm.h"
#include "Controls.h"
#include "ofxAudioUnit.h"
#include "Compressor.h"
#include "AlchemyChain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void play();
    void togglePlaying();
    void toggleDebugUI();
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
    
    AlchemyChain leftChain, rightChain;
    ofxBpm bpm;
    Compressor compressor;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    Controls controls;
    bool playing, showDebugUI;
};
