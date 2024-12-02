#pragma once

#include <conio.h>
#include "color.h"
#include "Menu.h"
#include "Users.h"
#include "Admin.h"
#include "Section.h"
#include "TestingResultsSystem.h"

int my_getch();
const string get_string();
void main_menu(TestingResultsSystem& testing_result_system, 
	Users& users, Admin& admin, Section& sections);
void first_time_in_program(Admin& admin);
void user_menu(TestingResultsSystem& testing_result_system,
	const Section& sections, Users& users);
void enter_user_menu(TestingResultsSystem& testing_result_system, 
	Users& users, string& login, bool& log_in);
void user_log_in(const Users& users, string& login, bool& log_in);
void user_register(TestingResultsSystem& testing_result_system, Users& users);
void user_testing_menu(TestingResultsSystem& testing_result_system, 
	const Section& sections, Users& users, const string& login);
void testing_menu(TestingResultsSystem& testing_result_system, 
	const Section& sections, const string& login);
void admin_menu(TestingResultsSystem& testing_result_system,
	Admin& admin, Section& sections, Users& users);
void admin_log_in(const Admin& admin, bool& log_in);
void change_admin_parametres(Admin& admin);
void admin_users_menu(TestingResultsSystem& testing_result_system,
	Admin& admin, Users& users);
void admin_delete_user_menu(TestingResultsSystem& testing_result_system, 
	Users& users);
void admin_change_parametres_user_menu(Users& users);
void admin_show_user_results_menu(TestingResultsSystem& testing_result_system,
	Users& users);
void show_user_info(Users& users);
void admin_sections_menu(TestingResultsSystem& testing_result_system,
	Section& sections);
void add_section(Section& sections);
void delete_section(TestingResultsSystem& testing_result_system, 
	Section& sections);
void show_sections_results(TestingResultsSystem& testing_result_system,
	Section& sections);
void subsections_menu(TestingResultsSystem& testing_result_system,
	Section& sections);
void add_subsection_menu(Section& sections);
void delete_subsection_menu(TestingResultsSystem& testing_result_system,
	Section& sections);
void show_subsections_results(TestingResultsSystem& testing_result_system,
	Section& sections);
void add_questions(Section& sections);
void save_admin(const Admin& admin);
void read_admin(Admin& admin);
void save_sections(const Section& sections);
void read_sections(Section& sections);
void save_users(const Users& users);
void read_users(Users& users);
void read_testing_results_system(TestingResultsSystem& testing_result_system);
void save_testing_results_system(TestingResultsSystem& testing_result_system);