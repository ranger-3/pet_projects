#pragma once

#include <iostream>
#include "color.h"

using namespace std;

class GuessTheWord
{
	enum { Red = 4, LightGreen = 10, White = 15 };
	enum { Max_errors = 6 };

	string word;
	string guess_word;
	string wrong_guesses;

public:

	GuessTheWord(const string& word);
	~GuessTheWord() {}

	const string GetWord()const { return word; }
	const int GetErrorsCount()const { return wrong_guesses.size(); }
	bool IsGuessed()const { return word == guess_word; }
	bool GuessLetter(const int& letter);
	bool IsAlreadyGuessed(const char& letter)const;
	void ShowGuessWord()const;
	void ShowWrongGuesses()const;
};

