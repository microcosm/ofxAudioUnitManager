#include "aumMonitorableAudioUnit.h"

void aumMonitorableAudioUnit::update() {
    if(isMonitoringParams) {
        if(ofGetFrameNum() > 0) {
            doPrintChanges();
        }
        doRecordParams();
    }
}

void aumMonitorableAudioUnit::printParamChanges() {
    startPrintingParamChanges();
}

void aumMonitorableAudioUnit::startPrintingParamChanges() {
    isMonitoringParams = true;
}

void aumMonitorableAudioUnit::stopPrintingParamChanges() {
    isMonitoringParams = false;
}

void aumMonitorableAudioUnit::compareAndPrint(string paramName, AudioUnitParameterValue previousValue, AudioUnitParameterValue currentValue) {
    if(previousValue != currentValue) {
        cout << paramName << " changed from " << previousValue << " to " << currentValue << endl;
    }
}
