#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"

using namespace std;

class UserInfo
{
	enum 
	{
		User_info_size = 6, Name = 0, Surname, Patronymic, 
		Address, Phone_number, Password, Mask = 543153816, 
		Mask_for_char = 43
	};

	string user_info[User_info_size];

	const string GetString()const;
	void ShowFieldName(const string& field_name, const bool& indent = true)const;
	void ShowFieldInfo(const string& field_name, const string& field_info)const;
	void ShowFieldsInfo(const bool& admin = false)const;
	void GetAndSetNewValue(const int& field_position);

public:

	UserInfo(const string& name, const string& surname, const string& patronymic,
		const string& address, const string& phone_number, const string& password);
	UserInfo();

	~UserInfo() {}

	bool IsCorrectPassword(const string& password)const { return user_info[Password] == password; }
	void SetPassword(const string& password) { user_info[Password] = password; }
	bool GetPassword()const;
	void UserInfoMenu(const bool& admin = false);
	void ShowFullUserInfo(const bool& admin = false)const;
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);

	friend ostream& operator<<(ostream& out, const UserInfo& item);
	friend istream& operator>>(istream& in, UserInfo& item);

};

