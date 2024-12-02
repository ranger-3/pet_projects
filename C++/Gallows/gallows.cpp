#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	system("chcp 1251>NULL");
	system("color 07");
	srand(time(NULL));


	Dictionary dictionary;
	main_menu(dictionary);

	cout << "\n\n\n\n\n";
	return 0;
}
