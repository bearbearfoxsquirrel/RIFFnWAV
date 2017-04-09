#include <iostream>
#include "WAV.h"
#include "SoundIO.h"
#include "SoundEditor.h"

const int MAX_PATH_LENGTH = 500;

char* getInputFilePath() {
    char* wavFilePath = new char[MAX_PATH_LENGTH];
    cout << "Please enter in the location of a wav file you would like to edit" << endl;
    cin >> wavFilePath;

    return wavFilePath;
}

char* getOutputFilePath() {
    char* wavFilePath = new char[MAX_PATH_LENGTH];
    cout << "Please enter the location of where to save the file, along with it's filename and format" << endl;
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
    SoundIO* soundIO  = new SoundIO();
    SoundEditor* soundEditor = new SoundEditor();


    char runApplication = 'y';
    do {

        //
        //GET INPUT SOUND FILE
        //
        WAV* wavFile = new WAV();
        bool tryAgain = false;
        do {
            char* wavFilePath = getInputFilePath();

            if (!soundIO->read(wavFile, wavFilePath)) {
                cout << "Would you like to try again? ";
                cin >> runApplication;
                if (isYes(runApplication))
                    tryAgain = true;
                else
                    tryAgain = false;
            } else {
                tryAgain = false;
            }
            delete wavFilePath;
        } while (tryAgain);

        cout << endl;
/*
        //
        // EDITING MENU
        //
        char editorChoice;
        cout << "What would you like to do to this file? " << endl
             << "1. Reverse entire sound file" << endl
             << "2. Reverse a sample of sound file" << endl
             << "3. Concatenate two sound files" << endl
             << "4. Extract a sample from the sound file" << endl
             << "5. Nothing" << endl
             << "Please enter a choice ";
        cin >> editorChoice;


        switch (editorChoice) {
            case '1' :
                soundEditor->reverseWAV(wavFile);
        }

        cout << endl;*/

        //
        // WILL USER SAVE FILE
        //
        char toSave;
        cout << "Would you like to save this edited sound file? ";
        cin >> toSave;

        if (isYes(toSave)) {
            cout << endl;
            char* outputPath = getOutputFilePath();
            soundIO->save(wavFile, outputPath);
            delete outputPath;
        }

        delete wavFile;

        cout << endl;

        //
        // CONTINUE USING APPLICATION?
        //
        cout << "Would you like to edit another file?" << endl;
        cin >> runApplication;
    } while (isYes(runApplication));

    delete soundIO;
    delete soundEditor;
    return 0;
}