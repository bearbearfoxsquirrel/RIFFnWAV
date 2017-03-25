//
// Created by Michael Davis on 25/03/2017.
//

#include "SoundIO.h"

SoundIO::SoundIO(char *path) {
    this->path = path;
}



RIFF* SoundIO::readWAVHeader() {
    char *riffID, *waveID, *fmt, *data;
    int fileSize, sampleRate, bytesPerSecond;
    unsigned int formatLength, sizeOfData;
    short int formatTag, numberChannels,bytesPerSample, bitsPerSample;

    RIFF* riff = new RIFF();

    try {
        inputFileStream->read(riffID, riff->RIFF_ID_LEN * sizeof(char));            //get riffID
        if (riff->isValidRiffID(riffID)) {
            inputFileStream->read((char*) &fileSize, sizeof(int));                       //get fileSize
            inputFileStream->read( waveID, riff->WAVE_ID_LEN * sizeof(char));      //get waveID
            inputFileStream->read( fmt, riff->FMT_LEN * sizeof(char));             //get fmt
            inputFileStream->read((char*) &formatLength, sizeof(unsigned int));          //get formatLength
            inputFileStream->read((char*) &formatTag, sizeof(short int));                //get formatTag
            inputFileStream->read((char*) &numberChannels, sizeof(short int));           //get numberChannels
            inputFileStream->read((char*) &sampleRate, sizeof(int));                     //get sampleRate
            inputFileStream->read((char*) &bytesPerSecond, sizeof(int));                 //get bytesPerSecond
            inputFileStream->read((char*) &bytesPerSample, sizeof(short int));           //get bytesPerSample
            inputFileStream->read((char*) &bitsPerSample, sizeof(short int));            //get bitsPerSample
            inputFileStream->read( data, riff->DATA_LEN * (sizeof(char)));         //get data
            inputFileStream->read((char*) &sizeOfData, sizeof(unsigned int));            //get sizeOfData
        }
    } catch (const ifstream::failure& e){
        inputFileStream->close();
        cout << "Failure in reading WAV header" << endl;
    }

    delete riff;
    riff = new RIFF(riffID, fileSize, waveID, fmt, formatLength, formatTag,
                    numberChannels, sampleRate, bytesPerSecond, bytesPerSample, bitsPerSample, data, sizeOfData);
    return riff;
}

WAV* SoundIO::read(char *wavFilename) {
    string fullFilePath;
    fullFilePath.append(path + '/');
    fullFilePath.append(wavFilename);

    inputFileStream = new ifstream(fullFilePath, ios::binary);
    WAV wav;



    if (inputFileStream) {
        if (wav.getHeader().read(filestreamIn)) {
            numberOfSamples = header.getSizeOfData() / header.getBytesPerSample(); //work out the number of samples in the WAV file
            samples = new short int[numberOfSamples]; //create an array of samples

            filestreamIn.read((char*) samples, numberOfSamples * sizeof(short int)); //read samples in one go
        } else {
            //Error reading the RIFF header of the WAV file
            cout << "Problem reading header file of " << wavFilename << endl;
            return false;
        }
    } else {
        //Error creating an ifstream from the specified fileName
        cout << "Unable to open the file:" << wavFilename << endl;
        return false;
    }
    filestreamIn.close();
    return true;
}