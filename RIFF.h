#ifndef PRACTICAL_14_RIFF_H
#define PRACTICAL_14_RIFF_H

#include <fstream>

using namespace std;

class RIFF {
public:
    bool read(ifstream& filestreamIn);
    void write(ofstream& filestreamOut);

    short int getBytesPerSample() const;
    short int getBitsPerSample() const;
    unsigned int getSizeOfData() const;
    int getSampleRate() const;



private:
    static const int RIFF_ID_LEN = 4;
    static const int WAVE_ID_LEN = 4;
    static const int FMT_LEN = 4;
    static const int DATA_LEN = 4;

    //RIFF Header Parameters
    char riffID[RIFF_ID_LEN];
    int fileSize;
    char waveID[WAVE_ID_LEN];
    char fmt[FMT_LEN];
    unsigned int formatLength;
    short int formatTag;
    short int numberChannels;
    int sampleRate;
    int bytesPerSecond;
    short int bytesPerSample;
    short int bitsPerSample;
    char data[DATA_LEN];
    unsigned int sizeOfData;

};

#endif //PRACTICAL_14_RIFF_H