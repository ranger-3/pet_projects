#pragma once
#include "Ship.h"
#include "Status.h"


enum
{
	Empty = 0, Fired = 1, Enter = 13, Esc = 27, Space = 32, Board_size = 10,
	Shoot = 1, End_turn = 0, All_dead = 0, Win = 2, Killed = 2, Already_fired = 3,
	Player_first = 1, Comp_first = 2, Comp_1 = 1, Comp_2 = 2
};

enum {LightGreen = 10, Red = 4, Orange = 6, LightGray = 7, White = 15, Gray = 8, Vanil = 14};

struct Board
{
	short ship = 0;
	bool fired = false;
	bool dead = false;
	bool last_fire = false;
};

void memory(Board**& b);
void destroy(Board**& b);
void clear_board(Board**& b);

void show_line(Board**& b, const short line, bool show_ship = true);

void init_board(Board**& b, Ship*& s);
void show_boards(Board**& b1, Board**& b2, bool show_both = false);

bool check_if_dead(Board**& b, Ship*& s, const short coord1, const short coord2);
void put_dead(Board**& b, Ship*& s, Status& st, const short coord1, const short coord2);
void around_dead_ship(Board**& b, Ship*& s, const short coord1, const short coord2);

bool check_dir(Board**& b, bool& vertical, const short c1, const short c2);
void no_dir_shot(Board**& b, const short sm1, const short sm2, short& c1, short& c2);
void dir_shot(Board**& b, bool vertical, const short sm1, const short sm2, short& c1, short& c2);


short get_coords(short& coord1, short& coord2);
void random_shot(Board**& b, short& c1, short& c2);
void smart_shot(Board**& b, short& c1, short& c2, short& sm1, short& sm2);
short shot(Board**& b, Ship*& s, Status& st, short c1, short c2);
void find_target(Board**& b, bool& target, short& sm1, short& sm2);
void game(Board**& b1, Board**& b2, Ship*& s1, Ship*& s2, Status& st1, Status& st2, short& continue_game, bool smart_mode = false);
void bot_game(Board**& b1, Board**& b2, Ship*& s1, Ship*& s2, Status& st1, Status& st2, bool smart_mode, bool show_all, bool& first_turn, short& continue_game);