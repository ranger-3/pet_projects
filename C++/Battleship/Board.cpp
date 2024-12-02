#include <iostream>
#include "Board.h"
#include "Init_board.h"
#include "func.h"
#include "color.h"

using namespace std;

void memory(Board**& b)
{
	int i;
	b = new Board *[Board_size];
	for (i = 0; i < Board_size; i++)
	{
		b[i] = new Board[Board_size];
	}	
}

void destroy(Board**& b)
{
	int i;
	for (i = 0; i < Board_size; i++)
	{
		delete[]b[i];
	}
	delete[]b;
	b = nullptr;
}

void clear_board(Board**& b)
{
	short i, j;
	for (i = 0; i < Board_size; i++)
	{
		for (j = 0; j < Board_size; j++)
		{
			b[i][j].ship = 0;
			b[i][j].dead = false;
			b[i][j].fired = false;
			b[i][j].last_fire = false;
		}
	}
}

void init_board(Board**& b, Ship*& s)
{
	short i, j, k, d, c1, c2, ship_size;

	for (i = 0; i < Navy; i++)
	{
		ship_size = s[i].size;
		for (j = k = 0, d = 1; j < ship_size; j++, k += 2, d += 2)
		{
			c1 = s[i].coord[k];
			c2 = s[i].coord[d];
			b[c1][c2].ship = i + 1;
		}
	}
}

void show_line(Board**& b, const short line, bool show_ship)
{
	short i;
	bool last_fire;
	SetColor(Orange);
	cout << "\t\t" << line << "  ";
	for (i = 0; i < Board_size; i++)
	{
		last_fire = b[line][i].last_fire;
		last_fire ? SetColor(LightGreen) : SetColor(Red);

		if (b[line][i].ship && b[line][i].dead)
		{
			cout << 'X';
		}
		else if (b[line][i].ship && b[line][i].fired)
		{
				cout << '/';
		}
		else if (b[line][i].fired)
		{
			last_fire ? SetColor(LightGreen) : SetColor(LightGray);
			cout << '|';
		}
		else if (show_ship && b[line][i].ship)
		{
			SetColor(LightGray);
			cout << 'X';
		}
		else
		{
			SetColor(LightGray);
			cout << '.';
		}


		cout << ' ';
	}
}

void show_boards(Board**& b1, Board**& b2, bool show_both)
{
	short i;
	char ch = 'A';

	system("cls");

	cout << "\n\n\n";

	letter_line();
	cout << '\t';
	letter_line();
	cout << endl;

	for (i = 0; i < Board_size; i++)
	{
		show_line(b1, i);
		cout << '\t';
		show_line(b2, i, show_both);
		cout << endl;
	}

}

short get_coords(short& coord1, short& coord2)
{
	char c1, c2;

	SetColor(White);
	cout << "\nВведите координаты для выстрела: ";

	c1 = my_getch();
	cout << c1 << ' ';
	if (c1 == Esc)
		return Exit;

	c2 = my_getch();
	if (c2 == Esc)
		return Exit;



	if (c1 >= 'A' && c1 <= 'J' || c1 >= 'a' && c1 <= 'j')
	{
		swap(c1, c2);
	}

	if (c1 >= '0' && c1 <= '9')
	{
		c1 -= '0';
	}
	else
	{
		return Wrong;
	}

	if (c2 >= 'A' && c2 <= 'J')
	{
		c2 -= 'A';
	}
	else if (c2 >= 'a' && c2 <= 'j')
	{
		c2 -= 'a';
	}
	else if (c2 >= '0' && c2 <= '9')
	{
		c2 -= '0';
	}

	if (c2 < 0 || c2 > 9)
	{
		return Wrong;
	}

	coord1 = c1;
	coord2 = c2;

	return Succes;
}

bool check_if_dead(Board**& b, Ship*& s, const short coord1, const short coord2)
{
	short c1, c2, i, j, k, size, current;
	current = b[coord1][coord2].ship - 1;
	size = s[current].size;
	
	for (i = j = 0, k = 1; i < size; i++, j += 2, k += 2)
	{
		c1 = s[current].coord[j];
		c2 = s[current].coord[k];

		if (!b[c1][c2].fired)
		{
			return false;
		}
	}
	return true;
}

void put_dead(Board**& b, Ship*& s, Status& st, const short coord1, const short coord2)
{
	short c1, c2, i, j, k, size, current;
	current = b[coord1][coord2].ship - 1;
	size = s[current].size;

	for (i = j = 0, k = 1; i < size; i++, j += 2, k += 2)
	{
		c1 = s[current].coord[j];
		c2 = s[current].coord[k];

		b[c1][c2].dead = true;
	}
	s[current].dead = true;

	change_status(st, size);
}

