#include "WAV.h"
#include <iostream>
#include <fstream>

using namespace std;
WAV::WAV() {

}

WAV::~WAV() {
    delete samples;
}

bool WAV::read(char *fileName) {
    ifstream filestreamIn(fileName);

    if (filestreamIn) {
        if (header.read(filestreamIn)) {
            numberOfSamples = header.getSizeOfData() / header.getBytesPerSample(); //work out the number of samples in the WAV file
            samples = new short int[numberOfSamples]; //create an array of samples

           // for (unsigned int i = 0; i < numberOfSamples; i++)
             //   filestreamIn.read((char*)&(sample[i]), sizeof(short int));          //read samples, sample by sample
            filestreamIn.read((char*) samples, numberOfSamples * sizeof(short int)); //read samples in one go
            filestreamIn.close();
        } else {
            //Error reading the RIFF header of the WAV file
            cout << "Problem reading header file of " << fileName << endl;
        }
    } else {
        //Error creating an ifstream from the specified fileName
        cout << "Unable to open the file:" << fileName << endl;
    }
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


void WAV::reverseSample() {
        short int tempSample;
        for (unsigned int i = 0; i < numberOfSamples/2; i++) {
            tempSample = samples[i];
            samples[i] = samples[numberOfSamples - i];
            samples[numberOfSamples - i] = tempSample;
        }
}

void WAV::reverseSample(double startTime, double endTime) {
    short int tempSample;
    int startSample = startTime * header.getSampleRate() * header.getBytesPerSample();
    int endSample = endTime * header.getSampleRate() * header.getBytesPerSample();


    for (unsigned int i = startSample; i < endSample / 2; i++) {
        tempSample = samples[i];
        samples[i] = samples[endSample - i];
        samples[endSample - i] = tempSample;
    }
}