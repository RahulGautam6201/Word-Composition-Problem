#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

// Structure representing a node in the trie
struct TrieNode {
    bool isEndOfWord; // Indicates if the node marks the end of a word
    unordered_map<char, TrieNode*> children; // Maps characters to child nodes

    TrieNode() : isEndOfWord(false) {}
};

// Function to insert a word into the trie
void insertWord(TrieNode* root, const string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}

// Recursive function to check if a word is a compound word
bool isCompoundWord(const string& word, TrieNode* root, unordered_map<string, bool>& memo, bool isOriginalWord) {
    if (memo.find(word) != memo.end()) {
        return memo[word];
    }

    TrieNode* current = root;
    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];
        if (current->children.find(c) == current->children.end()) {
            break;
        }
        current = current->children[c];

        // If a prefix is found, check the suffix recursively
        if (current->isEndOfWord) {
            string suffix = word.substr(i + 1);
            if ((!isOriginalWord && suffix.empty()) || isCompoundWord(suffix, root, memo, false)) {
                memo[word] = true;
                return true;
            }
        }
    }

    memo[word] = false;
    return false;
}

int main() {
    // List of input files to process
    string inputFiles[] = {"Input_01.txt", "Input_02.txt"};

    for (const string& fileName : inputFiles) {
        ifstream inputFile(fileName);
        if (!inputFile) {
            cerr << "Error: Could not open file " << fileName << endl;
            continue;
        }

        // Load words from file into a vector
        vector<string> words;
        string word;
        while (inputFile >> word) {
            words.push_back(word);
        }
        inputFile.close();

        // Sort words by length in descending order
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() > b.length();
        });

        // Construct the trie from the word list
        TrieNode* root = new TrieNode();
        for (const string& w : words) {
            insertWord(root, w);
        }

        // Memoization map to avoid redundant checks
        unordered_map<string, bool> memo;
        string longestCompoundWord;
        string secondLongestCompoundWord;

        auto startTime = chrono::high_resolution_clock::now();

        // Identify the longest and second longest compound words
        for (const string& w : words) {
            if (isCompoundWord(w, root, memo, true)) {
                if (longestCompoundWord.empty()) {
                    longestCompoundWord = w;
                } else if (secondLongestCompoundWord.empty()) {
                    secondLongestCompoundWord = w;
                    break;
                }
            }
        }

        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = endTime - startTime;

        // Output the results
        cout << "File: " << fileName << endl;
        cout << "Longest Compound Word: " << longestCompoundWord << endl;
        cout << "Second Longest Compound Word: " << secondLongestCompoundWord << endl;
        cout << "Time Taken: " << elapsed.count() << " ms" << endl;
        cout << "------------------------------------" << endl;

        // Free memory allocated for the trie
        vector<TrieNode*> nodesToFree = {root};
        while (!nodesToFree.empty()) {
            TrieNode* node = nodesToFree.back();
            nodesToFree.pop_back();
            for (auto& pair : node->children) {
                nodesToFree.push_back(pair.second);
            }
            delete node;
        }
    }

    return 0;
}