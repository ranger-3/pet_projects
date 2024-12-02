#include "GuessTheWord.h"

GuessTheWord::GuessTheWord(const string& word)
	:
	word(word), guess_word(word.size(), ' ')
{
	int size = this->word.size();
	char ch = 0;
	for (size_t i = 0; i < size; ++i)
	{
		ch = this->word[i];
		if (ch >= 'à' && ch <= 'ÿ')
		{
			this->word[i] -= 32;
		}
	}
}

bool GuessTheWord::GuessLetter(const int& letter)
{
	bool is_right_letter = false;
	size_t size = word.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (word[i] == letter)
		{
			is_right_letter = true;
			guess_word[i] = letter;
		}
	}

	if (!is_right_letter)
	{
		wrong_guesses += letter;
	}

	return is_right_letter;
}

bool GuessTheWord::IsAlreadyGuessed(const char& letter)const
{
	for (const auto& v : guess_word)
	{
		if (v == letter)
		{
			return true;
		}
	}

	for (const auto& v : wrong_guesses)
	{
		if (v == letter)
		{
			return true;
		}
	}

	return false;
}

void GuessTheWord::ShowGuessWord()const
{
	cout << "\t";
	SetColor(White);

	for (const auto& v : guess_word)
	{
		cout << v << ' ';
	}

	cout << "\n\t";

	SetColor(LightGreen);
	for (const auto& v : guess_word)
	{
		cout << "- ";
	}

	SetColor(White);
	cout << endl;
}

void GuessTheWord::ShowWrongGuesses()const
{
	cout << "\t";
	SetColor(White);

	for (const auto& v : wrong_guesses)
	{
		cout << v << ' ';
	}

	cout << "\n\t";

	SetColor(Red);
	for (const auto& v : wrong_guesses)
	{
		cout << "- ";
	}

	SetColor(White);
	cout << endl;
}