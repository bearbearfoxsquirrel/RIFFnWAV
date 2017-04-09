//
// Created by Michael Davis on 25/03/2017.
//

#ifndef SPEECH_N_WAVS_SOUNDIO_H
#define SPEECH_N_WAVS_SOUNDIO_H

#include <fstream>
#include <iostream>
#include "WAV.h"

using namespace std;

class SoundIO {
public:
    SoundIO(char* path);
    SoundIO();

  //  ~SoundIO();

  //  ifstream getInputFileStream() const;

    bool read(WAV *wav, char *wavFilename);
    bool save(WAV *wav, char* outputFilename);



private:
    char* getFullPath(char* filename);

    RIFF readWAVHeader();
    bool saveWAVHeader(RIFF riff);
    // bool validateHeader(char header[]);

    char* path;
    ifstream* inputFileStream;
    ostream* fileOutputStream;

    void initInputStream(char* wavFilename);
    void initOutputStream(char *wavFilename);

};
#endif //SPEECH_N_WAVS_SOUNDIO_H
