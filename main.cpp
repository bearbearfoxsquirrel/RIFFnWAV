#include <iostream>
#include "WAV.h"
#include "string"









int main() {
    char* wavFilePath = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Speech n Wavs/speech.wav";
    char* wavFilePathSave = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Speech n Wavs/speechsaved.wav";
    char* wavFilePathSaveReverse = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Speech n Wavs/speechsavedReversed.wav";

    WAV wavFile;

    wavFile.read(wavFilePath);
   // wavFile.reverseSample();
  //  wavFile.reverseSample(0.5, 1.5);
    //

    short int* extractFromWAV = wavFile.getSample(0.5, 1.5);

  //  wavFile.save(wavFilePathSaveReverse);
    return 0;


}