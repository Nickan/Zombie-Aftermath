#ifndef SETTINGS_H
#define SETTINGS_H

#include "GameAudio.h"
#include "ScoreHandler.h"

// Handles all the settings and sounds for the game

using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class Settings {
    public:
        Settings();
        static int score;
        static int cash;
        static int life;
        static int zombieKills;

        static bool soundEnable;

        static void reset();

        static void playMainBgm();
        static void playGameBgm();

        static void stopMainBgm();
        static void stopGameBgm();

        static void playSelect();
        static void playFireNormalCannon();
        static void playFireSplashCannon();
        static void playFireIceCannon();

        static void addScoreToList();
        static void recordScoreList();
        static void saveSettings();

        vector<int>& getScoreList();

        static void initialize();

        ~Settings();
    protected:
    private:
        static Music* mainBgmPtr;
        static Music* gameBgmPtr;

        static GameSound* selectPtr;
        static GameSound* fireNormalCannonPtr;
        static GameSound* fireSplashCannonPtr;
        static GameSound* fireIceCannonPtr;

        static string scoreFile;
        static ScoreHandler scoreHandler;

        static ofstream fileSettingsWriter;
        static ifstream fileSettingsReader;

        static void loadSettings();
};

#endif // SETTINGS_H
