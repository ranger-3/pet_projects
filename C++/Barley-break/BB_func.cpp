#include <iostream>
#include <iomanip>
#include <time.h>
#include "func.h"
#include "BB_func.h"
#include "color.h"

using namespace std;

void init(short* m, const bool big_board)
{
	short i, high_value;

	high_value = big_board ? High_big_board : High_small_board;

	for (i = 0; i < high_value; i++, m++)
	{
		*m = i + 1;
	}
	*m = 0;
}

void show_big(const short* m)
{
	short i, j;

	SetColor(Orange);
	cout << "\n\n\n\t\t";
	cout << "---------------------" << endl;
	cout << "\t\t";
	for (i = 0, j = 1; i < Big_board_size; i++, j++, m++)
	{
		if (*m == 0)
		{
			SetColor(Orange);
			cout << "| ";
			SetColor(LightGreen);
			cout << "__ ";
		}
		else
		{
			SetColor(Orange);
			cout << "| " << setw(2);
			SetColor(LightGray);
			cout << *m << ' ';
		}
		if (j == Big_board_step)
		{
			SetColor(Orange);
			cout << "|" << endl;
			cout << "\t\t---------------------";
			cout << endl << "\t\t";
			j = 0;
		}
	}
}

void show_small(const short* m)
{
	short i, j;

	SetColor(Orange);
	cout << "\n\n\n\t\t";
	cout << "-------------" << endl;
	cout << "\t\t";
	for (i = 0, j = 1; i < Small_board_size; i++, j++, m++)
	{
		if (*m == 0)
		{
			SetColor(Orange);
			cout << "| ";
			SetColor(LightGreen);
			cout << "_ ";
		}
		else
		{
			SetColor(Orange);
			cout << "| ";
			SetColor(LightGray);
			cout << *m << ' ';
		}
		if (j == Small_board_step)
		{
			SetColor(Orange);
			cout << "|" << endl;
			cout << "\t\t-------------";
			cout << endl << "\t\t";
			j = 0;
		}
	}
}

void mix(short* m, const bool big_board)
{
	short i, a, b, high_value;

	high_value = big_board ? High_big_board : High_small_board;

	for (i = 0; i < Mix; i++)
	{
		a = rand_num(0, high_value);
		b = rand_num(0, high_value);
		swap(m[a], m[b]);
	}
}

short manual_mix(short* m, const bool big_board)
{
	short i, a, b, high_value;
	char key;

	high_value = big_board ? High_big_board : High_small_board;

	mix(m, big_board);
	do
	{
		system("cls");
		big_board ? show_big(m) : show_small(m);
		SetColor(LightGray);
		cout << "\n\n\n\t\t(Space) перемешать";
		cout << "\n\n\t\t(Enter) принять";
		SetColor(Orange);
		cout << "\n\n\t\t(Esc) Выход в главное меню";
		key = my_getch();
		if (key == Space)
		{
			for (i = 0; i < Mix; i++)
			{
				a = rand_num(0, high_value);
				b = rand_num(0, high_value);
				swap(m[a], m[b]);
			}
		}
		else if (key == Enter)
		{
			return Succes;
		}
	} while (key != Esc);

	return Exit;
}

short find_space(const short* m)
{
	short i;

	for (i = 0; i < Big_board_size; i++, m++)
	{
		if (*m == 0)
			return i;
	}
	return 0;
}

void check_turn(const bool big_board, const short current, bool& up, bool& down, bool& left, bool& right)
{
	short step, high_board;

	if (big_board)
	{
		step = Big_board_step;
		high_board = High_big_board;
	}
	else
	{
		step = Small_board_step;
		high_board = High_small_board;
	}
	
	up = current - step >= 0 ? true : false;
	down = current + step <= high_board ? true : false;
	left = current % step ? true : false;
	right = (current + 1) % step ? true : false;
}

short turn(short* m, short& current, const bool big_board, const bool up, const bool down, const bool left, const bool right)
{
	char key;
	short step;
	step = big_board ? Big_board_step : Small_board_step;

	do
	{
		key = my_getch();

		if (up && key == Up)
		{
			swap(m[current], m[current - step]);
			current -= step;
			return Succes;
		}
		else if (down && key == Down)
		{
			swap(m[current], m[current + step]);
			current += step;
			return Succes;
		}
		else if (left && key == Left)
		{
			swap(m[current], m[current - 1]);
			current--;
			return Succes;
		}
		else if (right && key == Right)
		{
			swap(m[current], m[current + 1]);
			current++;
			return Succes;
		}
	} while (key != Esc);

	return Exit;
}

short comp_turn(short* m, short& current, const bool big_board, const bool up, const bool down, const bool left, const bool right)
{
	char key;
	short step, num;
	step = big_board ? Big_board_step : Small_board_step;

	do
	{
		key = my_getch();

		if (key == Space)
		{
			while (true)
			{
				num = rand_num(0, Any_dir);
				if (up && num == 0)
				{
					swap(m[current], m[current - step]);
					current -= step;
					return Succes;
				}
				else if (down && num == 1)
				{
					swap(m[current], m[current + step]);
					current += step;
					return Succes;
				}
				else if (left && num == 2)
				{
					swap(m[current], m[current - 1]);
					current--;
					return Succes;
				}
				else if (right && num == 3)
				{
					swap(m[current], m[current + 1]);
					current++;
					return Succes;
				}
			}
		}

	} while (key != Esc);

	return Exit;
}

bool check_win(const short* m, const short* win, const bool big_board)
{
	short i, high_value;

	high_value = big_board ? High_big_board : High_small_board;

	for (i = 0; i < high_value; i++, m++, win++)
	{
		if (*m != *win)
			return false;
	}
	return true;
}

void game(short* m, const short* m_win, const bool big_board, const bool player)
{
	bool up, down, left, right, win = false;
	short status, current;
	int hours, minutes, seconds, turns = 0;
	time_t start, end;
	void (*fptr_show)(const short*);
	short (*fptr_turn)(short*, short&, const bool, const bool, const bool, const bool, const bool);

	fptr_turn = player ? turn : comp_turn;
	fptr_show = big_board ? show_big : show_small;
	current = find_space(m);
	time(&start);
	do
	{
		system("cls");
		fptr_show(m);
		game_info(turns, player);

		check_turn(big_board, current, up, down, left, right);

		status = fptr_turn(m, current, big_board, up, down, left, right);


		if (status == Exit)
		{
			continue;
		}
		else if (check_win(m, m_win, big_board))
		{
			win = true;
			status = Exit;
			continue;
		}
		turns++;


	} while (status != Exit);

	time(&end);
	seconds = difftime(end, start);
	hours = seconds / 3600;
	seconds -= (hours * 3600);
	minutes = seconds / 60;
	seconds -= (minutes * 60);

	system("cls");
	fptr_show(m);
	SetColor(LightGray);
	cout << "\n\n\t\tХодов: " << turns;
	printf("\n\n\t\tЗатраченное время: %02d:%02d:%02d\n", hours, minutes, seconds);
	if (win)
	{
		SetColor(LightGreen);
		cout << "\n\n\t\tПобеда!";
	}
	SetColor(Orange);
	cout << "\n\n\n\t\tНажмите любую клавишу для продолжения";
	my_getch();
}