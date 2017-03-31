#include <iostream>
#include "RIFF.h"

RIFF::RIFF() {

}

RIFF::~RIFF() {

}

RIFF::RIFF(RIFF const & riff ) : fileSize(riff.fileSize),
formatLength(riff.formatLength), formatTag(riff.formatTag),
numberChannels(riff.numberChannels), sampleRate(riff.sampleRate),
bytesPerSecond(riff.bytesPerSecond), bytesPerSample(riff.bytesPerSample),
bitsPerSample(riff.bitsPerSample), sizeOfData(riff.sizeOfData) {
    for (int i = 0; i < RIFF_ID_LEN; i++) {
        riffID[i] = riff.riffID[i];
        waveID[i] = riff.waveID[i];
        fmt[i] = riff.fmt[i];
        data[i] = riff.data[i];
    }
}

void RIFF::operator=(const RIFF & riff) {
    setFileSize(riff.fileSize);
    setFormatLength(riff.formatLength);
    setNumberChannels(riff.numberChannels);
    setSampleRate(riff.sampleRate);
    setBytesPerSecond(riff.bytesPerSecond);
    setBytesPerSample(riff.bytesPerSample);
    setBitsPerSample(riff.bitsPerSample);
    setSizeOfData(riff.sizeOfData);

    for (int i = 0; i < RIFF_ID_LEN; i++) {
        riffID[i] = riff.riffID[i];
        waveID[i] = riff.waveID[i];
        fmt[i] = riff.fmt[i];
        data[i] = riff.data[i];
    }
}

/*
bool RIFF::read(ifstream &filestreamIn) {
    //Read values of header
    try {
        filestreamIn.read(riffID, RIFF_ID_LEN * sizeof(char));                          //get riffID
        if () {
            filestreamIn.read((char *) &fileSize, sizeof(int));               //get fileSize
            filestreamIn.read(waveID, WAVE_ID_LEN * sizeof(char));            //get waveID
            filestreamIn.read(fmt, FMT_LEN * sizeof(char));                   //get fmt
            filestreamIn.read((char *) &formatLength, sizeof(unsigned int));  //get formatLength
            filestreamIn.read((char *) &formatTag, sizeof(short int));        //get formatTag
            filestreamIn.read((char *) &numberChannels, sizeof(short int));   //get numberChannels
            filestreamIn.read((char *) &sampleRate, sizeof(int));             //get sampleRate
            filestreamIn.read((char *) &bytesPerSecond, sizeof(int));         //get bytesPerSecond
            filestreamIn.read((char *) &bytesPerSample, sizeof(short int));   //get bytesPerSample
            filestreamIn.read((char *) &bitsPerSample, sizeof(short int));    //get bitsPerSample
            filestreamIn.read(data, DATA_LEN * (sizeof(char)));               //get data
            filestreamIn.read((char *) &sizeOfData, sizeof(unsigned int));    //get sizeOfData
        } else {
           return false;
        }
    } catch (const ifstream::failure& e){
        filestreamIn.close();
        return false;
    }
    return true;
}*/

bool RIFF::isValidRiffID(char* potentialRiffID) {
    for (short int i = 0; i < RIFF_ID_LEN; i++)
        if (potentialRiffID[i] != RIFF_ID[i]) return false;
    return true;
}

/*
void RIFF::write(ofstream &filestreamOut) {
    try {

        if (riffID[0] == 'R' && riffID[1] == 'I' && riffID[2] == 'F' && riffID[3] == 'F') {

            for (int i = 0; i < RIFF_ID_LEN; i++)
                filestreamOut.write(&riffID[i], sizeof(char));

            filestreamOut.write((char *) &fileSize, sizeof(int));//write fileSize


            for (int i = 0; i < WAVE_ID_LEN; i++)
                filestreamOut.write(&waveID[i], sizeof(char));

            for (int i = 0; i < FMT_LEN; i++)
                filestreamOut.write(&fmt[i], sizeof(char));

            filestreamOut.write((char *) &formatLength, sizeof(unsigned int));  //write formatLength
            filestreamOut.write((char *) &formatTag, sizeof(short int));        //write formatTag
            filestreamOut.write((char *) &numberChannels, sizeof(short int));   //write numberChannels
            filestreamOut.write((char *) &sampleRate, sizeof(int));             //write sampleRate
            filestreamOut.write((char *) &bytesPerSecond, sizeof(int));         //write bytesPerSecond
            filestreamOut.write((char *) &bytesPerSample, sizeof(short int));   //write bytesPerSample
            filestreamOut.write((char *) &bitsPerSample, sizeof(short int));    //write bitsPerSample

            for (int i = 0; i < DATA_LEN; i++)
                filestreamOut.write(&data[i], sizeof(char));

            filestreamOut.write((char *) &sizeOfData, sizeof(unsigned int));    //write sizeOfData
        } else {
            cout << "File is not in RIFF header format" << endl;
            filestreamOut.close();
        }
    } catch (const ofstream::failure &e) {
        cout << "Problem writing RIFF Header" << endl;
        filestreamOut.close();
    }
}
 */

