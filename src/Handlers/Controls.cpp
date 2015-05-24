#include "Controls.h"

string Controls::report() {
    stringstream report;
    report << "CONTROLS" << endl
    << endl << "SPACE:      Start/stop playing"
    << endl << "ENTER:      Toggle fullscreen"
    << endl << "d:          Debug / preset UI"
    << endl << "LEFT/RIGHT: Switch chain"
    << endl << "            (all below controls"
    << endl << "            contextual to this)"
    << endl << "UP/DOWN:    Switch presets"
    << endl << "[]          Switch notes"
    << endl << "u:          Synth UI"
    << endl << "r:          Reverb UI"
    << endl << "f:          Filter UI"
    << endl << "c:          Compressor UI"
    << endl << "s:          Save preset";
    return report.str();
}