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

    WAV* read(char* wavFilename);

    RIFF readWAVHeader();

private:
   // bool validateHeader(char header[]);

    char* path;
    ifstream* inputFileStream;
    ostream* fileOutputStream;

    void initInputStream(char* wavFilename);

};
#endif //SPEECH_N_WAVS_SOUNDIO_H
