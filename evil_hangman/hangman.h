#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: 

    last modified: 9/24/2017
*/

#include <string>
#include <map>
#include <vector>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries, length of word
    // returns if there is a word of that length
	bool start_new_game(int num_guesses, int num_length, bool running_total);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

private:
    map<int, vector<string>> dict;
    map<string, vector<string>> possible_families;
    vector<string> family;
    string final_word;
    int user_length;
    int remaining_guesses;
    string used;
    bool running_total;
};

#endif
