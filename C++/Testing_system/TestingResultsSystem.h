#pragma once

#include <map>
#include <iomanip>
#include <vector>
#include "TestingResultList.h"

class TestingResultsSystem
{
	map<string, TestingResultList> users_results;

	void ShowChapterStats(const TestingResult& testing_result, const size_t& handed_over)const;
	void ShowSectionStats(const string& section, const TestingResult& testing_result, 
		const size_t handed_over)const;
	void ShowSubsectionStats(const string& subsection, const TestingResult& testing_result, 
		const size_t handed_over)const;

public:

	TestingResultsSystem(const map<string, TestingResultList>& users_results);
	TestingResultsSystem();

	~TestingResultsSystem() {}

	void AddUser(const string& user_login);
	void AddResult(const string& user_login, const TestingResult& testing_result);
	void RenameLogin(const string& old_user_login, const string& new_user_login);
	void ClearUserResults(const string& user_login);
	void DeleteUser(const string& user_login);
	void DeleteSection(const string& section);
	void DeleteSubsection(const string& section, const string& subsection);
	void ShowUserResults(const string& user_login)const;
	void ShowSectionsResults(const vector<string>& section)const;
	void ShowSubsectionResults(const string& section, const vector<string>& subsections);
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
	
};

