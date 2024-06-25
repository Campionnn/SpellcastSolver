#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Trie.h"

using namespace std;

class Parser {
public:
    Parser(const vector<vector<char>>& _grid, Trie& _dictTrie) : grid(_grid), dictTrie(_dictTrie) {
        numRows = grid.size();
        numCols = grid[0].size();
    }

    void parseGridIntoTrie(Trie& trie);
    void searchFromCell(Trie& trie, vector<vector<bool>>& visited, string& word, int row, int col);
private:
    const vector<vector<char>>& grid;
    Trie& dictTrie;
    int numRows;
    int numCols;
};

#endif