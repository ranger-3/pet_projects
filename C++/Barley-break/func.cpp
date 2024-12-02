#include <iostream>
#include <conio.h>
#include "func.h"
#include "BB_func.h"
#include "color.h"

using namespace std;

int my_getch()
{
	int ch = _getch();
	if (ch == 224) {
		ch = _getch();
		return -ch;
	}
	return ch;
}

int rand_num(int a, int b)
{
	if (a > b)
		swap(a, b);
	return rand() % (b - a + 1) + a;
}

short change_menu_point(int key, short current, const short last_point)
{
	if (key == Up)
	{
		if (current == First_point)
		{
			current = last_point;
		}
		else
		{
			current--;
		}
	}
	else if (key == Down)
	{
		if (current == last_point)
		{
			current = First_point;
		}
		else
		{
			current++;
		}
	}

	return current;
}

short main_menu()
{
	short current = 1;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\tВыбор режима игры:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "8  (3.3)";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "15 (4.4)";

		

		SetColor(Vanil);
		cout << "\n\n\n\n\t(Enter) Выбрать пункт ";

		SetColor(Orange);
		cout << "\n\n\t(Esc) Выход из программы ";

		key = my_getch();
		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, Second_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Small_board_point;
			}
			else if (current == Second_point)
			{
				return Big_board_point;
			}
		}


	} while (key != Esc);

	return Exit;
}

short who_collect_menu()
{
	short current = 1;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\tРежим игры:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "Человек собирает";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "Компьютер собирает";

		SetColor(Orange);
		cout << "\n\n\n\t(Esc) Выход в главное меню ";

		key = my_getch();
		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, Second_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Player_collecting;
			}
			else if (current == Second_point)
			{
				return Computer_collecting;
			}
		}


	} while (key != Esc);

	return Exit;
}

short mix_menu()
{
	short current = 1;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\tНачальное размешивание пятнашек:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "Ручное размешивание";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "Компьютерное размешивание";

		SetColor(Orange);
		cout << "\n\n\n\t(Esc) Выход в главное меню ";

		key = my_getch();
		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, Second_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Manual_mix;
			}
			else if (current == Second_point)
			{
				return Computer_mix;
			}
		}


	} while (key != Esc);

	return Exit;
}

void game_info(const int turns, const bool player)
{
	SetColor(LightGray);
	cout << "\n\n\n\t\tХодов: " << turns;
	cout << "\n\n\n\t\t";
	player ? cout << "(Стрелки) управление" : cout << "(Space) следующий ход";
	SetColor(Orange);
	cout << "\n\n\t\t(Esc) Выход в главное меню ";
}