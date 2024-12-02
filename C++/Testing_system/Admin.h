#pragma once

#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace std;

class Admin
{
	enum 
	{
		Mask = 987968899, Mask_for_char = 123, 
		Change_login = 1, Change_password, Exit
	};

	string login;
	string password;

public:

	Admin(const string& login, const string& password);
	Admin() : Admin("", "") {}

	~Admin() {}

	const string GetString()const;
	bool IsAdmin()const { return login.size(); }
	void SetLogin(const string& login) { this->login = login; }
	void SetPassword(const string& password) { this->password = password; }
	const string& GetLogin()const { return login; }
	const string& GetPassword()const { return password; }
	bool CheckLogin(const string& login)const { return this->login == login; }
	bool CheckPassword(const string& password)const { return this->password == password; }
	void ChangeParametrsMenu();
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
};

