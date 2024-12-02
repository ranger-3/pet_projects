#include<iostream>
#include<conio.h>
#include "Board.h"
#include "Ship.h"
#include "Init_board.h"
#include "Status.h"
#include "func.h"
#include "color.h"

using namespace std;



int main()
{
	system("chcp 1251>NULL");
	srand(time(NULL));

	
	Ship* s1, *s2;
	Init_board** ib;
	Board** b1, ** b2;
	Status st1, st2;

	short menu_point, init_point, computer_point, game_mode, continue_game;
	bool inited, smart_mode, first_turn, show_all;

	continue_game = inited = smart_mode = false;
	first_turn = show_all = true;
	computer_point = Exit;
	game_mode = Exit;

	memory(ib);
	memory(b1);
	memory(b2);
	init(s1, Navy + 1);
	init(s2, Navy + 1);
	fill_ships(s1);
	fill_ships(s2);

	do
	{
		init_point = Exit;
		menu_point = main_menu(continue_game);
		if (!continue_game)
		{
			game_mode = menu_point;
		}

		if (menu_point == Player_computer || menu_point == Computer_computer)
		{
			continue_game = false;
			init_point = init_menu();
			if (init_point == Exit)
			{
				menu_point = No_point;
			}
		}

		if (init_point == Manual_init)
		{
			clear_init_board(ib);
			start_coord(s1);
			inited = manual_init(ib, s1);
			if (!inited)
				continue;
			if (menu_point == Player_computer)
			{
				clear_init_board(ib);
				random_init(ib, s2);
			}
			else if (menu_point == Computer_computer)
			{
				clear_init_board(ib);
				start_coord(s2);
				inited = manual_init(ib, s2);
				if (!inited)
					continue;
			}
		}
		else if (init_point == Random_init)
		{
			clear_init_board(ib);
			random_init(ib, s1);
			clear_init_board(ib);
			random_init(ib, s2);
		}

		if (init_point == Manual_init || init_point == Random_init)
		{
			clear_board(b1);
			clear_board(b2);
			init_board(b1, s1);
			init_board(b2, s2);
			clear_stats(st1, st2);
			first_turn = rand_num(0, 1);
			computer_point = computer_menu();
			if (computer_point == Random_AI)
			{
				smart_mode = false;
			}
			else if (computer_point == intellectual_AI)
			{
				smart_mode = true;
			}
			else if (computer_point == Exit)
			{
				menu_point = No_point;
			}
		}

		if (menu_point == Player_computer || menu_point == Continue_game && game_mode == Player_computer)
		{
			game(b1, b2, s1, s2, st1, st2, continue_game, smart_mode);
		}
		else if (menu_point == Computer_computer || menu_point == Continue_game && game_mode == Computer_computer)
		{
			bot_game(b1, b2, s1, s2, st1, st2, smart_mode, show_all, first_turn, continue_game);
		}


	} while (menu_point != Exit);

	destroy(s1);
	destroy(s2);
	destroy(ib);
	destroy(b1);
	destroy(b2);

	_getch();
	return 0;
}