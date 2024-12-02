#include "Users.h"

const char* choose_user_header{ "Выберите пользователя" };

bool Users::CorrectPassword(const string& login, const string& password) const
{
	const auto it = users.find(login);
	if (it != users.end())
	{
		return it->second.IsCorrectPassword(password);
	}
	return false;
}

void Users::AddUser(const string& login, const UserInfo& user_info)
{
	users.emplace(login, user_info);
}

void Users::AddUser(const string& login)
{
	users.emplace(login, UserInfo());
}

void Users::DeleteUser(const string& login)
{
	users.erase(login);
}

void Users::ShowUserInfo(const string& login, const bool& admin) const
{
	const auto it = users.find(login);
	if (it != users.end())
	{
		it->second.ShowFullUserInfo(admin);
	}
}

void Users::UserParametresMenu(const string& login, const bool& admin)
{
	auto it = users.find(login);
	if (it != users.end())
	{
		it->second.UserInfoMenu(admin);
	}

}

const vector<string> Users::UsersLogins() const
{
	vector<string> users_logins;

	for (const auto& user : users)
	{
		users_logins.push_back(user.first);
	}
	return users_logins;
}

void Users::ChooseUser(string& login) const
{
	vector<string> users_logins = UsersLogins();
	users_logins.push_back("Вернуться назад");
	Menu menu(users_logins, choose_user_header);
	unsigned short current_point = 0;
	int key = 0;

	menu.ShowAndGet(key, current_point);
	if (key == Esc || current_point == users_logins.size())
	{
		login.resize(0);
	}
	else
	{
		--current_point;
		login = users_logins[current_point];
	}
}

void Users::SaveBin(ofstream& fout) const
{
	size_t size = users.size();
	fout.write((char*)&size, sizeof(size));

	for (const auto& user : users)
	{
		size = user.first.size();
		fout.write((char*)&size, sizeof(size));
		fout.write(user.first.c_str(), size);
		user.second.SaveBin(fout);
	}
}

void Users::ReadBin(ifstream& fin)
{
	size_t size = 0, size_str = 0, i = 0;
	string login;
	UserInfo user_info;

	fin.read((char*)&size, sizeof(size));

	for (; i < size; ++i)
	{
		fin.read((char*)&size_str, sizeof(size_str));
		login.resize(0);
		login.resize(size_str);
		fin.read(&login[0], size_str);
		user_info.ReadBin(fin);
		users.emplace(login, user_info);
	}
}
