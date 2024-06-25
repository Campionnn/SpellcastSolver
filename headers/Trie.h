#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    struct TrieNode {
        bool isEndOfWord;
        unordered_map<char, TrieNode*> children;
        TrieNode() : isEndOfWord(false) {}
    };
    TrieNode* root;

public:
    Trie();
    ~Trie();
    void insert(string word);
    bool search(string word);
    bool startsWith(string prefix);
    void print();
    vector<string> getWords();
private:
    void printHelper(TrieNode* node, string& word);
    void destroyTrie(TrieNode* node);
    void getWordsHelper(TrieNode* node, string& word, vector<string>& words);
};

#endif