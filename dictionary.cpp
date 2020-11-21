#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <string.h>

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

void autoComplete(Trie *current, vector <string> &available_words, const string &prefix) {
    //base cases
    if(!current) return;
    if(current -> isEnd) available_words.push_back(prefix);
    unordered_map <char, Trie*> remaining_words = current -> wordMap;
    for (auto i: remaining_words) 
        autoComplete(remaining_words[i.first], available_words, prefix + i.first);        
}

vector <string> prefixSearch(Trie *root, string &prefix) {
    vector <string> available_words;
    if(!root) return available_words;
    Trie *temp = root;
    for (int i = 0; i < prefix.length(); i++) {
        temp = temp -> wordMap[prefix[i]];
        //if any one of the letters of prefix is not present
        if (!temp) return available_words;      
    }
    //if prefix is present, we find the possible words
    autoComplete(temp, available_words, prefix);
    return available_words;
}

bool checkSpelling() {
    return true;
}

int main() {
    int choice = 0;
    Trie *root = NULL;
    while (choice <= 5) {
        cout << "Operations available: " << endl << "1. Find a words' meaning" << endl << "2. Insert a word into dictionary"
            << endl << "3. Find words with a particular prefix" << endl << "4. Check spelling of a word" << endl << "5. Quit" << endl << "Enter your response: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                string word;
                cout << "Enter the word: ";
                cin >> word;
                cout << "Here it is: " << searchWord(root, word) << endl;; 
                break;
            }                
            case 2: { 
                string word, meaning;
                cout << "Enter the word: ";
                cin >> word;
                cout << "Enter its meaning: ";
                getline(cin >> ws, meaning);
                insertWord(root, word, meaning); 
                cout << word << " has been inserted." << endl;
                break;
            }    
            case 3: {
                string prefix;
                cout << "Enter the prefix: ";
                cin >> prefix;
                vector <string> possible_words = prefixSearch(root, prefix); 
                for(auto i = possible_words.begin(); i != possible_words.end(); i++)
                    cout << *i << " ";
                cout << endl;
                
                break;
            }
            case 4: {
                string word;
                cout << "Enter the word: ";
                cin >> word;
                // if(checkSpelling(root, word)) cout << "Your word is correctly spelt." << endl;
                // else cout << "Your word is misspelt."
            }
            case 5: exit(0);
            default: cout << "Wrong response. Please try again.";
        }
    }

    return 0;
}