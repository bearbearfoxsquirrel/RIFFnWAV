#include "WAV.h"

using namespace std;
WAV::WAV() {
    //Not needed to initialise the wave file
}

WAV::WAV(RIFF header) {
    this->header = header;

    //Not needed to initialise the wave file
}
void WAV::operator = (const WAV wav) {
    this->header = wav.header;
    this->numberOfSamples = wav.numberOfSamples;

    //delete samples;
 //   samples = new short int[numberOfSamples];

    for (unsigned int i = 0; i < this->numberOfSamples; i++)
        samples[i] = wav.samples[i];
}

WAV::~WAV() {
    delete samples;
}

RIFF WAV::getHeader() {
    return header;
}

void WAV::setHeader(RIFF header)  {
    this->header = header;
}

void WAV::setNumberOfSamples(unsigned int numberOfSamples) {
    this->numberOfSamples = numberOfSamples;
}



void WAV::setSamples(short int *samples) {
    this->samples = samples;
    //for (int i = 0; i < numberOfSamples; i++)
     //   this->samples[i] = samples[i];
}

short int* WAV::getSamples() const {
    return samples;
}

short int WAV::getSample(int samplePosition) const {
    return samples[samplePosition];
}

void WAV::setSample(short int sample, int position) {
    this->samples[position] = sample;
}


short int* WAV::getSample(double startTime, double endTime) const {
    int samplesPerSecond = header.getSampleRate() * header.getBytesPerSample();
    int startSample = startTime * samplesPerSecond;
    int endSample = endTime * samplesPerSecond;

    int extractSamplesLength = endSample - startSample;
    short int* extractedSamples = new short int[extractSamplesLength];

    for (int i = 0; i < extractSamplesLength; i++)
        extractedSamples[i] = samples[startSample + i];
    return extractedSamples;
}

unsigned int WAV::getNumberOfSamples() const {
    return numberOfSamples;
}
/*
void WAV::save(char *fileName) {
    ofstream filestreamOut(fileName);

    if (filestreamOut) {
        try {
            header.write(filestreamOut);
            for (unsigned int i = 0; i < numberOfSamples; i++)
                filestreamOut.write((char*) &(samples[i]), sizeof(short int));

        } catch (const ofstream::failure &e) {
            cout << "Error saving file to location: " << fileName << endl;
        }
        filestreamOut.close();
    }
}



*/