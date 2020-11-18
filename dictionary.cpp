#include <iostream>
#include <unordered_map>

using namespace std;

struct Trie
{
    unordered_map<char, Trie*> wordMap;
    string meaning;
    bool isEnd;
};

Trie* getNewTrieNode() 
{ 
    Trie *node = new Trie; 
    node -> isEnd = false; 
    return node; 
}

void insertWord(Trie *&root, const string &word, const string &meaning) {
    if (!root) root = getNewTrieNode();
    Trie *temp = root;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        //If the value of that letter does not exist in wordMap, we create new Trie node with that letter
        if (temp -> wordMap.find(letter) == temp -> wordMap.end()) 
            temp -> wordMap[letter] = getNewTrieNode();
        temp = temp -> wordMap[letter];
    }
    //Make the last letters' Trie nodes; isEnd as true and give it the words' meaning
    temp -> isEnd = true;
    temp -> meaning = meaning;

    return;
}

string searchWord(Trie *root, const string &word) {
    if (!root) return "Dictionary is empty. Please input some words";
    Trie *temp = root;
    for (int i = 0; i < word.length(); i++) {
        temp = temp -> wordMap[word[i]];
        if (!temp) return "Word not found.";
    }
    //If it is the end of a valid word stored in dictionary, return its meaning
    if (temp -> isEnd) return temp -> meaning;
    return "Word not found.";
}

int main() {
    int choice;
    cout << "Enter your response: " << endl << "1. Find a words meaning" << "2. Insert a word into dictionary"
        << endl << "3. View the dictionary" << endl << "4. Quit" << endl;
    Trie *root = NULL;
    switch(choice) {
        case 1: { 
                    string word;
                    cout << "Enter the word: ";
                    cin >> word;
                    cout << "Meaning: " << searchWord(root, word); 
                }
                break;
        case 2: { 
                    string word, meaning;
                    cout << "Enter the word: ";
                    cin >> word;
                    cout << "Enter its meaning: ";
                    cin >> meaning;
                    insertWord(root, word, meaning); 
                }   
                break;
        case 3: viewWords();
                break;
        case 4: exit(0);
        defaut: cout << "Wrong response. Please try again.";
    }

    return 0;
}