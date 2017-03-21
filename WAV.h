#ifndef PRACTICAL_14_WAV_H
#define PRACTICAL_14_WAV_H

#include "RIFF.h"

class WAV {
public:
    WAV();
    ~WAV();

    bool read(char* fileName);
    void save(char* fileName);


    //Reverse sample
    void reverseSample();
    void reverseSample(int startTime, int endTime);

    //Split sample into segments & re-concatenate
    void splitAndConcat();

private:
    //The WAV header
    RIFF header;

    //The WAV data
    unsigned int numberOfSamples;
    short int* samples;
};

#endif //PRACTICAL_14_WAV_H