short int RIFF::getBytesPerSample() const {
    return bytesPerSample;
}

short int RIFF::getBitsPerSample() const {
    return bitsPerSample;
}

int RIFF::getSampleRate() const {
    return sampleRate;
}

unsigned int RIFF::getSizeOfData() const {
    return sizeOfData;
}

const char *RIFF::getRiffID() const {
    return riffID;
}

int RIFF::getFileSize() const {
    return fileSize;
}

void RIFF::setFileSize(int fileSize) {
    RIFF::fileSize = fileSize;
}

const char *RIFF::getWaveID() const {
    return waveID;
}

const char *RIFF::getFmt() const {
    return fmt;
}

unsigned int RIFF::getFormatLength() const {
    return formatLength;
}

void RIFF::setFormatLength(unsigned int formatLength) {
    RIFF::formatLength = formatLength;
}

short RIFF::getFormatTag() const {
    return formatTag;
}

void RIFF::setFormatTag(short formatTag) {
    RIFF::formatTag = formatTag;
}

short RIFF::getNumberChannels() const {
    return numberChannels;
}

void RIFF::setNumberChannels(short numberChannels) {
    RIFF::numberChannels = numberChannels;
}

void RIFF::setSampleRate(int sampleRate) {
    RIFF::sampleRate = sampleRate;
}

int RIFF::getBytesPerSecond() const {
    return bytesPerSecond;
}

void RIFF::setBytesPerSecond(int bytesPerSecond) {
    RIFF::bytesPerSecond = bytesPerSecond;
}

void RIFF::setBytesPerSample(short bytesPerSample) {
    RIFF::bytesPerSample = bytesPerSample;
}

void RIFF::setBitsPerSample(short bitsPerSample) {
    RIFF::bitsPerSample = bitsPerSample;
}

const char *RIFF::getData() const {
    return data;
}

void RIFF::setSizeOfData(unsigned int sizeOfData) {
    RIFF::sizeOfData = sizeOfData;
}

void RIFF::setRiffID(char* riffID) {
    for (unsigned int i = 0; i < RIFF_ID_LEN; i++)
        this->riffID[i] = riffID[i];
}

void RIFF::setWaveID(char *waveID) {
    for (unsigned int i = 0; i < WAVE_ID_LEN; i++)
        this->waveID[i] = waveID[i];
}

void RIFF::setFmt(char *fmt) {
    for (unsigned int i = 0; i < FMT_LEN; i++)
        this->fmt[i] = fmt[i];
}

void RIFF::setData(char *data) {
    for (unsigned int i = 0; i < DATA_LEN; i++)
        this->data[i] = data[i];
}
/*RIFF::RIFF(char *riffID, int fileSize, char *waveID, char *fmt, unsigned int formatLength, short formatTag,
           short numberChannels, int sampleRate, int bytesPerSecond, short bytesPerSample, short bitsPerSample,
           char *data, unsigned int sizeOfData) : riffID(riffID), fileSize(fileSize), waveID(waveID), fmt(fmt),
                                                  formatLength(formatLength), formatTag(formatTag),
                                                  numberChannels(numberChannels), sampleRate(sampleRate),
                                                  bytesPerSecond(bytesPerSecond), bytesPerSample(bytesPerSample),
                                                  bitsPerSample(bitsPerSample), data(data), sizeOfData(sizeOfData) {}*/

