#include <iostream>
#include <conio.h>
#include "Init_board.h"
#include "color.h"
#include "func.h"


using namespace std;

int my_getch()
{
    int ch = _getch();
    if (ch == 224) {
        ch = _getch();
        return -ch;
    }
    return ch;
}

int rand_num(int a, int b)
{
    if (a > b)
        swap(a, b);
    return rand() % (b - a + 1) + a;
}

short change_menu_point(int key, short current, const short last_point)
{
	if (key == Up)
	{
		if (current == First_point)
		{
			current = last_point;
		}
		else
		{
			current--;
		}
	}
	else if (key == Down)
	{
		if (current == last_point)
		{
			current = First_point;
		}
		else
		{
			current++;
		}
	}

	return current;
}

short main_menu(short& continue_game)
{
	short current = 1, max_point;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\t����� ����:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "������� � ���������";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "��������� � ���������";

		if (continue_game)
		{
			max_point = Third_point;
			current == Third_point ? SetColor(LightGreen) : SetColor(LightGray);
			cout << "\n\n\t" << "���������� ���� ";
		}
		else
		{
			max_point = Second_point;
		}

		SetColor(Vanil);
		cout << "\n\n\n\n\t(Enter) ������� ����� ";

		SetColor(Orange);
		cout << "\n\n\t(Esc) ����� �� ��������� ";

		key = my_getch();
		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, max_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Player_computer;
			}
			else if (current == Second_point)
			{
				return Computer_computer;
			}
			else if (current == Third_point)
			{
				return Continue_game;
			}
		}


	} while (key != Esc);

	return Exit;
}

short init_menu()
{
	short max_point = Second_point, current = 1;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\t����������� ��������:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "���������� �������";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "��������� �����������";

		SetColor(Orange);
		cout << "\n\n\n\t(Esc) ��������� � ������� ���� ";

		key = my_getch();

		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, max_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Manual_init;
			}
			else if (current == Second_point)
			{
				return Random_init;
			}
		}

	} while (key != Esc);

	return Exit;
}

short computer_menu()
{
	short max_point = Second_point, current = 1;
	char key;
	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\n\t��������� ����� ������ � ���� �������:";
		current == First_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "��������� �������";
		current == Second_point ? SetColor(LightGreen) : SetColor(LightGray);
		cout << "\n\n\t" << "���������������� ����";

		SetColor(Orange);
		cout << "\n\n\n\t(Esc) ��������� � ������� ���� ";

		key = my_getch();

		if (key == Down || key == Up)
		{
			current = change_menu_point(key, current, max_point);
		}
		else if (key == Enter)
		{
			if (current == First_point)
			{
				return Random_AI;
			}
			else if (current == Second_point)
			{
				return intellectual_AI;
			}
		}

	} while (key != Esc);

	return Exit;
}

char get_status()
{
	char key;
	do
	{
		key = my_getch();
		if (key == Space)
		{
			return Space;
		}

	} while (key != Esc);

	return Exit;
}

void bot_info(const bool first)
{
	SetColor(Vanil);
	cout << "\n\n\t\t��� ������ ";
	first ? cout << 1 : cout << 2;
	SetColor(LightGray);
	cout << "\n\n\n\t\t(Space) ��������� ���\t\t\t(Esc) ������� � ���� ";
}

void kill_ship_message(bool first)
{
	SetColor(LightGreen);
	cout << "\n\n\t\t����� ";
	first ? cout << 1 : cout << 2;
	cout << " ��������� �������";
}

void damage_ship_message(bool first)
{
	SetColor(LightGreen);
	cout << "\n\n\t\t����� ";
	first ? cout << 1 : cout << 2;
	cout << " ����� ����������� �������";
}

void pl_shot_message(const bool kill)
{
	SetColor(LightGreen);
	cout << "\n\t\t";
	if (kill)
	{
		cout << "�� ���������� ������� ����������";
	}
	else
	{
		cout << "�� ������� ������� ����������";
	}
	cout << endl;
}

void cp_shot_message(const bool kill)
{
	cout << "\n\t\t";
	SetColor(Red);
	if (kill)
	{
		cout << "��� ������� ����������";
	}
	else
	{
		cout << "��� ������� �������";
	}
	cout << endl;
}

void comp_turn_message()
{
	SetColor(Vanil);
	cout << "\n\t\t��� ����������\n ";
	SetColor(LightGray);
	cout << "\n\t\t(Space) ��������� ��� ";
}

void player_turn_message()
{
	SetColor(Vanil);
	cout << "\n\t\t��� ���\n ";
}

void wrong_coord_message()
{
	SetColor(Orange);
	cout << "\n\t\t�� ����� ��������� ����������";
	cout << "\n\t\t�������� �������\n";
}

void already_fired_message()
{
	SetColor(Orange);
	cout << "\n\t\t�� ��� �������� �� �������� �����������";
	cout << "\n\t\t�������� �������\n";
}