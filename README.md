ofxAudioUnitManager
===================
This addon is a leightweight manager for Adam Carlucci's excellent [ofxAudioUnit](https://github.com/admsyn/ofxAudioUnit). It allows you to manage chains of Audio Units and sets of presets with your keyboard at runtime, and to design new chains with just a few lines of code.

![A screenshot of ofxAudioUnitManager](images/ofxAudioUnitManager.png)

You can show and hide the control panel above by hitting 'v'.

What is this addon for?
-----------------------
The purpose of this addon is to make it easy to experiment with sound design in your apps.

To do this, the addon automates tasks associated with using `ofxAudioUnit` that are not related to sound design. It then puts in place a helpful interface allowing you to experiment, save and experiment more, often without recompiling.

How to create an audio unit chain
---------------------------------
Any chain you create will be made up of a number of units in sequence. The first unit in the sequence will be a synth, or sound-generating unit. The subsequent units will be filters or other types of processing units that modulate the audio signal they recieve from the prior unit in the chain, whether that's the synth or another filter.

First, the declarations:
```cpp
    ofxAudioUnitManager manager;
    ofxAudioUnitChain myChain;
    ofxManagedAudioUnit mySynth, myFilter, myReverb;
```

Second, define the synths (and give them a unique name):
```cpp
    mySynth.setup("My Synth", 'aumu', 'ncut', 'TOGU');
    myFilter.setup("My Filter", kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    myReverb.setup("My Reverb", kAudioUnitType_Effect, kAudioUnitSubType_MatrixReverb);
```

Third, link the units to make a chain:
```cpp
    manager.createChain(&myChain)
           .link(&mySynth)
           .to(&myFilter)
           .to(&myReverb)
           .toMixer();
```

That's it. Your chain is good to go.

Those of you who used this addon prior to version 0.2.0 will notice how much simpler this now is to use.

Managing presets
----------------
Use the `left` and `right` arrow keys at runtime to select different chains. Use the `up` and `down` arrow keys to switch between presets on a chain.

On the disk, presets are saved in `bin/data` in a directory named `AudioUnitPresets`:

![How the filesystem is organised](images/finder.png)

Inside `AudioUnitPresets` each chain has a folder. Inside each chain folder are directories for each of the presets. These you save and name from the `ofxAudioUnitManager` user interface.

Inside each preset folder are the individual preset files, one for each unit in the chain.

Sending MIDI to your chains
---------------------------
This addon uses [ofxBpm](https://github.com/mirrorboy714/ofxBpm) and [ofxMidi](https://github.com/danomatika/ofxMidi) to allow you to send MIDI sequences at timed intervals.

```cpp
    void ofApp::setup() {
        ofAddListener(bpm.beatEvent, this, &ofApp::play);
    }

    void ofApp::play(void){
        chain.midi()->sendNoteOn(1, 60); //Each chain exposes it's ofxMidi instance
    }
```

Each chain sets up an `ofxMidi` instance and provides access for you to manipulate it.

Known issues
------------
Whenever a dialog pops up the openFrameworks window loses focus. If you try to use the keyboard, it will appear as though the app has become unresponsive. However all you need to do is click the window again to regain focus. If anyone knows a workaround for this, please contact me.

How to try out this addon
-------------------------
1. Clone [ofxAudioUnit](https://github.com/admsyn/ofxAudioUnit), follow the instructions in the readme, and make sure it works
2. Clone this addon and it's dependencies (listed below)
3. Install the [TAL NoiseMaker](http://kunz.corrupt.ch/products/tal-noisemaker) audio unit. The example project in this repo uses this synth. The 32bit version seems to work with openFrameworks
3. Launch the example project and try out the key controls listed on the screen

Dependencies
------------
- [ofxAudioUnit](https://github.com/admsyn/ofxAudioUnit)
- [ofxMidi](https://github.com/danomatika/ofxMidi)
- [ofxBpm](https://github.com/mirrorboy714/ofxBpm)
- [TAL NoiseMaker](http://kunz.corrupt.ch/products/tal-noisemaker) to run the bundled examples

Tested against [openFrameworks 0.8.4](http://openframeworks.cc/download/).