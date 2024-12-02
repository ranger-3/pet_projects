#pragma once

enum
{
	Exit = 0, First_point = 1, Second_point = 2, Third_point = 3,
	Player_computer = 1, Computer_computer = 2, Continue_game = 3,
	Manual_init = 1, Random_init = 2, Random_AI = 1, intellectual_AI = 2,
	Succes = 1, Wrong = 2, No_point = 5
};

int my_getch();
int rand_num(int a, int b);
short change_menu_point(int dir, short current, const short last_point);
short main_menu(short& continue_game);
short init_menu();
short computer_menu();
char get_status();
void bot_info(const bool first);
void kill_ship_message(bool first);
void damage_ship_message(bool first);
void pl_shot_message(const bool kill);
void cp_shot_message(const bool kill);
void comp_turn_message();
void player_turn_message();
void wrong_coord_message();
void already_fired_message();