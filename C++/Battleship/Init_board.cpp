#include <iostream>
#include "func.h"
#include "Init_board.h"
#include "color.h"

using namespace std;

void memory(Init_board**& ib)
{
	int i;
	ib = new Init_board *[Board_size];
	for (i = 0; i < Board_size; i++)
	{
		ib[i] = new Init_board[Board_size];
	}	
}

void destroy(Init_board**& ib)
{
	int i;
	for (i = 0; i < Board_size; i++)
	{
		delete[]ib[i];
	}
	delete[]ib;
	ib = nullptr;
}

void letter_line()
{
	short i;
	char ch = 'A';
	cout << "\t\t   ";
	for (i = 0; i < Board_size; i++, ch++)
	{
		SetColor(Orange);
		cout << ch << ' ';
	}
}


void show(Init_board**& ib, Ship*& s, const short current_ship)
{
	short i, j;
	char ch = 'A';

	cout << "\n\n\n";
	letter_line();
	cout << endl;

	for (i = 0; i < Board_size; i++)
	{
		SetColor(Orange);
		cout << "\t\t" << i << "  ";
		for (j = 0; j < Board_size; j++)
		{
			if (ib[i][j].current_ship_near)
			{
				SetColor(Red);
				cout << 'X';
			}
			else if (ib[i][j].current)
			{
				SetColor(LightGreen);
				cout << 'X';
			}
			else if (ib[i][j].ship)
			{
				SetColor(White);
				cout << 'X';
			}
			else
			{
				SetColor(White);
				cout << '.';
			}
			cout << ' ';
		}
		
		string_ship(s[i], i, current_ship);
	}
}

bool check_around(Init_board**& ib, Ship const s)
{
	short i, j, k, a, c1, c2, t2;

	for (i = j = 0, k = 1; i < s.size; i++, j += 2, k += 2)
	{
		c1 = s.coord[j] - 1;
		c2 = s.coord[k];

		for (a = 0; a < 3; a++, c1++)
		{
			if (c1 >= 0 && c1 <= Board_size - 1)
			{
				if (ib[c1][c2].ship)
					return true;
				if (c2 > 0)
				{
					t2 = c2 - 1;
					if (ib[c1][t2].ship)
						return true;
				}
				if (c2 < Board_size - 1)
				{
					t2 = c2 + 1;
					if (ib[c1][t2].ship)
						return true;
				}
			} 
		}
	} 

	return false;
}



void put_current(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].current = true;
}

void clear_current(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].current = false;
}

void put_ship(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].ship = true;
}

void clear_ship(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].ship = false;
}

void put_ship_near(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].current_ship_near = true;
}

void clear_ship_near(Init_board**& ib, const short c1, const short c2)
{
	ib[c1][c2].current_ship_near = false;
}

void put_status(Init_board**& ib, Ship& s, void (*fptr)(Init_board**&, short const, short const))
{
	short i, j, k, c1, c2;

	for (i = j = 0, k = 1; i < s.size; i++, j += 2, k += 2)
	{
		c1 = s.coord[j];
		c2 = s.coord[k];	
		(*fptr)(ib, c1, c2);
	}
}

bool manual_init(Init_board**& ib, Ship*& s)
{
	short current = 0;
	bool ship_near;
	char key;

	void (*fptr_ib)(Init_board**&, short const, short const);
	clear_ships(s);

	do
	{
		system("cls");

		if (check_around(ib, s[current]))
		{
			fptr_ib = put_ship_near;
			ship_near = true;
		}
		else
		{
			fptr_ib = put_current;
			ship_near = false;
		}

		put_status(ib, s[current], fptr_ib);
		show(ib, s, current);
		init_info(current);
		fptr_ib = ship_near ? clear_ship_near : clear_current;
		put_status(ib, s[current], fptr_ib);
		key = my_getch();

		switch (key)
		{
		case Up:
			if (check_border(s[current], Up))
				change_coord(s[current], -1, 0);
			break;
		case Down:
			if (check_border(s[current], Down))
				change_coord(s[current], 1, 0);
			break;
		case Left:
			if (check_border(s[current], Left))
				change_coord(s[current], 0, -1);
			break;
		case Right:
			if (check_border(s[current], Right))
				change_coord(s[current], 0, 1);
			break;
		case Space:
			rotate_ship(s[current]);
			break;
		case 'r': case 'R': case 'к': case 'К':
			clear_init_board(ib);
			random_init(ib, s);
			current = change_current(s);
			break;
		case 's': case 'S': case 'ы': case 'Ы':
			if (current == Navy)
				return true;
		case Enter:
			if (ship_near)
				continue;
			fptr_ib = put_ship;
			put_status(ib, s[current], fptr_ib);
			s[current].dead = false;
			current = change_current(s);
			if (s[current].dead)
			{
				start_coord_ship(s[current]);
			}
		}
		
		if (key >= First_ship && key <= Last_ship)
		{
			current = key - 48;
			if (s[current].dead)
			{
				start_coord_ship(s[current]);
			}
			else
			{
				s[current].dead = true;
				fptr_ib = clear_ship;
				put_status(ib, s[current], fptr_ib);
			}
		}

	} while (key != Esc);

	return false;
}

void clear_init_board(Init_board**& ib)
{
	short i, j;
	for (i = 0; i < Board_size; i++)
	{
		for (j = 0; j < Board_size; j++)
		{
			ib[i][j].ship = false;
		}
	}
}

void random_init(Init_board**& ib, Ship*& s)
{
	short i, j, k, d, ship_size;
	int c1, c2, high_border;
	bool init, vertical;

	for (i = 0; i < Navy; i++)
	{
		init = true;
		ship_size = s[i].size;
		high_border = High_border - ship_size + 1;

		while (init)
		{
			vertical = rand_num(0, 1);
			
			if (vertical)
			{
				c1 = rand_num(Low_border, high_border);
				c2 = rand_num(Low_border, High_border);
			}
			else
			{
				c1 = rand_num(Low_border, High_border);
				c2 = rand_num(Low_border, high_border);
			}
	
			for (j = k = 0, d = 1; j < ship_size; j++, k += 2, d += 2)
			{
				s[i].coord[k] = c1;
				s[i].coord[d] = c2;
				vertical ? c1++ : c2++;
			}

			if (!check_around(ib, s[i]))
			{
				put_status(ib, s[i], put_ship);
				s[i].dead = false;
				init = false;
			}	
		}
	}
}

void init_info(short current)
{
	SetColor(LightGray);
	cout << "\n\n\n\n\n\t\t(Стрелки) перемещение корабля";
	cout << "\n\t\t(Пробел)  повернуть корабль";
	cout << "\n\t\t(Цифра)   изменить текущий корабль";
	cout << "\n\t\t(R)       случайная расстановка кораблей";
	
	if (current == Navy)
	{
		SetColor(LightGreen);
	}
	cout << "\n\n\t\t(S)   Начать игру";
	SetColor(Orange);
	cout << "\n\n\t\t(Esc) возврат в меню";
}