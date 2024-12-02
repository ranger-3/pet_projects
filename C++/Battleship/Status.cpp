#include <iostream>
#include "Status.h"
#include "Board.h"
#include "Ship.h"
#include "color.h"

using namespace std;

void clear_stats(Status& st1, Status& st2)
{
	st1.four_alive = Four_deck;
	st2.four_alive = Four_deck;
	st1.three_alive = Three_deck;
	st2.three_alive = Three_deck;
	st1.two_alive = Two_deck;
	st2.two_alive = Two_deck;
	st1.single_alive = Single_deck;
	st2.single_alive = Single_deck;
	st1.alive = Navy;
	st2.alive = Navy;
}

void change_status(Status& st, const short size)
{
	if (size == Single_deck_size)
	{
		st.single_alive--;
	}
	else if (size == Two_deck_size)
	{
		st.two_alive--;
	}
	else if (size == Three_deck_size)
	{
		st.three_alive--;
	}
	else if (size == Four_deck_size)
	{
		st.four_alive--;
	}
	st.alive--;
}

void show_stats(Status& st1, Status& st2)
{
	st1.four_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\n\n\t\t" << st1.four_alive << " - XXXX";
	st2.four_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\t\t\t\t" << st2.four_alive << " - XXXX";

	st1.three_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\n\t\t" << st1.three_alive << " - XXX";
	st2.three_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\t\t\t\t\t" << st2.three_alive << " - XXX";

	st1.two_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\n\t\t" << st1.two_alive << " - XX";
	st2.two_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\t\t\t\t\t" << st2.two_alive << " - XX";

	st1.single_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\n\t\t" << st1.single_alive << " - X";
	st2.single_alive == All_dead ? SetColor(Orange) : SetColor(LightGray);
	cout << "\t\t\t\t\t" << st2.single_alive << " - X";

	st1.alive == All_dead ? SetColor(Red) : SetColor(LightGray);
	cout << "\n\n\t\t" << st1.alive << " - Всего кораблей";
	st2.alive == All_dead ? SetColor(Red) : SetColor(LightGray);
	cout << "\t\t\t" << st2.alive << " - Всего кораблей" << endl;
}