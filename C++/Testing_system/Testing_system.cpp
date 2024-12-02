
#include <iostream>
#include "program.h"
#include "TestingResultsSystem.h"

using namespace std;

int main()
{
	system("chcp 1251>NULL");
	system("color 07");
	srand(time(NULL));

	Admin admin;
	Users users;
	TestingResultsSystem testing_result_system;
	Section sections;

	read_admin(admin);
	read_sections(sections);
	read_users(users);
	read_testing_results_system(testing_result_system);

	main_menu(testing_result_system, users, admin, sections);
	
	save_testing_results_system(testing_result_system);
	save_admin(admin);
	save_sections(sections);
	save_users(users);
	

	cout << "\n\n\n\n\n";
	return 0;
}
