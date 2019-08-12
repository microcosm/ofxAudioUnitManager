#pragma once
#include "ofMain.h"
#include "aumManagedAudioUnit.h"

class aumMonitorableAudioUnit : public aumManagedAudioUnit {

public:
    void update();
    void printParamChanges();
    void startPrintingParamChanges();
    void stopPrintingParamChanges();

protected:
    bool isMonitoringParams = false;

    virtual void doPrintChanges() = 0;
    virtual void doRecordParams() = 0;
    void compareAndPrint(string paramName, AudioUnitParameterValue previousValue, AudioUnitParameterValue currentValue);
};
