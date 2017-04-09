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
        inputFileStream->read(riffID, riff.RIFF_ID_LEN);                                 //get riffID
        if (riff.isValidRiffID(riffID)) {
            inputFileStream->read((char*) &fileSize, sizeof(int));                        //get fileSize
            inputFileStream->read( waveID, riff.WAVE_ID_LEN);                            //get waveID
            inputFileStream->read( fmt, riff.FMT_LEN );                                  //get fmt
            inputFileStream->read((char*) &formatLength, sizeof(unsigned int));          //get formatLength
            inputFileStream->read((char*) &formatTag, sizeof(short int));                //get formatTag
            inputFileStream->read((char*) &numberChannels, sizeof(short int));           //get numberChannels
            inputFileStream->read((char*) &sampleRate, sizeof(int));                     //get sampleRate
            inputFileStream->read((char*) &bytesPerSecond, sizeof(int));                 //get bytesPerSecond
            inputFileStream->read((char*) &bytesPerSample, sizeof(short int));           //get bytesPerSample
            inputFileStream->read((char*) &bitsPerSample, sizeof(short int));            //get bitsPerSample
            inputFileStream->read( data, riff.DATA_LEN);                                 //get data
            inputFileStream->read((char*) &sizeOfData, sizeof(unsigned int));            //get sizeOfData

            riff.setRiffID(riffID);
            riff.setFileSize(fileSize);
            riff.setWaveID(waveID);
            riff.setFmt(fmt);
            riff.setFormatLength(formatLength);
            riff.setFormatTag(formatTag);
            riff.setNumberChannels(numberChannels);
            riff.setSampleRate(sampleRate);
            riff.setBytesPerSecond(bytesPerSecond);
            riff.setBytesPerSample(bytesPerSample);
            riff.setBitsPerSample(bitsPerSample);
            riff.setData(data);
            riff.setSizeOfData(sizeOfData);
        }
    } catch (const ifstream::failure& e){
        inputFileStream->close();
        cout << "Failure in reading WAV header" << endl;
    }
    return riff;

}

char* SoundIO::getFullPath(char *filename) {
    string fullFilePath;
    if (path != nullptr) {
        fullFilePath.append(path);
        fullFilePath.append("/");
         fullFilePath.append(filename);
    } else {
         fullFilePath.append(filename);
    }

    char *fullFilePathChar = new char[fullFilePath.length() + 1];
    std::strcpy(fullFilePathChar, fullFilePath.c_str());
    return fullFilePathChar;
}

void SoundIO::initInputStream(char* wavFilename) {
    char* fullFilePath = getFullPath(wavFilename);

    inputFileStream = new ifstream(fullFilePath, ios::binary);

    delete [] fullFilePath;
}

bool SoundIO::read(WAV* wav, char *wavFilename) {
    initInputStream(wavFilename);
    //WAV* wav = new WAV();

    if (inputFileStream) {
        wav->setHeader(readWAVHeader());

        char* riffID = new char[wav->getHeader().RIFF_ID_LEN];
        strcpy(riffID, wav->getHeader().getRiffID());
        if (wav->getHeader().isValidRiffID(riffID)) {

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
            delete inputFileStream;
            return false;
        }
    } else {
        //Error creating an ifstream from the specified fileName
        cout << "Unable to open the file: " << wavFilename << endl;
        inputFileStream->close();
        delete inputFileStream;
        return false;
    }
    delete inputFileStream;
    return true;
}

void SoundIO::initOutputStream(char *wavFilename) {
    char* fullOutputPath = getFullPath(wavFilename);

    fileOutputStream = new ofstream(fullOutputPath, ios::binary);
    delete [] fullOutputPath;
}

bool SoundIO::saveWAVHeader(RIFF riff) {
    try {
        char riffID[riff.RIFF_ID_LEN], waveID[riff.WAVE_ID_LEN], fmt[riff.FMT_LEN], data[riff.DATA_LEN];

        strcpy(riffID, riff.getRiffID());
        strcpy(waveID, riff.getWaveID());
        strcpy(fmt, riff.getFmt());
        strcpy(data, riff.getData());


        int fileSize = riff.getFileSize(), sampleRate = riff.getSampleRate(), bytesPerSecond = riff.getBytesPerSecond();
        unsigned int formatLength = riff.getFormatLength(), sizeOfData = riff.getSizeOfData();
        short int formatTag = riff.getFormatTag(), numberChannels = riff.getNumberChannels(), bytesPerSample = riff.getBytesPerSample(), bitsPerSample = riff.getBitsPerSample();


        if (riff.isValidRiffID(riffID)) {
            fileOutputStream->write(            riffID, riff.RIFF_ID_LEN);
            fileOutputStream->write(  (char *) &fileSize, sizeof(int));
            fileOutputStream->write(            waveID,  riff.WAVE_ID_LEN);
            fileOutputStream->write(            fmt,  riff.FMT_LEN);
            fileOutputStream->write(  (char *) &formatLength, sizeof(unsigned int));
            fileOutputStream->write(  (char *) &formatTag, sizeof(short int));
            fileOutputStream->write(  (char *) &numberChannels, sizeof(short int));
            fileOutputStream->write(  (char *) &sampleRate, sizeof(int));
            fileOutputStream->write(  (char *) &bytesPerSecond, sizeof(int));
            fileOutputStream->write(  (char *) &bytesPerSample, sizeof(short int));
            fileOutputStream->write(  (char *) &bitsPerSample, sizeof(short int));
            fileOutputStream->write(            data, riff.DATA_LEN);
            fileOutputStream->write(  (char *) &sizeOfData, sizeof(unsigned int));
        }
    } catch (const ifstream::failure& e){
        inputFileStream->close();
        cout << "Failure in reading WAV header" << endl;
        return false;
    }
    return true;
}

bool SoundIO::save(WAV *wav, char *outputFilename) {
    initOutputStream(outputFilename);

    if (fileOutputStream) {
        if (saveWAVHeader(wav->getHeader())) {
            //unsigned int numberOfSamples = wav->getHeader().getSizeOfData() / wav->getHeader().getBytesPerSample();

           // for (unsigned int sample = 0; sample < numberOfSamples; sample++)
            //    fileOutputStream->write((char *) (wav->getSample(sample)), sizeof (short int));
            fileOutputStream->write((char *) wav->getSamples(), sizeof(short int) * wav->getNumberOfSamples());
            return true;
        } else {
            cout << "Error saving file, closing program" << endl;
            exit(1);
        }
    }
    return false;
}
