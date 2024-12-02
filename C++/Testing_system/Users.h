#pragma once

#include <map>
#include "UserInfo.h"

class Users
{
	map<string, UserInfo> users;

public:

	const size_t Amount()const { return users.size(); }
	bool Contains(const string& login)const { return users.find(login) != users.end(); }
	bool CorrectPassword(const string& login, const string& password)const;
	void AddUser(const string& login, const UserInfo& user_info);
	void AddUser(const string& login);
	void DeleteUser(const string& login);
	void ShowUserInfo(const string& login, const bool& admin = false)const;
	void UserParametresMenu(const string& login, const bool& admin = false);
	const vector<string> UsersLogins()const;
	void ChooseUser(string& login)const;
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
};

