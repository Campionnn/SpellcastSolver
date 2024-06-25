#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "./headers/Trie.h"
#include "./headers/Parser.h"
#include "./headers/WordScorer.h"
#include "./headers/words.h"

using namespace std;

vector<tuple<string, int, vector<pair<int, int>>>> getWordScores(vector<vector<char>> grid, vector<pair<pair<int, int>, string>> bonuses);
string getInputTxt();

int main() {
    vector<vector<char>> grid = {
        {'d', 's', 'w', 'a', 'v'},
        {'u', 'a', 'e', 'b', 'g'},
        {'j', 'e', 'e', 'o', 'o'},
        {'t', 'f', 'n', 'y', 'i'},
        {'n', 'z', 'c', 'o', 'e'}
    };
    vector<pair<pair<int, int>, string>> bonuses = {
        {{0, 0}, "TL"},
        {{2, 2}, "2x"}
    };

    vector<tuple<string, int, vector<pair<int, int>>>> wordScores = getWordScores(grid, bonuses);

    if (wordScores.size() == 0) {
        cout << "No words found" << endl;
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        tuple<string, int, vector<pair<int, int>>> wordScore = wordScores[i];
        cout << get<0>(wordScore) << " " << get<1>(wordScore) << " ";
        for (pair<int, int> position : get<2>(wordScore)) {
            cout << "(" << position.first << ", " << position.second << ") ";
        }
        cout << endl;
    }
    return 0;
}

vector<tuple<string, int, vector<pair<int, int>>>> getWordScores(vector<vector<char>> grid, vector<pair<pair<int, int>, string>> bonuses) {
    vector<tuple<string, int, vector<pair<int, int>>>> wordScores;

    Trie dictTrie;
    string test2 = getInputTxt();
    istringstream inputFile(getInputTxt());
    string word;
    while (getline(inputFile, word)) {
        dictTrie.insert(word);
    }

    Parser parser(grid, dictTrie);
    Trie answerTrie;
    parser.parseGridIntoTrie(answerTrie);
    vector<string> words = answerTrie.getWords();

    WordScorer scorer(grid, words, bonuses);
    wordScores = scorer.getWordScores();
    sort(wordScores.begin(), wordScores.end(), [](tuple<string, int, vector<pair<int, int>>> a, tuple<string, int, vector<pair<int, int>>> b) {
        return get<1>(a) > get<1>(b);
    });
    return wordScores;
}

string getInputTxt() {
    return string(reinterpret_cast<const char*>(words_txt), words_txt_len);
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(word_scorer, handle) {
    handle.doc() = "Python binding for Spellcast Solver";
    handle.def("getWordScores", &getWordScores, "Returns a list of words, their scores, and their path in the grid");
}