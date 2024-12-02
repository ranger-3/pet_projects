#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Menu.h"
#include "color.h"

using namespace std;

class Question
{

	enum
	{
		Buf_size = 250, Required_points = 3, Mask = 257945999,
		Mask_for_char = 78
	};

	string question;
	vector<pair<string, bool>> answers;

	const string GetString()const;
	void GetAndSet(const string& header, string& str);
	void SetRightQuestion();
	const vector<string> RandomSortAnswers()const;

public:

	Question(const string& question, const vector<pair<string, bool>>& answers);
	Question(const string& question);
	Question();

	~Question() {}

	const string& GetQuestion()const { return question; }
	void InitQuestion();
	void Ask(int& key, bool& correct)const;
	void clear();
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);

	friend ostream& operator<<(ostream& out, const Question& item);
};

