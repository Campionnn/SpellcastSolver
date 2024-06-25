#include "../headers/Parser.h"

void Parser::parseGridIntoTrie(Trie& trie) {
    vector<vector<bool>> visited;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            string word = "";
            visited = vector<vector<bool>>(numRows, vector<bool>(numCols, false));
            searchFromCell(trie, visited, word, row, col);
        }
    }
}

void Parser::searchFromCell(Trie& trie, vector<vector<bool>>& visited, string& word, int row, int col) {
    if (row < 0 || row >= numRows || col < 0 || col >= numCols || visited[row][col]) {
        return;
    }
    visited[row][col] = true;
    word += grid[row][col];
    if (dictTrie.search(word)) {
        trie.insert(word);
    }
    if (dictTrie.startsWith(word)) {
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (r == row && c == col) {
                    continue;
                }
                searchFromCell(trie, visited, word, r, c);
            }
        }
    }
    visited[row][col] = false;
    word.pop_back();
}

// #include <pybind11/pybind11.h>
// namespace py = pybind11;

// PYBIND11_MODULE(Parser_, m) {
//     py::class_<Parser>(m, "Parser")
//         .def(py::init<const vector<vector<char>>&, Trie&>())
//         .def("parseGridIntoTrie", &Parser::parseGridIntoTrie)
//         .def("searchFromCell", &Parser::searchFromCell);
// }