#include "UserInfo.h"

vector<string>fields_name
{ 
	"Имя", "Фамилия", "Отчество", "Домашний адрес", 
	"Номер телефона", "Пароль", "Вернуться назад"
};

const char* header_user_info_menu{ "Выберите пункт, который желаете изменить " };
const char* header_repeat_password{ "Введен неверный пароль" };
const char* header_get_current_password{ "Введите текущий пароль" };
const char* empty_field = { "Не заполнено" };

const string UserInfo::GetString()const
{
	char buf[70]{};
	string tmp;
	cin.getline(buf, sizeof(buf));
	tmp = buf;
	return tmp;
}

void UserInfo::ShowFieldName(const string& field_name, const bool& indent) const
{
	SetColor(Vanil);
	if (indent)
	{
		cout << endl;
	}
	cout << field_name << ": ";
	SetColor(White);
}

void UserInfo::ShowFieldInfo(const string& field_name, const string& field_info)const
{
	ShowFieldName(field_name);
	cout << field_info;
}

void UserInfo::ShowFieldsInfo(const bool& admin) const
{
	size_t size = User_info_size;

	if (!admin)
	{
		--size;
	}

	for (size_t i = 0; i < size; ++i)
	{
		ShowFieldInfo(fields_name[i], user_info[i]);
	}
}

void UserInfo::GetAndSetNewValue(const int& field_position)
{
	string new_value;
	SetColor(Vanil);
	cout << "\nСтарое значение(" << fields_name[field_position] << "): ";
	SetColor(White);
	cout << user_info[field_position];
	SetColor(Vanil);
	cout << "\nВведите новое значение: ";
	SetColor(White);
	new_value = GetString();
	user_info[field_position] = new_value;
}

UserInfo::UserInfo(const string& name, const string& surname, const string& patronymic,
	const string& address, const string& phone_number, const string& password)
{
	user_info[Name] = name;
	user_info[Surname] = surname;
	user_info[Patronymic] = patronymic;
	user_info[Address] = address;
	user_info[Phone_number] = phone_number;
	user_info[Password] = password;
}

UserInfo::UserInfo()
{
	for (auto& field_info : user_info)
	{
		field_info = empty_field;
	}
}

bool UserInfo::GetPassword() const
{
	Menu passwrod_repeat(header_repeat_password);
	string password;
	bool repeat = true;

	while (repeat)
	{
		system("cls");
		SetColor(Vanil);
		cout << endl << header_get_current_password << ": ";
		SetColor(White);
		password = GetString();
		if (IsCorrectPassword(password))
		{
			return true;
		}
		else
		{
			passwrod_repeat.RepeatMenu(repeat);
		}
	}

	return false;
}

void UserInfo::UserInfoMenu(const bool& admin)
{
	Menu menu(fields_name, header_user_info_menu);
	int key = 0;
	unsigned short current_point = 1, 
		last_point = fields_name.size();

	while (key != Esc)
	{
		menu.ShowAndGet(key, current_point);

		if (key == Enter)
		{
			system("cls");
			if (current_point == last_point)
			{
				key = Esc;
				break;
			}
			else if (current_point - 1 == Password && !admin)
			{
				if (!GetPassword())
				{
					continue;
				}
				system("cls");
			}

			GetAndSetNewValue(current_point - 1);
		}
	}
}

void UserInfo::ShowFullUserInfo(const bool& admin) const
{
	ShowFieldsInfo(admin);
}

void UserInfo::SaveBin(ofstream& fout)const
{
	unsigned int size = 0, mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;

	for (const auto& field_info : user_info)
	{
		size = field_info.size();
		size = ~size;
		size ^= mask;
		fout.write((char*)&size, sizeof(size));

		for (const auto& ch : field_info)
		{
			symbol = ~ch;
			symbol ^= mask_for_symbol;
			fout.put(symbol);
		}
	}
}

void UserInfo::ReadBin(ifstream& fin)
{
	unsigned int size = 0, i = 0, mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;

	for (auto& field_info : user_info)
	{
		fin.read((char*)&size, sizeof(size));
		size ^= mask;
		size = ~size;
		field_info.resize(0);

		for (i = 0; i < size; ++i)
		{
			fin.get(symbol);
			symbol ^= mask_for_symbol;
			symbol = ~symbol;
			field_info += symbol;
		}
	}
}

ostream& operator<<(ostream & out, const UserInfo & item)
{
	item.ShowFieldsInfo();
	return out;
}

istream& operator>>(istream& in, UserInfo& item)
{
	bool indent = false;
	for (size_t i = 0; i < item.User_info_size; ++i)
	{
		item.ShowFieldName(fields_name[i], indent);
		item.user_info[i] = item.GetString();
	}
	return in;
}
