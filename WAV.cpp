#include "WAV.h"
#include <iostream>
#include <fstream>

using namespace std;
WAV::WAV() {
    //Not needed to initialise the wave file
}

WAV::~WAV() {
    delete samples;
}

RIFF WAV::getHeader() {
    return header;
}

short int* WAV::getSamples() const {
    return samples;
}

short int WAV::getSample(int samplePostion) const {
    return samples[samplePostion];
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

bool WAV::read(char *fileName) {
    ifstream filestreamIn(fileName, ios::binary);

    if (filestreamIn) {
        if (header.read(filestreamIn)) {
            numberOfSamples = header.getSizeOfData() / header.getBytesPerSample(); //work out the number of samples in the WAV file
            samples = new short int[numberOfSamples]; //create an array of samples

            filestreamIn.read((char*) samples, numberOfSamples * sizeof(short int)); //read samples in one go
        } else {
            //Error reading the RIFF header of the WAV file
            cout << "Problem reading header file of " << fileName << endl;
            return false;
        }
    } else {
        //Error creating an ifstream from the specified fileName
        cout << "Unable to open the file:" << fileName << endl;
        return false;
    }
    filestreamIn.close();
    return true;
}

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



