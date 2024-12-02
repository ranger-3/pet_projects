#include <iostream>
#include "Ship.h"
#include "Init_board.h"
#include "Board.h"
#include "color.h"

using namespace std;

void init(Ship*& s, const int size)
{
	s = new Ship[size];
}

void destroy(Ship*& s)
{
	delete[]s;
	s = nullptr;
}

void clear_ships(Ship*& s)
{
	short i;
	for (i = 0; i < Navy; i++)
	{
		s[i].dead = true;
	}
}

void start_coord(Ship*& s)
{
	short i, j, k, d, c1, c2, size;

	c2 = Middle;

	for (k = 0; k < Navy; k++)
	{
		size = s[k].size;

		if (size == Four_deck_size)
		{
			c1 = Middle - 2;
		}
		else if (size == Three_deck_size || size == Two_deck_size)
		{
			c1 = Middle - 1;
		}
		else
		{
			c1 = Middle;
		}


		for (i = j = 0, d = 1; i < size; i++, c1++, j += 2, d += 2)
		{
			s[k].coord[j] = c1;
			s[k].coord[d] = c2;
		}
	}
}

void start_coord_ship(Ship& s)
{
	short i, j, d, c1, c2, size;

	size = s.size;
	c2 = Middle;

	if (size == Four_deck_size)
	{
		c1 = Middle - 2;
	}
	else if (size == Three_deck_size || size == Two_deck_size)
	{
		c1 = Middle - 1;
	}
	else
	{
		c1 = Middle;
	}

	for (i = j = 0, d = 1; i < size; i++, c1++, j += 2, d += 2)
	{
		s.coord[j] = c1;
		s.coord[d] = c2;
	}
}

void fill_ships(Ship*& s)
{
	int i, j;
	s[0].size += 3;

	for (i = 0, j = 1; i < Three_deck; i++, j++)
	{
		s[j].size += 2;
	}

	for (i = 0, j = 3; i < Two_deck; i++, j++)
	{
		s[j].size += 1;
	}
	s[Navy].size = 0;
}

void string_ship(Ship const s, short const num, short const current)
{
	int k;
	k = s.size;
	SetColor(LightGray);
	if (num == current)
	{
		SetColor(LightGreen);
	}
	cout << "\t\t(" << num << ") ";
	if (k == Four_deck_size)
	{
		cout << "Линкор   ";
	}
	else if (k == Three_deck_size)
	{
		cout << "Крейсер  ";
	}
	else if (k == Two_deck_size)
	{
		cout << "Эсминец  ";
	}
	else
	{
		cout << "Катер    ";
	}

	if (s.dead)
	{
		cout << "нет позиции";
	}
	cout << endl;
}

void change_coord(Ship& s, short const c1, short const c2)
{
	short i, j, d;
	
	for (i = j = 0, d = 1; i < s.size; i++, j += 2, d += 2)
	{

		s.coord[j] += c1;
		s.coord[d] += c2;
	}
}

bool check_border(Ship const s, short const dir)
{
	short max;
	if (dir == Up)
	{
		if (s.coord[0] == Low_border)
			return false;
	}
	else if (dir == Down)
	{
		max = (s.size * 2) - 2;
		if (s.coord[max] == High_border)
			return false;
	}
	else if (dir == Left)
	{
		if (s.coord[1] == Low_border)
			return false;
	}
	else if (dir == Right)
	{
		max = (s.size * 2) - 1;
		if (s.coord[max] == High_border)
			return false;
	}
	return true;
}

void rotate_ship(Ship& s)
{
	short i, j, k, c1, c2;
	bool vertical;

	vertical = s.coord[0] == s.coord[2] ? false : true;

	c1 = s.coord[0];

	if (vertical)
	{
		c2 = s.coord[1] - s.size + 1;
		if (c2 < 0)
		{
			c2 = 0;
		}
	}
	else
	{
		c2 = s.coord[1] + s.size - 1;
		if (c1 + s.size - 1 > High_border)
		{
			c1 = High_border - s.size + 1;
		}

	}

	for (i = j = 0, k = 1; i < s.size; i++, j += 2, k += 2)
	{
		s.coord[j] = c1;
		s.coord[k] = c2;
		vertical ? c2++ : c1++;
	}
}

int change_current(Ship*& s)
{
	short i;
	for (i = 0; i < Navy; i++)
	{
		if (s[i].dead)
			return i;
	}
	return Navy;
}

bool board_ready(Ship*& s)
{
	short i;
	for (i = 0; i < Navy; i++)
	{
		if (s[i].dead)
			return false;
	}
	return true;
}