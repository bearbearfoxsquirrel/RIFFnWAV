#ifndef PRACTICAL_14_WAV_H
#define PRACTICAL_14_WAV_H

#include "RIFF.h"

class WAV {
public:
    WAV();
    ~WAV();

    bool read(char* fileName);
    void save(char* fileName);

    //GETTERS
    RIFF getHeader();

    short int* getSamples() const; //Returns the whole sample array to the

    short int getSample(int samplePostion) const;

    short int* getSample(double startTime, double endTime) const; //Returns the samples within a certain start time and end time (in seconds)

    unsigned int getNumberOfSamples() const;

    //SETTERS
    void setSample(short int sample, int position) const;

private:
    //The WAV header
    RIFF header;

    //The WAV data
    unsigned int numberOfSamples;
    short int* samples;
};

#endif //PRACTICAL_14_WAV_H