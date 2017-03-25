//
// Created by Michael Davis on 25/03/2017.
//

#ifndef SPEECH_N_WAVS_SOUNDEDITOR_H
#define SPEECH_N_WAVS_SOUNDEDITOR_H

#include "WAV.h"

class SoundEditor {

    void extractWAVSample(WAV wav, double startTime, double endTime); //Move to another thing

    void concatWAV(WAV wavToConcat); //Move to another thing

    void reverseWAV(WAV wav);

    void reverseWAVSample(WAV wav, double startTime, double endTime);

};
#endif //SPEECH_N_WAVS_SOUNDEDITOR_H
