#include "program.h"

const char* first_time_welcome_message
{
	"Добро пожаловать в программу для тестирования\n"
	"Зарегистрируйте администратора"
};

const char* press_any_key{ "Нажмите любую клавишу для продолжения" };
const char* main_menu_header{ "Войти как" };
const char* user_doesnt_exist_header{ "Такого логина не существует" };
const char* user_already_exist_header{ "Логин уже существует" };
const char* guest_mode_header{ "Режим гостя" };
const char* wrong_password_header{ "Введен неверный пароль" };
const char* admin_mode_header{ "Режим Администратора" };
const char* admin_mode_users_menu_header{ "Режим Администратора(Пользователи)" };
const char* admin_mode_sections_menu_header{ "Режим Администратора(Разделы)" };
const char* admin_mode_subsections_menu_header{ "Режим Администратора(Подразделы)" };
const char* admin_wrong_login_menu_header{ "Введен неверный логин администратора" };
const char* admin_wrong_password_menu_header{ "Введен неверный пароль администратора" };
const char* section_already_exist{ "Раздел уже существует" };
const char* subsection_already_exist{ "Подраздел уже существует" };
const char* sure_to_exit_testing_header
{
	"Уверены что хотите закончить тестирование?\n"
	"\tЕсли закончите, то результаты не будут сохранены"
};

vector<string> main_menu_points
{
	"Гость", "Администратор", "Выход из программы"
};

vector<string> user_enter_points
{
	"Войти", "Зарегистрироваться", "Выход в гланое меню"
};

vector<string> user_testing_menu_points
{
	"Начать тестирование", "Посмотреть результаты тестов", 
	"Посмотреть личную информацию", "Изменить личную информацию", 
	"Выход в главное меню"
};

vector<string> sure_to_exit_testing_points
{
	"Продолжить тестирование", "Выйти"
};

vector<string> admin_mode_points
{
	"Пользователи", "Разделы", "Изменить Логин/Пароль", "Выход"
};

vector<string> admin_change_parametres_points
{
	"Изменить Логин", "Изменить Пароль", "Вернуться назад"
};

vector<string> admin_users_menu_points
{
	"Создать", "Удалить", "Резултаты",
	"Изменить параметры", "Личная информация", "Вернуться назад"
};

vector<string> admin_sections_menu_points
{
	"Добавить Раздел", "Удалить Раздел", "Результаты по разделам",
	"Подразделы", "Вернуться назад"
};

vector<string> admin_subsections_menu_points
{
	"Добавить Подраздел", "Удалить Подраздел", "Добавить вопросы",
	"Результаты по подразделам", "Вернуться назад"
};

const char* admin_file("admin.txt");
const char* sections_file("sections.txt");
const char* users_file("users.txt");
const char* testing_results_file("testing_results.txt");

enum { Point1 = 1, Point2, Point3, Point4, Point5, Point6 };

int my_getch()
{
	int ch = _getch();
	if (ch == 224) {
		ch = _getch();
		return -ch;
	}
	return ch;
}

const string get_string()
{
	char buf[200]{};
	cin.getline(buf, sizeof(buf));
	return buf;
}

void main_menu(TestingResultsSystem& testing_result_system,
	Users& users, Admin& admin, Section& sections)
{
	Menu main_menu(main_menu_points, main_menu_header);
	unsigned short current_point = 0;
	int key = 0;

	

	if (!admin.IsAdmin())
	{
		first_time_in_program(admin);
	}

	do
	{
		if (current_point == Point1)
		{
			user_menu(testing_result_system, sections, users);
		}
		else if (current_point == Point2)
		{
			admin_menu(testing_result_system, admin, sections, users);
		}
		else if (current_point == Point3)
		{
			break;
		}

		main_menu.ShowAndGet(key, current_point);

	} while (key != Esc);


}

