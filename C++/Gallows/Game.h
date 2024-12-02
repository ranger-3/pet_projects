#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include "Dictionary.h"
#include "GallowsPicture.h"
#include "GuessTheWord.h"
#include "Menu.h"

using namespace std;

int my_getch();
void save_dictionary(const Dictionary& dictionary);
void read_dictionary(Dictionary& dictionary);
void main_menu(Dictionary& dictionary);
void game(GallowsPicture& gallows_picture, const string& word);
bool is_letter(const int& letter);
void show_game_time(const int& time_difference);
void game_result(const bool& win, const GuessTheWord& guess_the_word, 
	const GallowsPicture& gallows_picture, const int& time_difference);
void to_upper(char& letter);