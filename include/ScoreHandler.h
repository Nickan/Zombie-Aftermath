#ifndef SCOREHANDLER_H
#define SCOREHANDLER_H

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class ScoreHandler
{
    public:
        ScoreHandler();
        void readFromFile(const string&);
        void writeToFile(const string&);
        void createNewScoreFile(const string&, const int&);
        void addScoreToList(const int&);

        bool isFileExists(const string&);

        vector<int>& getScoreList();

        ~ScoreHandler();
    protected:
    private:
        vector<int> scoreList;

        ofstream scoreWriter;
        ifstream scoreReader;
};

#endif // SCOREHANDLER_H
