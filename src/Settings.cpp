#include "Settings.h"
int Settings::score = 0;
int Settings::cash = 200;
int Settings::life = 50;
int Settings::zombieKills;

bool Settings::soundEnable;

string Settings::scoreFile;

ofstream Settings::fileSettingsWriter;
ifstream Settings::fileSettingsReader;

Music* Settings::mainBgmPtr;
Music* Settings::gameBgmPtr;

GameSound* Settings::fireNormalCannonPtr;
GameSound* Settings::fireSplashCannonPtr;
GameSound* Settings::fireIceCannonPtr;
GameSound* Settings::selectPtr;

ScoreHandler Settings::scoreHandler;

Settings::Settings() {

}

void Settings::initialize() {

    mainBgmPtr = GameAudio::newMusic("assets/gamebgm.wav");
    gameBgmPtr = GameAudio::newMusic("assets/gamebgm.wav");


    selectPtr = GameAudio::newSound("assets/select.wav");
    fireNormalCannonPtr = GameAudio::newSound("assets/firenormalcannon.wav");
    fireSplashCannonPtr = GameAudio::newSound("assets/firesplashcannon.wav");
    fireIceCannonPtr = GameAudio::newSound("assets/fireicecannon.wav");

    scoreFile = "assets/score.txt";

    if (scoreHandler.isFileExists(scoreFile)) {
        scoreHandler.readFromFile(scoreFile);
    } else {
        ///< Specifies the number of scores to be written
        scoreHandler.createNewScoreFile(scoreFile, 10);
    }

    loadSettings();
    reset();

}

void Settings::reset() {
    cash = 200;
    life = 50;
    score = 0;
    zombieKills = 0;
}

void Settings::recordScoreList() {
    scoreHandler.writeToFile(scoreFile);
}

void Settings::addScoreToList() {
    scoreHandler.addScoreToList(score);
    score = 0;
}

void Settings::loadSettings() {
    ///< To be changed later, for sound settings
    fileSettingsReader.clear();
    fileSettingsReader.open("assets/settings.txt");

    if (fileSettingsReader.is_open()) {
        int settingsType;
        fileSettingsReader >> settingsType;
        if (settingsType == 0) {
            soundEnable = false;
        } else {
            soundEnable = true;
        }
    }
    fileSettingsReader.close();
}

void Settings::saveSettings() {
    fileSettingsWriter.clear();
    fileSettingsWriter.open("assets/settings.txt");
    if (soundEnable) {
        fileSettingsWriter << 1 << endl;
    } else {
        fileSettingsWriter << 0 << endl;
    }
    fileSettingsWriter.close();
}

void Settings::playMainBgm() {
    if (soundEnable) {
        mainBgmPtr->play();
    }
}

void Settings::playGameBgm() {
    if (soundEnable) {
        gameBgmPtr->play();
    }
}

void Settings::stopMainBgm() {
    if (soundEnable) {
        mainBgmPtr->stop();
    }
}

void Settings::stopGameBgm() {
    if (soundEnable) {
        gameBgmPtr->stop();
    }
}

void Settings::playSelect() {
    if (soundEnable) {
        selectPtr->play();
    }
}

void Settings::playFireNormalCannon() {
    if (soundEnable) {
        fireNormalCannonPtr->play();
    }
}

void Settings::playFireSplashCannon() {
    if (soundEnable) {
        fireSplashCannonPtr->play();
    }
}

void Settings::playFireIceCannon() {
    if (soundEnable) {
        fireIceCannonPtr->play();
    }
}

vector<int>& Settings::getScoreList() {
    return scoreHandler.getScoreList();
}

Settings::~Settings() {
    GameAudio::dispose();
}
