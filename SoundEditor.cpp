//
// Created by Michael Davis on 25/03/2017.
//
#include "SoundEditor.h"

SoundEditor::SoundEditor(WAV *wav) {
    this->currentWavFile = wav;
}

SoundEditor::SoundEditor() {
    this->currentWavFile = nullptr;
}

void SoundEditor::reverseWAVSample(WAV *wav, double startTime, double endTime) {
    short int tempSample;
    int samplesPerSecond = wav->getHeader().getSampleRate() * wav->getHeader().getBytesPerSample();
    int startSample = startTime * samplesPerSecond;
    int endSample = endTime * samplesPerSecond;

    unsigned int currentEnd;
    for (unsigned int currentStart = startSample; currentStart < endSample / 2; currentStart++) {
        currentEnd = endSample - currentStart;
        //Swap current start with current end in the wav file
        tempSample = wav->getSample(currentStart);
        wav->setSample(wav->getSample(currentEnd), currentStart); //sample value, position
        wav->setSample(tempSample, currentEnd);
    }
}

void SoundEditor::reverseWAV(WAV *wav) {
    short int tempSample;
    unsigned int numberOfSamples = wav->getNumberOfSamples();

    unsigned int currentEnd;
    for (unsigned int currentStart = 0; currentStart <  numberOfSamples/ 2; currentStart++) {
        currentEnd = numberOfSamples - currentStart;
        //Swap current start with current end in the wav file
        tempSample = wav->getSample(currentStart);
        wav->setSample(wav->getSample(currentEnd), currentStart); //sample value, position
        wav->setSample(tempSample, currentEnd);
    }
}