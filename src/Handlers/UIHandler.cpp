#include "UIHandler.h"

void UIHandler::setup() {
    padding = 10;
    controlsDimensions = ofVec2f(300, 285);
    chainInfoDimensions = ofVec2f(220, 340);
    waveformsDimensions = ofVec2f(220, 80);

    controlsPositions = getControlsPositions();
    chainInfoPositions = ofVec2f(padding, padding);
    waveformsPositions = ofVec2f(padding, chainInfoPositions.y + chainInfoDimensions.y + 5);
}

void UIHandler::drawControls() {
    controlsPositions = getControlsPositions();
    drawDebugBox(controlsPositions.x, controlsPositions.y, controlsDimensions.x, controlsDimensions.y);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(controlsReport(), controlsPositions.x + padding, controlsPositions.y + padding*2);
}

void UIHandler::drawChains(vector<AudioUnitChain*> chains) {
    ofVec2f position;
    for(int i = 0; i < chains.size(); i++) {
        position.x = (chainInfoPositions.x * (i+1)) + (chainInfoDimensions.x * i);
        position.y = chainInfoPositions.y;
        drawWaveforms(chains.at(i), position.x);
        drawChainReport(chains.at(i), position, i+1);
    }
}

void UIHandler::drawWaveforms(AudioUnitChain* chain, float positionX) {
    drawDebugBox(positionX, waveformsPositions.y, waveformsDimensions.x, waveformsDimensions.y, ofColor(chain->getColor(), 64));
    chain->tap()->getStereoWaveform(leftWaveform, rightWaveform, waveformsDimensions.x, waveformsDimensions.y);
    ofSetColor(ofColor::white);
    ofSetLineWidth(1);
    ofTranslate(positionX, waveformsPositions.y);
    leftWaveform.draw();
    rightWaveform.draw();
    ofTranslate(-positionX, -waveformsPositions.y);
}

void UIHandler::drawChainReport(AudioUnitChain* chain, ofVec2f position, int chainNumber) {
    drawDebugBox(position.x, position.y, chainInfoDimensions.x, chainInfoDimensions.y, ofColor(chain->getColor(), 64));
    ofSetColor(ofColor::white);
    ofDrawBitmapString(chainReport(chain, chainNumber), position.x + 10, position.y + 20);
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
            ofGetWidth()  - controlsDimensions.x - padding,
            ofGetHeight() - controlsDimensions.y - padding);
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