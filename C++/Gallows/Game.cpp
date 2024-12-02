#include "Game.h"

const char* file_dictionary{ "dictionary.txt" };
const char* game_name{ "Виселица" };
const char* are_you_sure_to_exit{ "Точно хотите закончить игру?" };
const char* press_any_key{ "Нажмите любую клавишу для продолжения!" };
const char* wrong_symbol_entered{ "Введен неверный символ!" };
const char* letter_already_entered{ "Вы уже вводили такую букву!" };

vector<string> main_menu_points({ "Начать игру", "Выйти из игры" });
vector<string> want_to_exit_points({ "Продолжить игру", "Выйти в главное меню" });

enum { Point1 = 1, Point2, Esc = 27, Red = 4, LightGreen = 10, White = 15, Max_mistakes = 6 };


int my_getch()
{
	int ch = _getch();
	if (ch == 224) {
		ch = _getch();
		return -ch;
	}
	return ch;
}

void save_dictionary(const Dictionary& dictionary)
{
	ofstream fout(file_dictionary, ios::binary);

	if (fout)
	{
		dictionary.SaveEncrypt(fout);
		fout.close();
	}
}

void read_dictionary(Dictionary& dictionary)
{
	ifstream fin(file_dictionary, ios::binary);

	if (fin)
	{
		dictionary.ReadDecrypt(fin);
		fin.close();
	}
}

void main_menu(Dictionary& dictionary)
{
	Menu main_menu(main_menu_points, game_name, "\n\n\t");
	GallowsPicture gallows_picture;
	unsigned short current_point = 1;
	int key = 0;
	bool skip = false;

	read_dictionary(dictionary);

	while (key != Esc)
	{
		
		system("cls");
		gallows_picture.Show();
		main_menu.ShowAndGetNoLoop(key, current_point, skip);

		if (skip || key == Esc)
		{
			continue;
		}

		if (current_point == Point1)
		{
			game(gallows_picture, dictionary.GetRandomWord());
		}
		else if (current_point == Point2)
		{
			key = Esc;
		}

	}

	save_dictionary(dictionary);
}

void game(GallowsPicture& gallows_picture, const string& word)
{
	GuessTheWord guess_the_word(word);
	Menu exit_game_menu(want_to_exit_points, are_you_sure_to_exit);
	char letter = 0;
	bool continue_game = false, win = false, 
		wrong_symbol = false, already_got_letter = false;
	int mistakes_counter = 0;
	time_t start = 0, end = 0;

	gallows_picture.SetStatus(0);
	time(&start);

	while (letter != Esc)
	{
		system("cls");
		gallows_picture.Show();
		cout << endl << endl;
		guess_the_word.ShowGuessWord();
		cout << endl << endl;
		guess_the_word.ShowWrongGuesses();
		cout << endl << endl;
		if (already_got_letter)
		{
			cout << '\t' << letter_already_entered << "\n\n";
			already_got_letter = false;
		}
		else if (wrong_symbol)
		{
			cout << '\t' << wrong_symbol_entered << "\n\n";
			wrong_symbol = false;
		}
		cout << "\n\tВведите букву: ";
		letter = _getch();

		if (letter == Esc)
		{
			exit_game_menu.RepeatMenu(continue_game);
			if (continue_game)
			{
				letter = 0;
			}
			else
			{
				return;
			}
		}

		if (is_letter(letter))
		{
			to_upper(letter);
			if (!guess_the_word.IsAlreadyGuessed(letter))
			{
				if (guess_the_word.GuessLetter(letter))
				{
					win = guess_the_word.IsGuessed();
					if (win)
					{
						break;
					}
				}
				else
				{
					++mistakes_counter;
					gallows_picture.SetStatus(mistakes_counter);
					if (mistakes_counter == Max_mistakes)
					{
						break;
					}
				}
			}
			else
			{
				already_got_letter = true;
			}
		}
		else
		{
			wrong_symbol = true;
		}
	}
	time(&end);
	game_result(win, guess_the_word, gallows_picture, difftime(end, start));
}

bool is_letter(const int& letter)
{
	if (letter >= 'а' && letter <= 'я' || letter >= 'А' && letter <= 'Я')
	{
		return true;
	}

	return false;
}

void show_game_time(const int& time_difference)
{
	int hours = 0, minutes = 0, seconds = time_difference;

	hours = seconds / 3600;
	seconds -= (hours * 3600);
	minutes = seconds / 60;
	seconds -= (minutes * 60);

	printf("\nЗатраченное время: %02d:%02d:%02d", hours, minutes, seconds);
}

void game_result(const bool& win, const GuessTheWord& guess_the_word,
	const GallowsPicture& gallows_picture, const int& time_difference)
{
	system("cls");
	cout << "\n\t";
	if (win)
	{
		SetColor(LightGreen);
		cout << "Победа!";
	}
	else
	{
		SetColor(Red);
		cout << "Поражение!";
	}

	SetColor(White);
	gallows_picture.Show();
	cout << "\n\n\n";
	guess_the_word.ShowGuessWord();
	cout << endl;
	guess_the_word.ShowWrongGuesses();
	cout << endl;
	show_game_time(time_difference);
	cout << "\nКоличество попыток: " << guess_the_word.GetErrorsCount();
	cout << "\nИскомое слово: " << guess_the_word.GetWord();
	cout << "\n\n\n" << press_any_key;
	my_getch();
}

void to_upper(char& letter)
{
	if (letter >= 'а' && letter <= 'я')
	{
		letter -= 32;
	}
}