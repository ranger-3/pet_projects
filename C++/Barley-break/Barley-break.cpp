#include <iostream>
#include <conio.h>
#include "func.h"
#include "BB_func.h"

using namespace std;

int main()
{
	system("chcp 1251>NULL");
	srand(time(NULL));

	bool big_board, player;
	char key;
	short m[Big_board_size], win_board[Big_board_size];
	short menu_point, who_collect_point, mix_point, manual_mix_point, step, current;
	
	big_board = player = true;
	init(win_board, big_board);

	do
	{
		who_collect_point = Exit;
		mix_point = Exit;
		menu_point = main_menu();

		if (menu_point != Exit)
		{
			if (menu_point == Small_board_point)
			{
				big_board = false;
			}
			else if (menu_point == Big_board_point)
			{
				big_board = true;
			}

			who_collect_point = who_collect_menu();
		}

		if (who_collect_point == Exit)
		{
			continue;
		}

		mix_point = mix_menu();
		init(m, big_board);

		if (mix_point == Exit)
		{
			continue;
		}
		else if (mix_point == Manual_mix)
		{
			manual_mix_point = manual_mix(m, big_board);

			if (manual_mix_point == Exit)
			{
				continue;
			}
		}
		else if (mix_point == Computer_mix)
		{
			mix(m, big_board);
		}

		if (who_collect_point != Exit)
		{
			if (who_collect_point == Player_collecting)
			{
				player = true;
			}
			else if (who_collect_point == Computer_collecting)
			{
				player = false;
			}
			game(m, win_board, big_board, player);
		}


	} while (menu_point != Exit);




	_getch();
	return 0;
}