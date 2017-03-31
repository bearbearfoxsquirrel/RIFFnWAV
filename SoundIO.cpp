//
// Created by Michael Davis on 25/03/2017.
//

#include "SoundIO.h"

SoundIO::SoundIO(char *path) {
    this->path = path;
}

SoundIO::SoundIO() {
    this->path = nullptr;
}


RIFF SoundIO::readWAVHeader() {
    RIFF riff;
    char riffID[riff.RIFF_ID_LEN], waveID[riff.WAVE_ID_LEN], fmt[riff.FMT_LEN], data[riff.DATA_LEN];
    int fileSize = 0, sampleRate = 0, bytesPerSecond = 0;
    unsigned int formatLength = 0, sizeOfData = 0;
    short int formatTag = 0, numberChannels = 0, bytesPerSample = 0, bitsPerSample = 0;


    try {
        inputFileStream->read(riffID, riff.RIFF_ID_LEN * sizeof(char));                  //get riffID
        if (riff.isValidRiffID(riffID)) {
            inputFileStream->read((char*) &fileSize, sizeof(int));                       //get fileSize
            inputFileStream->read( waveID, riff.WAVE_ID_LEN * sizeof(char));             //get waveID
            inputFileStream->read( fmt, riff.FMT_LEN * sizeof(char));                    //get fmt
            inputFileStream->read((char*) &formatLength, sizeof(unsigned int));          //get formatLength
            inputFileStream->read((char*) &formatTag, sizeof(short int));                //get formatTag
            inputFileStream->read((char*) &numberChannels, sizeof(short int));           //get numberChannels
            inputFileStream->read((char*) &sampleRate, sizeof(int));                     //get sampleRate
            inputFileStream->read((char*) &bytesPerSecond, sizeof(int));                 //get bytesPerSecond
            inputFileStream->read((char*) &bytesPerSample, sizeof(short int));           //get bytesPerSample
            inputFileStream->read((char*) &bitsPerSample, sizeof(short int));            //get bitsPerSample
            inputFileStream->read( data, riff.DATA_LEN * (sizeof(char)));                //get data
            inputFileStream->read((char*) &sizeOfData, sizeof(unsigned int));            //get sizeOfData
        }
    } catch (const ifstream::failure& e){
        inputFileStream->close();
        cout << "Failure in reading WAV header" << endl;
    }

    riff.setRiffID(riffID);
    riff.setFileSize(fileSize);
    riff.setWaveID(waveID);
    riff.setFmt(fmt);
    riff.setFormatLength(formatLength);
    riff.setNumberChannels(numberChannels);
    riff.setSampleRate(sampleRate);
    riff.setBytesPerSecond(bytesPerSecond);
    riff.setBytesPerSample(bytesPerSample);
    riff.setBitsPerSample(bitsPerSample);
    riff.setData(data);

    return riff;
}

void SoundIO::initInputStream(char* wavFilename) {
    string fullFilePath;
    if (path != nullptr) {
        fullFilePath.append(path);
        fullFilePath.append("/");
        fullFilePath.append(wavFilename);
    } else {
        fullFilePath.append(wavFilename);
    }

    char *fullFilePathChar = new char[fullFilePath.length() + 1];
  //  fullFilePathChar = fullFilePath.c_str();
    std::strcpy(fullFilePathChar, fullFilePath.c_str());

    inputFileStream = new ifstream();
    inputFileStream->read(fullFilePathChar, ios::binary);

    delete [] fullFilePathChar;
}

WAV* SoundIO::read(char *wavFilename) {
    initInputStream(wavFilename);
    WAV* wav = new WAV();

    if (inputFileStream) {
        wav->setHeader(readWAVHeader());

        if (wav->getHeader().getRiffID()[0] == 'R') {

            wav->setNumberOfSamples(wav->getHeader().getSizeOfData() / wav->getHeader().getBytesPerSample());

            unsigned int numberOfSamples = wav->getNumberOfSamples();
            short int *samples = new short int[numberOfSamples]; //create an array of samples

            inputFileStream->read((char *) samples, numberOfSamples * sizeof(short int)); //read samples in one go
            wav->setSamples(samples);
            inputFileStream->close();
        } else {
            //Error creating an ifstream from the specified fileName
            cout << "Unable to open the file:" << wavFilename << endl;
            inputFileStream->close();
            return nullptr;
        }
    } else {
        //Error creating an ifstream from the specified fileName
        cout << "Unable to open the file: " << wavFilename << endl;
        inputFileStream->close();
        return nullptr;
    }

    delete inputFileStream;
    return wav;
}