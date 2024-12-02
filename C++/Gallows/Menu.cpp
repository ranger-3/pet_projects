#include "Menu.h"

Menu::Menu(const vector<string>& messages, const string& header, const string& indent)
	: 
	messages(messages), max_points(messages.size()), indent(indent),
	header(header), current_point(1), key(0)
{}

Menu::Menu(const vector<string>& messages, const string& header)
	:
	Menu(messages, header, "\n\n\t")
{}

Menu::Menu(const vector<string>& messages)
	:
	Menu(messages, "")
{}

void Menu::GetKey()
{
	key = _getch();

	if (key == 224)
	{
		key = _getch();
		key = -key;

	}
}

void Menu::ShowPoint(const string& message, const unsigned& point)const
{
	SetColor(White);
	cout << indent;
	if (current_point == point)
	{
		SetColor(LightGreen);
		cout << "->";
	}
	else
	{
		cout << "  ";
	}
	cout << "  " << message;
	SetColor(White);
}

void Menu::ShowPoints()const
{
	if (header.size())
	{
		cout << indent << header;
	}

	for (unsigned i = 0; i < max_points; ++i)
	{
		ShowPoint(messages[i], i + 1);
	}
}

void Menu::ChangeCurrentPoint()
{
	if (key == KeyUp)
	{
		current_point = current_point == First_point ?
			max_points : --current_point;
	}
	else if (key == KeyDown)
	{
		current_point = current_point == max_points ? 
			First_point : ++current_point;
	}
}

void Menu::ShowAndGet(int& key, unsigned short& current_point)
{
	do
	{
		system("cls");
		this->ChangeCurrentPoint();
		this->ShowPoints();
		this->GetKey();

	} while (this->key != Esc && this->key != Enter);

	key = this->key;
	current_point = this->current_point;
}

void Menu::ShowAndGetNoLoop(int& key, unsigned short& current_point, bool& skip)
{
	
	this->ChangeCurrentPoint();
	this->ShowPoints();
	this->GetKey();

	if (this->key == Esc || this->key == Enter)
	{
		key = this->key;
		current_point = this->current_point;
		skip = false;
	}
	else
	{
		skip = true;
	}
}

void Menu::RepeatMenu(bool& repeat)
{
	do
	{
		system("cls");
		this->ChangeCurrentPoint();
		this->ShowPoints();
		this->GetKey();

	} while (this->key != Esc && this->key != Enter);

	
	repeat = current_point == First_point && key != Esc ? true : false;
}