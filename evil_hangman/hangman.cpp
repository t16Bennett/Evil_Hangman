/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author:

    last modified: 9/24/2017
*/

#include <fstream>
#include <iostream>

#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() { 
    ifstream fin("dictionary.txt");
    if (!fin) {
        cout << "Could not open 'dictionary.txt' for reading, exiting." << endl;
    }
    double load = 1;
    const double NUM_OF_WORDS = 127143;
    string word;
    while (!fin.eof()) {
        getline(fin, word);
        int length = word.length();
        if(dict.count(length)>0){
            vector<string> temp = dict.at(length);
            temp.push_back(word);
            dict.erase(length);
            dict.emplace(length, temp);
        }
        else{
            vector<string> temp;
            temp.push_back(word);
            dict.emplace(length, temp);
        }
        cout << "Loading word # " << load << " of " << NUM_OF_WORDS << endl;
        load++;
    }
    fin.close();
}


// start_new_game()
//
// Setup a new game of hangman.
bool hangman::start_new_game(int num_guesses, int num_length, bool running_total1) {
    final_word = "";
    used = "";
    user_length = num_length;
    remaining_guesses = num_guesses;
    
    running_total = running_total1;
    //vector<string> toPrint = dict.at(user_length);
    //for(string print: toPrint){
    //    cout << print << endl;
    //}
    
    if(dict.count(user_length)>0){
        family = dict.at(user_length);
        for(int i = 0; i < user_length; i++){
            final_word.push_back('-');
        }
        return true;
    }
    return false;
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    vector<string> keyValues;
    used.push_back(c);
    
    //for(string print: family){
    //    cout << print << endl;
    //}
    
    for(string s: family){
        string tempfinal = final_word;
        for(int i = 0; i < final_word.length(); i++){
            if(s[i] == c){
                tempfinal.at(i) = c;
                //cout << tempfinal << endl;
            }
        }
        keyValues.push_back(tempfinal);
        if(possible_families.count(tempfinal)>0){
            vector<string> tempfamily = possible_families.at(tempfinal);
            tempfamily.push_back(s);
            possible_families.erase(tempfinal);
            possible_families.emplace(tempfinal, tempfamily);
        }
        else{
            vector<string> tempfamily2;
            tempfamily2.push_back(s);
            possible_families.emplace(tempfinal, tempfamily2);
        }
    }
    
    int intlargestFamily = 0;
    string strlargestFamily = "";
    for(string keys: keyValues){
        if(possible_families.at(keys).size() > intlargestFamily){
            strlargestFamily = keys;
            intlargestFamily = possible_families.at(keys).size();
        }
    }
    
    //cout << strlargestFamily << endl;
    if(running_total){
        cout << "Number of remaining words: "<< family.size() << endl;
    }
    
    map<string, vector<string>> dump;
    
    if(final_word == strlargestFamily){
        final_word = strlargestFamily;
        family = possible_families.at(strlargestFamily);
        possible_families = dump;
        remaining_guesses--;
        return false;
    }else{
        final_word = strlargestFamily;
        family = possible_families.at(strlargestFamily);
        possible_families = dump;
        return true;
    }
    
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return final_word;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return remaining_guesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    return used;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for(char a: used){
        if(a == c){
            return true;
        }
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    if(final_word == family.at(0)){
        return true;
    }
    return false;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(remaining_guesses == 0){
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return family.at(0);
}


