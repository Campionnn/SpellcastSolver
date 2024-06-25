#ifndef WORDSCORER_H
#define WORDSCORER_H

#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <unordered_map>

using namespace std;

class WordScorer {
public:
    WordScorer(vector<vector<char>> grid, vector<string> words, vector<pair<pair<int, int>, string>> bonuses);
    vector<tuple<string, int, vector<pair<int, int>>>> getWordScores();
private:
    vector<vector<char>> grid;
    vector<string> words;
    vector<pair<pair<int, int>, string>> bonuses;
    unordered_map<char, int> scoreMap;

    vector<pair<int, int>> getLetterPositions(char letter, pair<int, int> prevPosition);
    vector<vector<pair<int, int>>> findAllPaths(string word);
    void findAllPathsHelper(string word, vector<pair<int, int>>& path, vector<vector<pair<int, int>>>& paths);
};

#endif