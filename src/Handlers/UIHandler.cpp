#include "UIHandler.h"

void UIHandler::setup() {
    controlsDimensions = ofVec2f(300, 285);
    chainInfoDimensions = ofVec2f(220, 340);

    controlsPositions = getControlsPositions();
    chainInfoPositions = ofVec2f(20, 20);
}

void UIHandler::drawControls() {
    controlsPositions = getControlsPositions();
    drawDebugBox(controlsPositions.x, controlsPositions.y, controlsDimensions.x, controlsDimensions.y);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(controlsReport(), controlsPositions.x + 10, controlsPositions.y + 20);
}

void UIHandler::drawChains(vector<AudioUnitChain*> chains) {
    for(int i = 0; i < chains.size(); i++) {
        tap = chains.at(i)->tap();
        tap->getStereoWaveform(leftWaveform, rightWaveform, ofGetWidth(), ofGetHeight());
        ofSetColor(chains.at(i)->getColor());
        ofSetLineWidth(1);
        leftWaveform.draw();
        rightWaveform.draw();
    }

    for(int i = 0; i < chains.size(); i++) {
        x = (chainInfoPositions.x * (i+1)) + (chainInfoDimensions.x * i);
        y = chainInfoPositions.y;
        drawDebugBox(x, y, chainInfoDimensions.x, chainInfoDimensions.y, ofColor(chains.at(i)->getColor(), 64));
        ofSetColor(ofColor::white);
        ofDrawBitmapString(chainReport(chains.at(i), i+1), x + 10, y + 20);
    }
}

void UIHandler::drawDebugBox(int x, int y, int width, int height, ofColor color) {
    ofSetColor(color);
    ofFill();
    ofRect(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(x, y, width, height);
}

ofVec2f UIHandler::getControlsPositions() {
    return ofVec2f(
            ofGetWidth()  - controlsDimensions.x - 20,
            ofGetHeight() - controlsDimensions.y - 20);
}

string UIHandler::controlsReport() {
    stringstream report;
    report <<  "            CONTROLS"
    << endl << ""
    << endl << "            MANAGER"
    << endl << "            ----------------------"
    << endl << "         v: Toggle view overlay"
    << endl << "Left/right: Select chain"
    << endl << ""
    << endl << "            SELECTED CHAIN [*]"
    << endl << "            ----------------------"
    << endl << "         u: Show audio unit UIs"
    << endl << "   Up/down: Select preset"
    << endl << "         s: Save preset"
    << endl << "         r: Rename preset"
    << endl << "         d: Delete preset"
    << endl << ""
    << endl << "            EXAMPLE APP"
    << endl << "            ----------------------"
    << endl << "     SPACE: Start/stop playing"
    << endl << "     [ / ]: Current note up / down";
    return report.str();
}

string UIHandler::chainReport(AudioUnitChain *chain, int number) {
    stringstream report;
    report  << ""
            << "CHAIN " << number << " \"" << chain->getName() << "\""
    //        << "CHAIN " << number << (chain->isSelected() ? " [*] SELECTED" : "")
    << endl << ""
    << endl << chain->getUnitReport()
    << endl << ""
    << endl << chain->presets()->report();
    return report.str();
}