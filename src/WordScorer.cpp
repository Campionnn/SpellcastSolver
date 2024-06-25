#include "../headers/WordScorer.h"

#include <iostream>
#include <algorithm>

WordScorer::WordScorer(vector<vector<char>> grid, vector<string> words, vector<pair<pair<int, int>, string>> bonuses) {
    this->grid = grid;
    this->words = words;
    this->bonuses = bonuses;
    scoreMap = {
        {'a', 1},
        {'e', 1},
        {'i', 1},
        {'o', 1},
        {'n', 2},
        {'r', 2},
        {'s', 2},
        {'t', 2},
        {'d', 3},
        {'g', 3},
        {'l', 3},
        {'b', 4},
        {'h', 4},
        {'p', 4},
        {'m', 4},
        {'u', 4},
        {'y', 4},
        {'c', 5},
        {'f', 5},
        {'v', 5},
        {'w', 5},
        {'k', 6},
        {'j', 7},
        {'x', 7},
        {'q', 8},
        {'z', 8}
    };
}

vector<tuple<string, int, vector<pair<int, int>>>> WordScorer::getWordScores() {
    vector<tuple<string, int, vector<pair<int, int>>>> wordScores;
    for (string word : words) {
        vector<vector<pair<int, int>>> paths = findAllPaths(word);
        for (vector<pair<int, int>> path : paths) {
            bool doublePoints = false;
            int score = 0;
            for (pair<int, int> position : path) {
                char c = grid[position.first][position.second];
                int letterScore = scoreMap[c];
                string bonus = "";
                for (auto b : bonuses) {
                    if (b.first == position) {
                        bonus = b.second;
                        break;
                    }
                }
                if (bonus == "DL") {
                    letterScore *= 2;
                } else if (bonus == "TL") {
                    letterScore *= 3;
                } else if (bonus == "2x") {
                    doublePoints = true;
                }
                score += letterScore;
            }
            if (doublePoints) {
                score *= 2;
            }
            if (word.length() >= 6) {
                score += 10;
            }
            wordScores.push_back(make_tuple(word, score, path));
        }
    }
    return wordScores;
}

vector<pair<int, int>> WordScorer::getLetterPositions(char letter, pair<int, int> prevPosition) {
    vector<pair<int, int>> letterPositions;
    for (int i = prevPosition.first - 1; i <= prevPosition.first + 1; i++) {
        for (int j = prevPosition.second - 1; j <= prevPosition.second + 1; j++) {
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
                continue;
            }
            if (grid[i][j] == letter) {
                letterPositions.push_back(make_pair(i, j));
            }
        }
    }
    return letterPositions;
}

vector<vector<pair<int, int>>> WordScorer::findAllPaths(string word) {
    vector<vector<pair<int, int>>> paths;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == word[0]) {
                vector<pair<int, int>> path = {{i, j}};
                findAllPathsHelper(word, path, paths);
            }
        }
    }
    return paths;
}

void WordScorer::findAllPathsHelper(string word, vector<pair<int, int>>& path, vector<vector<pair<int, int>>>& paths) {
    if (word.size() == path.size()) {
        paths.push_back(path);
        return;
    }
    char c = word[path.size()];
    vector<pair<int, int>> letterPositions = getLetterPositions(c, path.back());
    for (pair<int, int> position : letterPositions) {
        if (find(path.begin(), path.end(), position) == path.end()) {
            path.push_back(position);
            findAllPathsHelper(word, path, paths);
            path.pop_back();
        }
    }
}

// #include <pybind11/pybind11.h>
// namespace py = pybind11;

// PYBIND11_MODULE(WordScorer_, m) {
//     py::class_<WordScorer>(m, "WordScorer")
//         .def(py::init<vector<vector<char>>, vector<string>, vector<pair<pair<int, int>, string>>>())
//         .def("getWordScores", &WordScorer::getWordScores);
// }