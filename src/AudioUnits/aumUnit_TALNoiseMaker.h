#pragma once
#include "aumMonitorableAudioUnit.h"

class aumUnit_TALNoiseMaker : public aumMonitorableAudioUnit
{
public:

    //min: 0, max: 1, default: 0
    const static int volume = 1;

    //min: 0, max: 1, default: 0
    const static int filtertype = 2;

    //min: 0, max: 1, default: 0
    const static int cutoff = 3;

    //These variables store the most recenty recorded values
    //of each of the parameters, for recording and detection
    AudioUnitParameterValue previous_volume;
    AudioUnitParameterValue previous_filtertype;
    AudioUnitParameterValue previous_cutoff;

    void doPrintChanges() {
        compareAndPrint("volume", previous_volume, get(volume));
        compareAndPrint("filtertype", previous_filtertype, get(filtertype));
        compareAndPrint("cutoff", previous_cutoff, get(cutoff));
    }

    void doRecordParams() {
        previous_volume = get(volume);
        previous_filtertype = get(filtertype);
        previous_cutoff = get(cutoff);
    }
};