void first_time_in_program(Admin& admin)
{
	string login, password;
	SetColor(White);
	cout << endl << first_time_welcome_message << "\n\n";
	SetColor(Vanil);
	cout << "Введите логин: ";
	SetColor(White);
	login = admin.GetString();
	SetColor(Vanil);
	cout << "Введите пароль: ";
	SetColor(White);
	password = get_string();
	admin.SetLogin(login);
	admin.SetPassword(password);
}

void user_menu(TestingResultsSystem& testing_result_system, 
	const Section& sections, Users& users)
{
	Menu menu(user_enter_points);
	string login;
	bool log_in = false;

	enter_user_menu(testing_result_system, users, login, log_in);

	if (!log_in)
	{
		return;
	}

	user_testing_menu(testing_result_system, 
		sections, users, login);

}

void enter_user_menu(TestingResultsSystem& testing_result_system, 
	Users& users, string& login, bool& log_in)
{
	Menu menu(user_enter_points, guest_mode_header);
	unsigned short current_point = 0;
	int key = 0;

	do
	{
		system("cls");
		if (current_point == Point1)
		{
			user_log_in(users, login, log_in);
			if (log_in)
			{
				break;
			}
			
		}
		else if (current_point == Point2)
		{
			user_register(testing_result_system, users);
		}
		else if (current_point == Point3)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void user_log_in(const Users& users, string& login, bool& log_in)
{
	Menu user_doesnt_exist_menu(user_doesnt_exist_header),
		wrong_password_menu(wrong_password_header);
	string password;
	bool repeat = false;

	do
	{

		system("cls");
		SetColor(Vanil);
		cout << "\nАвторизация Гостя\n";
		cout << "\nВведите логин: ";
		SetColor(White);
		login = get_string();
		if (!users.Contains(login))
		{
			user_doesnt_exist_menu.RepeatMenu(repeat);
		}
		else
		{
			do
			{
				system("cls");
				SetColor(Vanil);
				cout << "\nАвторизация Гостя\n";
				cout << "\nЛогин: ";
				SetColor(White);
				cout << login;
				SetColor(Vanil);
				cout << "\nВведите пароль: ";
				SetColor(White);
				password = get_string();

				if (users.CorrectPassword(login, password))
				{
					log_in = true;
					repeat = false;
				}
				else
				{
					wrong_password_menu.RepeatMenu(repeat);
				}
			} while (repeat);
		}
	
	} while (repeat);
}

void user_register(TestingResultsSystem& testing_result_system, Users& users)
{
	Menu user_already_exist_menu(user_already_exist_header);
	UserInfo user_info;
	string login;
	bool repeat = false;

	do
	{
		system("cls");
		SetColor(Vanil);
		cout << "\nРегистрация\n";
		cout << "\nВведите логин: ";
		SetColor(White);
		login = get_string();
		if (users.Contains(login))
		{
			user_already_exist_menu.RepeatMenu(repeat);
		}
		else
		{
			cin >> user_info;
			users.AddUser(login, user_info);
			testing_result_system.AddUser(login);
			repeat = false;
		}

	} while (repeat);
}

void user_testing_menu(TestingResultsSystem& testing_result_system, 
	const Section& sections, Users& users, const string& login)
{
	string guest_header = "Гость: " + login;
	Menu menu(user_testing_menu_points, guest_header);
	unsigned short current_point = 0;
	int key = 0;

	do
	{
		if (current_point == Point1)
		{
			testing_menu(testing_result_system, sections, login);
		}
		else if (current_point == Point2)
		{
			system("cls");
			testing_result_system.ShowUserResults(login);
			cout << endl << endl << press_any_key;
			my_getch();
		}
		else if (current_point == Point3)
		{
			system("cls");
			users.ShowUserInfo(login);
			cout << endl << endl << press_any_key;
			my_getch();
		}
		else if (current_point == Point4)
		{
			users.UserParametresMenu(login);
		}
		else if (current_point == Point5)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void testing_menu(TestingResultsSystem& testing_result_system, 
	const Section& sections, const string& login)
{
	Menu menu_sure_to_exit_testing(sure_to_exit_testing_points, 
		sure_to_exit_testing_header);
	int right_answers_amount = 0, answers_amount = 0, 
		current_question = 0;
	string section, subsection;
	TestingResult testing_result;
	unsigned short current_point = 0;
	int key = 0;

	section = sections.ChooseSectionMenu(key);

	if (key == Esc)
	{
		return;
	}

	subsection = sections.ChooseSubsectionMenu(section, key);

	if (key == Esc)
	{
		return;
	}

	answers_amount = sections.QuestionsAmount(section, subsection);
	while (key != Esc)
	{
		sections.Testing(section, subsection, key,
			right_answers_amount, current_question);

		if (answers_amount == current_question)
		{
			break;
		}

		if (key == Esc)
		{
			key = 0;
			menu_sure_to_exit_testing.ShowAndGet(key, current_point);
			if (current_point == Point2)
			{
				key = Esc;
			}
		}
	}

	if (key != Esc)
	{
		testing_result_system.AddResult(login, TestingResult
		(section, subsection, answers_amount, right_answers_amount));
	}
}

void admin_menu(TestingResultsSystem& testing_result_system, 
	Admin& admin, Section& sections, Users& users)
{
	Menu menu(admin_mode_points, admin_mode_header);
	unsigned short current_point = 0;
	int key = 0;
	bool log_in = false;

	admin_log_in(admin, log_in);
	if (!log_in)
	{
		return;
	}

	do
	{
		if (current_point == Point1)
		{
			admin_users_menu(testing_result_system, admin, users);
		}
		else if (current_point == Point2)
		{
			admin_sections_menu(testing_result_system, sections);
		}
		else if (current_point == Point3)
		{
			change_admin_parametres(admin);
		}
		else if (current_point == Point4)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);

}

void admin_log_in(const Admin& admin, bool& log_in)
{
	Menu admin_wrong_login(admin_wrong_login_menu_header),
		admin_wrong_password(admin_wrong_password_menu_header);
	string login, password;
	bool repeat = false;

	do
	{

		system("cls");
		SetColor(Vanil);
		cout << "\nАвторизация Админа\n";
		cout << "\nВведите логин: ";
		SetColor(White);
		login = get_string();
		if (admin.CheckLogin(login))
		{
			do
			{
				system("cls");
				SetColor(Vanil);
				cout << "\nАвторизация Админа\n";
				cout << "\nЛогин: ";
				SetColor(White);
				cout << login;
				SetColor(Vanil);
				cout << "\nВведите пароль: ";
				SetColor(White);
				password = get_string();

				if (admin.CheckPassword(password))
				{
					log_in = true;
					repeat = false;
				}
				else
				{
					admin_wrong_password.RepeatMenu(repeat);
				}
			} while (repeat);
		}
		else
		{
			admin_wrong_login.RepeatMenu(repeat);
		}

	} while (repeat);
}

void change_admin_parametres(Admin& admin)
{
	Menu menu(admin_change_parametres_points, admin_mode_header),
		wrong_password_menu(admin_wrong_password_menu_header);
	string new_admin_info;
	unsigned short current_point = 0;
	bool repeat = false;
	int key = 0;

	do
	{
		if (current_point == Point1)
		{
			system("cls");
			cout << "\nВведите новый логин: ";
			new_admin_info = get_string();
			admin.SetLogin(new_admin_info);
		}
		else if (current_point == Point2)
		{
			do
			{
				system("cls");
				cout << "\nВведите текущий пароль: ";
				new_admin_info = get_string();

				if (admin.CheckPassword(new_admin_info))
				{
					system("cls");
					cout << "\nВведите новый пароль: ";
					new_admin_info = get_string();
					admin.SetPassword(new_admin_info);
					repeat = false;
				}
				else
				{
					wrong_password_menu.RepeatMenu(repeat);
				}

			} while (repeat);
		}
		else if (current_point == Point3)
		{
			break;
		}
		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void admin_users_menu(TestingResultsSystem& testing_result_system, 
	Admin& admin, Users& users)
{
	Menu menu(admin_users_menu_points, admin_mode_users_menu_header);
	unsigned short current_point = 0;
	bool repeat = false;
	int key = 0;

	do
	{
		if (current_point == Point1)
		{
			user_register(testing_result_system, users);
		}
		else if (current_point == Point2)
		{
			admin_delete_user_menu(testing_result_system, users);
		}
		else if (current_point == Point3)
		{
			admin_show_user_results_menu(testing_result_system, users);
		}
		else if (current_point == Point4)
		{
			admin_change_parametres_user_menu(users);
		}
		else if (current_point == Point5)
		{
			show_user_info(users);
		}
		else if (current_point == Point6)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);

}

void admin_delete_user_menu(TestingResultsSystem& testing_result_system, 
	Users& users)
{
	string user_login;
	users.ChooseUser(user_login);

	if (user_login.size())
	{
		users.DeleteUser(user_login);
		testing_result_system.DeleteUser(user_login);
	}
}

void admin_change_parametres_user_menu(Users& users)
{
	string user_login;
	users.ChooseUser(user_login);

	if (user_login.size())
	{
		users.UserParametresMenu(user_login, true);
	}
}

void admin_show_user_results_menu(TestingResultsSystem& testing_result_system, Users& users)
{
	string user_login;
	users.ChooseUser(user_login);

	if (user_login.size())
	{
		system("cls");
		testing_result_system.ShowUserResults(user_login);
		cout << "\n\n" << press_any_key;
		my_getch();
	}
}

void show_user_info(Users& users)
{
	string user_login;
	users.ChooseUser(user_login);

	if (user_login.size())
	{
		system("cls");
		users.ShowUserInfo(user_login, true);
		cout << "\n\n" << press_any_key;
		my_getch();
	}
}

void admin_sections_menu(TestingResultsSystem& testing_result_system, Section& sections)
{
	Menu menu(admin_sections_menu_points, admin_mode_sections_menu_header);
	unsigned short current_point = 0;
	int key = 0;

	do
	{
		if (current_point == Point1)
		{
			add_section(sections);
		}
		else if (current_point == Point2)
		{
			delete_section(testing_result_system, sections);
		}
		else if (current_point == Point3)
		{
			show_sections_results(testing_result_system, sections);
		}
		else if (current_point == Point4)
		{
			subsections_menu(testing_result_system, sections);
		}
		else if (current_point == Point5)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void add_section(Section& sections)
{
	Menu menu(section_already_exist);
	string section;
	bool repeat = false;

	do
	{
		system("cls");
		cout << "\nВведите название раздела: ";
		section = get_string();

		if (sections.IsContains(section))
		{
			menu.RepeatMenu(repeat);
		}
		else
		{
			sections.AddSection(section);
		}	

	} while (repeat);

}

void delete_section(TestingResultsSystem& testing_result_system, 
	Section& sections)
{
	int key = 0;
	string section;
	section = sections.ChooseSectionMenu(key);
	if (key != Esc)
	{
		sections.Delete(section);
		testing_result_system.DeleteSection(section);
	}
}

void show_sections_results(TestingResultsSystem& testing_result_system, Section& sections)
{
	vector<string> sections_names = sections.GetSectionsNames();
	sections_names.pop_back();
	system("cls");
	testing_result_system.ShowSectionsResults(sections_names);
	cout << "\n\n" << press_any_key;
	my_getch();
}

void subsections_menu(TestingResultsSystem& testing_result_system, Section& sections)
{
	Menu menu(admin_subsections_menu_points, admin_mode_subsections_menu_header);
	unsigned short current_point = 0;
	int key = 0;

	do
	{
		if (current_point == Point1)
		{
			add_subsection_menu(sections);
		}
		else if (current_point == Point2)
		{
			delete_subsection_menu(testing_result_system, sections);
		}
		else if (current_point == Point3)
		{
			add_questions(sections);
		}
		else if (current_point == Point4)
		{
			show_subsections_results(testing_result_system, sections);
		}
		else if (current_point == Point5)
		{
			break;
		}

		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void add_subsection_menu(Section& sections)
{
	Menu menu(subsection_already_exist);
	bool repeat = false;
	int key = 0;
	string section, subsection;

	section = sections.ChooseSectionMenu(key);

	
	if (key != Esc)
	{
		do
		{
			system("cls");
			cout << "\nВведите название подраздела: ";
			subsection = get_string();

			if (sections.IsContainsSubsection(section, subsection))
			{
				menu.RepeatMenu(repeat);
			}
			else
			{
				sections.AddSubsection(section, subsection);
			}

		} while (repeat);		
	}
}

void delete_subsection_menu(TestingResultsSystem& testing_result_system, Section& sections)
{
	int key = 0;
	string section, subsection;

	section = sections.ChooseSectionMenu(key);
	if (key != Esc)
	{
		subsection = sections.ChooseSubsectionMenu(section, key);
		if (key != Esc)
		{
			sections.DeleteSubsection(section, subsection);
			testing_result_system.DeleteSubsection(section, subsection);
		}
	}
}

void show_subsections_results(TestingResultsSystem& testing_result_system, 
	Section& sections)
{
	vector<string> subsections_names, 
		sections_names = sections.GetSectionsNames();

	system("cls");
	for (const auto& section : sections_names)
	{
		subsections_names.resize(0);
		subsections_names = sections.GetSubsectionsName(section);
		testing_result_system.ShowSubsectionResults(section,
			subsections_names);

	}
	cout << "\n\n" << press_any_key;
	my_getch();
}

void add_questions(Section& sections)
{
	int key = 0;
	string section, subsection;

	section = sections.ChooseSectionMenu(key);
	if (key != Esc)
	{
		subsection = sections.ChooseSubsectionMenu(section, key);
		if (key != Esc)
		{
			sections.AddQuestions(section, subsection);
		}
	}
}

void save_admin(const Admin& admin)
{
	ofstream fout(admin_file, ios::binary);

	if (fout)
	{
		admin.SaveBin(fout);
		fout.close();
	}
}

void read_admin(Admin& admin)
{
	ifstream fin(admin_file, ios::binary);

	if (fin)
	{
		admin.ReadBin(fin);
		fin.close();
	}
}

void save_sections(const Section& sections)
{
	ofstream fout(sections_file, ios::binary);

	if (fout)
	{
		sections.SaveBin(fout);
		fout.close();
	}
}

void read_sections(Section& sections)
{
	ifstream fin(sections_file, ios::binary);

	if (fin)
	{
		sections.ReadBin(fin);
		fin.close();
	}
}

void save_users(const Users& users)
{
	ofstream fout(users_file, ios::binary);

	if (fout)
	{
		users.SaveBin(fout);
		fout.close();
	}
}
void read_users(Users& users)
{
	ifstream fin(users_file, ios::binary);

	if (fin)
	{
		users.ReadBin(fin);
		fin.close();
	}
}

void save_testing_results_system(TestingResultsSystem& testing_result_system)
{
	ofstream fout(testing_results_file, ios::binary);

	if (fout)
	{
		testing_result_system.SaveBin(fout);
		fout.close();
	}
}

void read_testing_results_system(TestingResultsSystem& testing_result_system)
{
	ifstream fin(testing_results_file, ios::binary);

	if (fin)
	{
		testing_result_system.ReadBin(fin);
		fin.close();
	}
}

