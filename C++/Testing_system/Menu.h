#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include "color.h"

using namespace std;

enum
{
	KeyUp = -72, KeyDown = -80, Esc = 27, Enter = 13
};

class Menu
{

	enum
	{
		First_point = 1, Minimum_points = 2
	};

	vector<string> messages;
	unsigned max_points;
	string indent;
	string header;
	unsigned short current_point;
	int key;

	void GetKey();
	void ShowPoint(const string& message, const unsigned& point)const;
	void ShowPoints()const;
	void ChangeCurrentPoint();

public:
	
	Menu(const vector<string>& messages, const string& header, const string& indent);
	Menu(const vector<string>& messages, const string& header);
	Menu(const vector<string>& messages);
	Menu(const string& header);

	~Menu() {}

	void ShowAndGet(int& key, unsigned short& current_point);
	void ShowAndGetNoLoop(int& key, unsigned short& current_point, bool& skip);
	void RepeatMenu(bool& repeat);
};

