#pragma once

#include <map>
#include "QuestionList.h"

class Subsection
{
	map <string, QuestionList> subsections;

	const string GetString()const;

public:

	const vector<string> GetSubsectionsName()const;
	const size_t Amount()const { return subsections.size(); }
	void Clear() { subsections.clear(); }
	bool IsContains(const string& subsection)const;
	void AddSubsection(const string& subsection);
	void DeleteSubsection(const string& subsection);
	void DeleteLastQuestion(const string& subsection);
	void Testing(const string& subsection, int& key, 
		int& right_answers_counter, int& current_question)const;
	void AddQuestions(const string& subsection);
	const string ChooseSubsectionMenu(int& key)const;
	void ClearQuestions(const string& subsection);
	void GetAndSetSubsection();
	const size_t QuestionsAmount(const string& subsection)const;
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);

};