void random_shot(Board**& b, short& c1, short& c2)
{
	bool shoot = true;

	while (shoot)
	{
		c1 = rand_num(Low_border, High_border);
		c2 = rand_num(Low_border, High_border);

		if (!b[c1][c2].fired)
		{
			return;
		}
	}

}

bool check_dir(Board**& b, bool& vertical, const short c1, const short c2)
{
	short t;

	if (c1 > 0)
	{
		t = c1 - 1;
		if (b[t][c2].fired && b[t][c2].ship)
		{
			vertical = true;
			return true;
		}
	}
	if (c1 < High_border)
	{
		t = c1 + 1;
		if (b[t][c2].fired && b[t][c2].ship)
		{
			vertical = true;
			return true;
		}
	}
	if (c2 > 0)
	{
		t = c2 - 1;
		if (b[c1][t].fired && b[c1][t].ship)
		{
			vertical = false;
			return true;
		}
	}
	if (c2 < High_border)
	{
		t = c2 + 1;
		if (b[c1][t].fired && b[c1][t].ship)
		{
			vertical = false;
			return true;
		}
	}
	return false;
}

void no_dir_shot(Board**& b, const short sm1, const short sm2, short& c1, short& c2)
{
	short t;

	if (sm1 > 0)
	{
		t = sm1 - 1;
		if (!b[t][sm2].fired)
		{
			c1 = t;
			c2 = sm2;
			return;
		}
	}
	if (sm1 < High_border)
	{
		t = sm1 + 1;
		if (!b[t][sm2].fired)
		{
			c1 = t;
			c2 = sm2;
			return;
		}
	}
	if (sm2 > 0)
	{
		t = sm2 - 1;
		if (!b[sm1][t].fired)
		{
			c1 = sm1;
			c2 = t;
			return;
		}
	}
	if (sm2 < High_border)
	{
		t = sm2 + 1;
		if (!b[sm1][t].fired)
		{
			c1 = sm1;
			c2 = t;
			return;
		}
	}
}

void dir_shot(Board**& b, bool vertical, const short sm1, const short sm2,  short& c1, short& c2)
{
	short t;
	if (vertical)
	{
		t = sm1;
		while (t > 0 && b[t][sm2].fired && b[t][sm2].ship)
		{
			t--;
			if (!b[t][sm2].fired)
			{
				c1 = t;
				c2 = sm2;
				return;
			}
		}

		t = sm1;
		while (t < High_border && b[t][sm2].fired && b[t][sm2].ship)
		{
			t++;
			if (!b[t][sm2].fired)
			{
				c1 = t;
				c2 = sm2;
				return;
			}
		}
	}
	else
	{
		t = sm2;
		while (t > 0 && b[sm1][t].fired && b[sm1][t].ship)
		{
			t--;
			if (!b[sm1][t].fired)
			{
				c1 = sm1;
				c2 = t;
				return;
			}
		}

		t = sm2;
		while (t < High_border && b[sm1][t].fired && b[sm1][t].ship)
		{
			t++;
			if (!b[sm1][t].fired)
			{
				c1 = sm1;
				c2 = t;
				return;
			}
		}
	}
}

void smart_shot(Board**& b, short& c1, short& c2, short& sm1, short& sm2)
{
	bool dir, vertical;

	dir = check_dir(b, vertical, sm1, sm2);
	if (dir)
	{
		dir_shot(b, vertical, sm1, sm2, c1, c2);
	}
	else
	{
		no_dir_shot(b, sm1, sm2, c1, c2);
	}
}


short shot(Board**& b, Ship*& s, Status& st, const short c1, const short c2)
{
	b[c1][c2].fired = true;

	if (b[c1][c2].ship)
	{
		if (check_if_dead(b, s, c1, c2))
		{
			put_dead(b, s, st, c1, c2);
			around_dead_ship(b, s, c1, c2);	
			return Killed;
		}
		return Shoot;
	}
	return End_turn;
}

