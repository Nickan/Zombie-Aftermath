#include "ScoreHandler.h"

ScoreHandler::ScoreHandler() {

}

void ScoreHandler::readFromFile(const string& filePath) {
    scoreList.clear();
    scoreReader.clear();
    scoreReader.open(filePath.c_str());

    ///< If the file exists
    if (scoreReader.is_open()) {
        int recordedScore;
        while (scoreReader >> recordedScore) {
            scoreList.push_back(recordedScore);
        }
    }
    scoreReader.close();
}

void ScoreHandler::writeToFile(const string& filePath) {
    scoreWriter.clear();
    scoreWriter.open(filePath.c_str());

    for (unsigned int i = 0; i < scoreList.size(); ++i) {
        scoreWriter << scoreList.at(i) << endl;
    }
    scoreWriter.close();
}

void ScoreHandler::createNewScoreFile(const string& filePath, const int& numOfScores) {
    scoreList.clear();
    scoreWriter.clear();
    scoreWriter.open(filePath.c_str());

    for (int i = 0; i < numOfScores; ++i) {
        scoreList.push_back(0);
        scoreWriter << 0 << endl;
    }
}

void ScoreHandler::addScoreToList(const int& score) {
    for (unsigned int i = 0; i < scoreList.size(); ++i) {
        if (score > scoreList.at(i)) {
            scoreList.insert(scoreList.begin() + i, score);
            scoreList.pop_back();
            return;
        }
    }
}

bool ScoreHandler::isFileExists(const string& filePath) {
    scoreReader.clear();
    scoreReader.open(filePath.c_str());

    if (scoreReader.is_open()) {
        return true;
    }
    return false;
}

vector<int>& ScoreHandler::getScoreList() {
    return scoreList;
}

ScoreHandler::~ScoreHandler() { }
