#pragma once

enum
{
	Size_coord = 8, Single_deck = 4, Two_deck = 3,
	Three_deck = 2, Four_deck = 1, Navy = 10,
	Middle = 5, Four_deck_size = 4, Three_deck_size = 3,
	Two_deck_size = 2, Single_deck_size = 1, First_ship = 48, Last_ship = 57
};

struct Ship
{
	short size = 1;
	short coord[Size_coord] = { 0 };
	bool dead = true;
};

void init(Ship*& s, const int size);
void destroy(Ship*& s);
void clear_ships(Ship*& s);
void start_coord(Ship*& s);
void start_coord_ship(Ship& s);
void fill_ships(Ship*& s);
void string_ship(Ship const s, short const num, short const current);

void change_coord(Ship& s, short const c1, short const c2);
bool check_border(Ship const s, short const dir);
void rotate_ship(Ship& s);
int change_current(Ship*& s);
bool board_ready(Ship*& s);
