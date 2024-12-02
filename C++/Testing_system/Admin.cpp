#include "Admin.h"

const char* admin_parametres_header{ "Выберите что желаете изменить" };
const char* admin_wrong_password_header{ "Введен неверный пароль" };
vector<string> admin_parametres_points{"Изменить Логин", "Изменить Пароль", "Вернуться назад"};

const string Admin::GetString() const
{
	char buf[80]{};
	cin.getline(buf, sizeof(buf));
	return buf;
}

Admin::Admin(const string& login, const string& password)
	:
	login(login), password(password)
{}

void Admin::ChangeParametrsMenu()
{
	Menu menu(admin_parametres_points, admin_parametres_header),
		repeat_menu(admin_wrong_password_header);
	unsigned short current_point = 0;
	int key = 0;
	string str;
	bool repeat = true;

	do
	{
		if (current_point == Change_login)
		{
			system("cls");
			SetColor(Vanil);
			cout << "\nТекущий логин: ";
			SetColor(White);
			cout << login;
			SetColor(Vanil);
			cout << "\nВведите новый логин: ";
			SetColor(White);
			login = GetString();
		}
		else if (current_point == Change_password)
		{
			while (repeat)
			{
				system("cls");
				SetColor(Vanil);
				cout << "\nВведите текущий пароль: ";
				SetColor(White);
				str = GetString();
				if (!CheckPassword(str))
				{
					repeat_menu.RepeatMenu(repeat);
				}
				else
				{
					system("cls");
					SetColor(Vanil);
					cout << "\nВведите новый пароль: ";
					SetColor(White);
					password = GetString();
					repeat = false;
				}
			}
			repeat = true;
		}
		else if (current_point == Exit)
		{
			key = Esc;
			continue;
		}
		menu.ShowAndGet(key, current_point);

	} while (key != Esc);
}

void Admin::SaveBin(ofstream & fout) const
{
	unsigned int size = login.size(), mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;

	size = ~size;
	size ^= mask;
	fout.write((char*)&size, sizeof(size));

	for (const auto& ch : login)
	{
		symbol = ~ch;
		symbol ^= mask_for_symbol;
		fout.put(symbol);
	}

	size = password.size();
	size = ~size;
	size ^= mask;
	fout.write((char*)&size, sizeof(size));

	for (const auto& ch : password)
	{
		symbol = ~ch;
		symbol ^= mask_for_symbol;
		fout.put(symbol);
	}
}


void Admin::ReadBin(ifstream& fin)
{
	unsigned int size = 0, i = 0, mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;

	fin.read((char*)&size, sizeof(size));
	size ^= mask;
	size = ~size;
	login.resize(0);

	for (; i < size; ++i)
	{
		fin.get(symbol);
		symbol ^= mask_for_symbol;
		symbol = ~symbol;
		login += symbol;
	}

	fin.read((char*)&size, sizeof(size));
	size ^= mask;
	size = ~size;
	password.resize(0);

	for (i = 0; i < size; ++i)
	{
		fin.get(symbol);
		symbol ^= mask_for_symbol;
		symbol = ~symbol;
		password += symbol;
	}
}