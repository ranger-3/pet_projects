#include "GallowsPicture.h"

void GallowsPicture::Show()const
{
	cout << "\n\t__________";
	cout << "\n\t|       |";
	cout << "\n\t|";
	if (status > 0)
	{
		cout << "       O";
	}
	cout << "\n\t|";
	if (status > 1)
	{
		cout << "      ";
		status > 2 ? cout << '/' : cout << ' ';
		cout << '|';
		if (status > 3)
		{
			cout << '\\';
		}
	}
	cout << "\n\t|";
	if (status > 1)
	{
		cout << "       |";
	}
	cout << "\n\t|";
	if (status > 4)
	{
		cout << "      /";
		if (status > 5)
		{
			cout << " \\";
		}
	}
	cout << "\n\t|---|_____";
	cout << "\n\t|________|";
}