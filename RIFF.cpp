#include <iostream>
#include "RIFF.h"
bool RIFF::read(ifstream &filestreamIn) {
    //Read values of header
    try {
        filestreamIn.read(riffID, RIFF_ID_LEN * sizeof(char));                          //get riffID
        if (riffID[0] == 'R' && riffID[1] == 'I' && riffID[2] == 'F' && riffID[3] == 'F') {
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
}


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
