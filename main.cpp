#include <iostream>
#include "WAV.h"

int main() {
    char* wavFilePath = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Practical 14/speech.wav";
    char* wavFilePathSave = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Practical 14/speechsaved.wav";
    char* wavFilePathSaveReverse = "/Users/Michael/Documents/Computer Science/Year Two/CSC4040 - Data Structures and Algorithms/C++ Programs/Practical 14/speechsavedReversed.wav";

    WAV wavFile;

    wavFile.read(wavFilePath);
    wavFile.reverseSample();
    wavFile.reverseSample(5, 200);
    wavFile.save(wavFilePathSaveReverse);
    return 0;


}