#pragma once

#include "Subsection.h"

class Section
{

	map<string, Subsection> sections;

public:

	const vector<string> GetSectionsNames()const;
	const vector<string> GetSubsectionsName(const string& section)const;
	const size_t Amount()const { return sections.size(); }
	bool IsContains(const string& section)const;
	bool IsContainsSubsection(const string& section, const string& subsection)const;
	void AddSection(const string& section);
	void AddSubsection(const string& section, const string& subsection);
	void Delete(const string& section);
	void DeleteSubsection(const string& section, const string& subsection);
	void DeleteLastQuestion(const string& section, const string& subsection);
	void Init(const string& section, const string& subsection);
	void Testing(const string& section, const string& subsection,
		int& key, int& right_answers_counter, int& current_question)const;
	const string ChooseSectionMenu(int& key)const;
	const string ChooseSubsectionMenu(const string& section, int& key)const;
	const size_t QuestionsAmount(const string& section, const string& subsection)const;
	void AddQuestions(const string& section, const string& subsection);
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
};

