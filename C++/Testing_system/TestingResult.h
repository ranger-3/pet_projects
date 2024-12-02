#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "color.h"

using namespace std;

class TestingResult
{
	enum { Grading_system = 12 };

	string section;
	string subsection;
	int answers_amount;
	int right_answers_amount;

public:

	TestingResult(const string& section, const string& subsection,
		const int& answers_amount, const int& right_answers_amount);
	TestingResult();

	~TestingResult() {}

	void SetSection(const string& section) { this->section = section; }
	void SetSubsection(const string& subsection) { this->subsection = subsection; }
	void SetRightAnswersAmount(const int& right_answers_amount) 
	{ this->right_answers_amount = right_answers_amount; }
	void SetAnswersAmount(const int& answers_amount) { this->answers_amount = answers_amount; }
	const string& GetSection()const { return section; }
	const string& GetSubsection()const { return subsection; }
	const int GetAnswersAmount()const { return answers_amount; }
	const int GetRightAnswersAmount()const { return right_answers_amount; }
	const int Mark()const;
	const double AccurateMark()const;
	const int Precent()const;
	const double AccuratePrecent()const;
	void ShowStats()const;
	void Clear();
	void Set(const string section, const string& subsection, 
		const int& answers_amount, const int& right_answers_amount);
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
	TestingResult& operator+=(const TestingResult& item);
	friend ostream& operator<<(ostream& out, const TestingResult& item);
};

