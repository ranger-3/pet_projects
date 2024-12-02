#pragma once
#include "Board.h"
#include "Ship.h"

enum
{
	Up = -72, Down = -80, Left = -75, Right = -77, Low_border = 0, High_border = 9
};

struct Init_board
{
	bool current = false;
	bool ship = false;
	bool current_ship_near = false;
};

void memory(Init_board**& ib);
void destroy(Init_board**& ib);
void show(Init_board**& ib, Ship*& s, const short current_ship);

void letter_line();

bool check_around(Init_board**& ib, Ship const s);

void put_current(Init_board**& ib, const short c1, const short c2);
void clear_current(Init_board**& ib, const short c1, const short c2);
void put_ship(Init_board**& ib, const short c1, const short c2);
void clear_ship(Init_board**& ib, const short c1, const short c2);
void put_ship_near(Init_board**& ib, const short c1, const short c2);
void clear_ship_near(Init_board**& ib, const short c1, const short c2);

void put_status(Init_board**& ib, Ship& s, void (*fptr)(Init_board**&, short const, short const));
void clear_init_board(Init_board**& ib);
void random_init(Init_board**& ib, Ship*& s);
bool manual_init(Init_board**& ib, Ship*& s);
void init_info(short current);
