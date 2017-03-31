#ifndef PRACTICAL_14_WAV_H
#define PRACTICAL_14_WAV_H

#include "RIFF.h"

class WAV {
public:
    WAV();
    WAV(RIFF header);
    ~WAV();

    bool read(char* fileName);
    void save(char* fileName);

    void operator = (const WAV wav);

    //GETTERS
    RIFF getHeader();

    short int* getSamples() const; //Returns the whole sample array to the

    short int getSample(int samplePosition) const;

    short int* getSample(double startTime, double endTime) const; //Returns the samples within a certain start time and end time (in seconds)

    unsigned int getNumberOfSamples() const;

    //SETTERS
    void setHeader(RIFF header);

    void setSample(short int sample, int position);

    void setNumberOfSamples(unsigned int numberOfSamples);

    void setSamples(short int* samples);

private:
    //The WAV header
    RIFF header;

    //The WAV data
    unsigned int numberOfSamples;
    short int* samples;
};

#endif //PRACTICAL_14_WAV_H