void around_dead_ship(Board**& b, Ship*& s, const short coord1, const short coord2)
{
	short c1, c2, tmp, i, j, k, a, size, current, line = 3;
	current = b[coord1][coord2].ship - 1;
	size = s[current].size;



	for (i = j = 0, k = 1; i < size; i++, j += 2, k += 2)
	{
		c1 = s[current].coord[j] - 1;
		c2 = s[current].coord[k];

		for (a = 0; a < line; a++, c1++)
		{
			if (c1 >= 0 && c1 <= Board_size - 1)
			{
				b[c1][c2].fired = true;
				if (c2 > 0)
				{
					tmp = c2 - 1;
					b[c1][tmp].fired = true;
				}
				if (c2 < Board_size - 1)
				{
					tmp = c2 + 1;
					b[c1][tmp].fired = true;
				}
			}
		}
	}
}

void find_target(Board**& b, bool& target, short& sm1, short& sm2)
{
	short i, j;
	for (i = 0; i < Board_size; i++)
	{
		for (j = 0; j < Board_size; j++)
		{
			if (b[i][j].fired && b[i][j].ship && !b[i][j].dead)
			{
				target = true;
				sm1 = i;
				sm2 = j;
				return;
			}
		}
	}
	target = false;
}

void game(Board**& b1, Board**& b2, Ship*& s1, Ship*& s2, Status& st1, Status& st2, short& continue_game, bool smart_mode)
{
	bool game , player_win, computer_win, target, kill, first_turn;
	short shoot, status, last_shot_pl, last_shot_cp,
		pl1, pl2, cp1, cp2, sm1, sm2;

	cp1 = cp2 = pl1 = pl2 = 0;
	player_win = computer_win = target = false;
	last_shot_pl = last_shot_cp = End_turn;
	status = Succes;
	game = true;

	if (continue_game)
	{
		find_target(b1, target, sm1, sm2);
		first_turn = continue_game == Player_first ? true : false;
	}
	else
	{
		first_turn = rand_num(0, 1);
	}

	while (game)
	{
		if (first_turn)
		{
			shoot = Shoot;
			while (shoot)
			{
				show_boards(b1, b2);
				show_stats(st1, st2);

				if (last_shot_pl != End_turn)
				{
					kill = last_shot_pl == Killed ? true : false;
					pl_shot_message(kill);
				}

				player_turn_message();

				if (status == Wrong)
				{
					last_shot_pl = End_turn;
					wrong_coord_message();
				}
				else if (status == Already_fired)
				{
					last_shot_pl = End_turn;
					already_fired_message();
				}

				b2[pl1][pl2].last_fire = false;

				status = get_coords(pl1, pl2);
				if (status == Wrong)
				{
					continue;
				}
				else if (status == Exit)
				{
					b1[cp1][cp2].last_fire = false;
					continue_game = Player_first;
					return;
				}
				if (b2[pl1][pl2].fired)
				{
					status = Already_fired;
					continue;
				}

				shoot = shot(b2, s2, st2, pl1, pl2);
				last_shot_pl = shoot;
				b2[pl1][pl2].last_fire = true;
				if (st2.alive == All_dead)
				{
					player_win = true;
					shoot = false;
				}
			}
			if (player_win)
			{
				game = false;
				continue;
			}
		}

		shoot = Shoot;

		while (shoot)
		{
			if (last_shot_cp != End_turn)
			{
				show_boards(b1, b2);
				show_stats(st1, st2);
				kill = last_shot_cp == Killed ? true : false;
				cp_shot_message(kill);
				comp_turn_message();
				status = get_status();

				if (status == Exit)
				{
					b2[pl1][pl2].last_fire = false;
					b1[cp1][cp2].last_fire = false;
					continue_game = Comp_first;
					return;
				}
			}

			b1[cp1][cp2].last_fire = false;

			if (smart_mode)
			{
				if (target)
				{
					smart_shot(b1, cp1, cp2, sm1, sm2);
				}
				else
				{
					random_shot(b1, cp1, cp2);
				}
			}
			else
			{
				random_shot(b1, cp1, cp2);
			}

			shoot = shot(b1, s1, st1, cp1, cp2);
			last_shot_cp = shoot;
			if (smart_mode)
			{
				if (shoot == Killed)
				{
					target = false;
				}
				else if (shoot == Shoot)
				{
					sm1 = cp1;
					sm2 = cp2;
					target = true;
				}
			}

			if (st1.alive == All_dead)
			{
				computer_win = true;
				shoot = false;
			}

			b1[cp1][cp2].last_fire = true;
		}
	
		if (computer_win)
		{
			game = false;
		}
		first_turn = true;
	}

	if (player_win || computer_win)
	{
		show_boards(b1, b2);
		show_stats(st1, st2);
		cout << "\n\n\n\t\t";
		if (player_win)
		{
			SetColor(LightGreen);
			cout << "Вы выиграли!";
		}
		else if (computer_win)
		{
			SetColor(Red);
			cout << "Вы проиграли";
		}

		SetColor(Orange);
		cout << "\n\n\t\t(Esc) или (Enter) для возврата в меню ";
		do
		{
			status = my_getch();

		} while (status != Esc && status != Enter);

		continue_game = false;
	}
}

