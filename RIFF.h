#ifndef PRACTICAL_14_RIFF_H
#define PRACTICAL_14_RIFF_H

#include <fstream>

using namespace std;

class RIFF {
public:
    static const int RIFF_ID_LEN = 4;
    static const int WAVE_ID_LEN = 4;
    static const int FMT_LEN = 4;
    static const int DATA_LEN = 4;
    const string RIFF_ID = "RIFF";

    void operator=(const RIFF & riff);

    bool isValidRiffID( char *potentialRiffID);

    RIFF();
    RIFF(RIFF const &riff) ;

   /* RIFF(char *riffID, int fileSize, char *waveID, char *fmt, unsigned int formatLength, short formatTag,
         short numberChannels, int sampleRate, int bytesPerSecond, short bytesPerSample, short bitsPerSample,
         char *data, unsigned int sizeOfData);*/

    ~RIFF();

    //GETTERS
    const char *getRiffID() const;

    int getFileSize() const;

    const char *getWaveID() const;

    int getSampleRate() const;

    const char *getFmt() const;

    unsigned int getFormatLength() const;

    short getFormatTag() const;

    short getNumberChannels() const;

    int getBytesPerSecond() const;

    short int getBytesPerSample() const;

    short int getBitsPerSample() const;

    unsigned int getSizeOfData() const;

    const char *getData() const;

    //SETTERS
    void setRiffID(char* riffID);

    void setFileSize(int fileSize);

    void setFmt(char* fmt);

    void setData(char *data);

    void setFormatLength(unsigned int formatLength);

    void setBytesPerSecond(int bytesPerSecond);

    void setBytesPerSample(short bytesPerSample);

    void setBitsPerSample(short bitsPerSample);

    void setNumberChannels(short numberChannels);

    void setFormatTag(short formatTag);

    void setSampleRate(int sampleRate);

    void setSizeOfData(unsigned int sizeOfData);

    void setWaveID(char* waveID);



private:
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