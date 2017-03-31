#include <iostream>
#include "WAV.h"
#include "SoundIO.h"
#include "SoundEditor.h"

const int MAX_PATH_LENGTH = 500;

char* getFilePath() {
    char* wavFilePath = new char[MAX_PATH_LENGTH];
    cout << "Please enter in the location of a wav file you would like to edit" << endl;
    cin >> wavFilePath;

    return wavFilePath;
}

bool isYes(char inputToCompare) {
    return inputToCompare == 'y' || inputToCompare == 'Y';
}

bool isNo(char inputToCompare) {
    return inputToCompare == 'n' || inputToCompare == 'Y';
}

bool isYesOrNo(char inputToCompare) {
    return isYes(inputToCompare) || isNo(inputToCompare);
}

bool willUserTryAgain() {
    char tryAgain;
    bool validInput = false;

    while (!validInput){
        cout << "Would you like to try again?";
        cin >> tryAgain;

        if (isYesOrNo(tryAgain)) validInput = true;
    }
    return isYes(tryAgain);
}

int main() {
    WAV* wavFile = nullptr;

    SoundIO* soundIO  = new SoundIO();
    SoundEditor* soundEditor;

    char runApplication = 'y';
    do {
        bool tryAgain = true;
        do {
            char* wavFilePath = getFilePath();
            wavFile = soundIO->read(wavFilePath);

            if (wavFile == nullptr)
                tryAgain = willUserTryAgain();
            else
                tryAgain = false;
        } while (tryAgain);

       // soundEditor = new SoundEditor(wavFile);

        cout << "Would you like to edit another file?" << endl;
        cin >> runApplication;
    } while (isYes(runApplication));

    delete soundIO;

    if (soundEditor != nullptr) delete soundEditor;

    return 0;


}