void bot_game(Board**& b1, Board**& b2, Ship*& s1, Ship*& s2, Status& st1, Status& st2, bool smart_mode, bool show_all, bool& first_turn, short& continue_game)
{
	char key;
	bool game, first_win, second_win, target_1, target_2, first, second;
	short shoot, status, last_shot1, last_shot2,
		a1, a2, c1, c2, am1, am2, sm1, sm2;

	a1 = a2 = c1 = c2 = 0;
	first_win = second_win = target_1 = target_2 = second = false;
	last_shot1 = last_shot2 = End_turn;
	game = first = true;
	status = Exit;


	if (continue_game)
	{
		find_target(b2, target_1, am1, am2);
		find_target(b1, target_2, sm1, sm2);
		first_turn = continue_game == Comp_1 ? true : false;
	}
	else
	{
		first_turn = rand_num(0, 1);
	}

	while (game)
	{
		if (first_turn)
		{
			shoot = Shoot;
			while (shoot)
			{
				show_boards(b1, b2, show_all);
				show_stats(st1, st2);
				b2[a1][a2].last_fire = false;
				if (last_shot1 == Shoot)
				{
					damage_ship_message(first);
				}
				else if (last_shot1 == Killed)
				{
					kill_ship_message(first);
				}
				bot_info(first);

				status = get_status();

				if (status == Exit)
				{
					b1[c1][c2].last_fire = false;
					continue_game = Comp_1;
					return;
				}

				if (smart_mode)
				{
					if (target_1)
					{
						smart_shot(b2, a1, a2, am1, am2);
					}
					else
					{
						random_shot(b2, a1, a2);
					}
				}
				else
				{
					random_shot(b2, a1, a2);
				}

				shoot = shot(b2, s2, st2, a1, a2);
				last_shot1 = shoot;

				b2[a1][a2].last_fire = true;

				if (smart_mode)
				{
					if (shoot == Killed)
					{
						target_1 = false;
					}
					else if (shoot == Shoot)
					{
						am1 = a1;
						am2 = a2;
						target_1 = true;
					}
				}

				if (st2.alive == All_dead)
				{
					first_win = true;
					shoot = false;
				}
			}
			if (first_win)
			{
				game = false;
				continue;
			}
		}


		shoot = Shoot;

		while (shoot)
		{
			show_boards(b1, b2, show_all);
			show_stats(st1, st2);
			b1[c1][c2].last_fire = false;
			if (last_shot2 == Shoot)
			{
				damage_ship_message(second);
			}
			else if (last_shot2 == Killed)
			{
				kill_ship_message(second);
			}
			bot_info(second);

			status = get_status();

			if (status == Exit)
			{
				b2[a1][a2].last_fire = false;
				first_turn = false;
				continue_game = Comp_2;
				return;
			}

			if (smart_mode)
			{
				if (target_2)
				{
					smart_shot(b1, c1, c2, sm1, sm2);
				}
				else
				{
					random_shot(b1, c1, c2);
				}
			}
			else
			{
				random_shot(b1, c1, c2);
			}

			shoot = shot(b1, s1, st1, c1, c2);
			last_shot2 = shoot;

			if (smart_mode)
			{
				if (shoot == Killed)
				{
					target_2 = false;
				}
				else if (shoot == Shoot)
				{
					sm1 = c1;
					sm2 = c2;
					target_2 = true;
				}
			}
			if (st1.alive == All_dead)
			{
				second_win = true;
				shoot = false;
			}
			b1[c1][c2].last_fire = true;
		}

		if (second_win)
		{
			game = false;
		}
		first_turn = true;
	}

	if (first_win || second_win)
	{
		show_boards(b1, b2);
		show_stats(st1, st2);
		cout << "\n\n\n\t\t";
		SetColor(LightGreen);
		if (first_win)
		{
			cout << "Игрок 1 выиграл!";
		}
		else if (second_win)
		{
			cout << "Игрок 2 выиграл!";
		}

		SetColor(Orange);
		cout << "\n\n\t\t(Esc) или (Enter) для возврата в меню ";
		do
		{
			status = my_getch();

		} while (status != Esc && status != Enter);

		continue_game = Exit;
	}
}