#pragma once

enum
{
	Mix = 30, Big_board_size = 16, Small_board_size = 9, High_big_board = 15, High_small_board = 8,
	Big_board_step = 4, Small_board_step = 3, Up = -72, Down = -80, Left = -75, Right = -77, Succes = 1,
	Any_dir = 4
};

enum { LightGreen = 10, Red = 4, Orange = 6, LightGray = 7, White = 15, Gray = 8, Vanil = 14 };


void init(short* m, const bool big_board);
void show_big(const short* m);
void show_small(const short* m);
void mix(short* m, const bool big_board);
short manual_mix(short* m, const bool big_board);

short find_space(const short* m);
void check_turn(const bool big_board, const short current, bool& up, bool& down, bool& left, bool& right);
short turn(short* m, short& current, const bool big_board, const bool up, const bool down, const bool left, const bool right);
short comp_turn(short* m, short& current, const bool big_board, const bool up, const bool down, const bool left, const bool right);
bool check_win(const short* m, const short* win, const bool big_board);

void game(short* m, const short* m_win, const bool big_board, const bool player);