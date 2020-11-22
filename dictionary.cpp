#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define UNDERLINE_ON "\033[4m"
#define UNDERLINE_OFF "\033[0m"

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

string searchMeaning(Trie *root, const string &word) {
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

bool searchWord(Trie *root, string &word) {
    Trie *temp = root;
    for (int i = 0; i < word.length(); i++) {
        temp = temp -> wordMap[word[i]];
        if (!temp) return false;
    }
    return temp -> isEnd;
}

int main() {
    int choice = 0;
    Trie *root = NULL;
    cout << "--------------------------------------------" << endl;
    while (choice <= 5) {
        cout << "Operations available: " << endl << "1. Find a words' meaning" << endl << "2. Insert a word into dictionary"
            << endl << "3. Find words with a particular prefix" << endl << "4. Check spelling of a word" << endl << "5. Quit" << endl << "Enter your response: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                string word;
                cout << "Enter the word: ";
                cin >> word;
                system("cls");
                cout << "Here it is: " << searchMeaning(root, word) << endl << "--------------------------------------------" << endl;
                break;
            }                
            case 2: { 
                string word, meaning;
                cout << "Enter the word: ";
                cin >> word;
                cout << "Enter its meaning: ";
                getline(cin >> ws, meaning);
                insertWord(root, word, meaning); 
                system("cls");
                cout << word << " has been inserted." << endl << "--------------------------------------------" << endl;
                break;
            }    
            case 3: {
                string prefix;
                cout << "Enter the prefix: ";
                cin >> prefix;
                vector <string> possible_words = prefixSearch(root, prefix); 
                system("cls");
                if(possible_words.size() == 0) cout << "No words with the prefix \"" << prefix << "\" are found." << endl;
                else {
                    cout << "Available words: ";
                    for(auto i = possible_words.begin(); i != possible_words.end(); i++)
                        cout << *i << " ";
                }
                cout << endl << "--------------------------------------------" << endl;
                
                break;
            }
            case 4: {
                string word = "";
                cout << "Correctly spelt words will be printed as it is and mispelt words will be underlined." << endl;
                cout << "Enter the word(s): ";
                cin >> ws;
                while(char letter = getchar()) {
                    //if enter is hit, we check the last word
                    if (letter == '\n') {
                        //if word is correctly spelt, we print it. if not, we print underlined word
                        searchWord(root, word) ? cout << word : cout << UNDERLINE_ON << word << UNDERLINE_OFF;
                        cout << letter << "--------------------------------------------" << endl;
                        break;
                    } 
                    //if space is hit, we evaluate previous word
                    else if (letter == ' ') {
                        //if word is correctly spelt, we print it. if not, we print underlined word
                        searchWord(root, word) ? cout << word : cout << UNDERLINE_ON << word << UNDERLINE_OFF;
                        //now we reset word to empty to take in new consequent word
                        word = "";
                        //we print space (which is letter here) for ease in readability
                        cout << letter;
                    }
                    //when letters of word are in input, we concatenate them to our query string
                    else word += letter;
                }
                break;
            }
            case 5: exit(0);
            default: cout << endl << "Wrong response. Please try again.";
        }
    }

    return 0;
}