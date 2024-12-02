#pragma once

enum
{
	Enter = 13, Esc = 27, Space = 32, Exit = 0, First_point = 1, Second_point = 2,
	Small_board_point = 1, Big_board_point = 2, Player_collecting = 1, Computer_collecting = 2,
	Manual_mix = 1, Computer_mix = 2
	
};

int my_getch();
int rand_num(int a, int b);
short main_menu();
short who_collect_menu();
short mix_menu();
void game_info(const int turns, const bool player);