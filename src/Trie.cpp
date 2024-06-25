#include "../headers/Trie.h"
#include <iostream>

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    destroyTrie(root);
}

void Trie::destroyTrie(TrieNode* node) {
    for (auto& child : node->children) {
        destroyTrie(child.second);
    }
    delete node;
}

void Trie::insert(std::string word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->isEndOfWord = true;
}

bool Trie::search(std::string word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            return false;
        }
        curr = curr->children[c];
    }
    return curr->isEndOfWord;
}

bool Trie::startsWith(std::string prefix) {
    TrieNode* curr = root;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) {
            return false;
        }
        curr = curr->children[c];
    }
    return true;
}

void Trie::print() {
    std::string word;
    printHelper(root, word);
}

void Trie::printHelper(TrieNode* node, std::string& word) {
    if (node->isEndOfWord) {
        std::cout << word << std::endl;
    }
    for (auto& child : node->children) {
        word.push_back(child.first);
        printHelper(child.second, word);
        word.pop_back();
    }
}

vector<string> Trie::getWords() {
    vector<string> words;
    string word;
    getWordsHelper(root, word, words);
    return words;
}

void Trie::getWordsHelper(TrieNode* node, string& word, vector<string>& words) {
    if (node->isEndOfWord) {
        words.push_back(word);
    }
    for (auto& child : node->children) {
        word += child.first;
        getWordsHelper(child.second, word, words);
        word.pop_back();
    }
}

// #include <pybind11/pybind11.h>
// namespace py = pybind11;

// PYBIND11_MODULE(Trie_, m) {
//     py::class_<Trie>(m, "Trie")
//         .def(py::init<>())
//         .def("insert", &Trie::insert)
//         .def("search", &Trie::search)
//         .def("startsWith", &Trie::startsWith)
//         .def("print", &Trie::print)
//         .def("getWords", &Trie::getWords);
// }