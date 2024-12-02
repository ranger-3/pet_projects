#include "TestingResultsSystem.h"

void TestingResultsSystem::ShowChapterStats(const TestingResult& testing_result, const size_t& handed_over) const
{
	SetColor(Vanil);
	cout << "\nСдано раз: ";
	SetColor(White);
	cout << handed_over;
	if (handed_over)
	{
		SetColor(Vanil);
		cout << "\nПроцент правильных ответов: ";
		SetColor(White);
		cout << setprecision(2) << fixed;
		cout << testing_result.AccuratePrecent() << '%';
		SetColor(Vanil);
		cout << "\nСредняя оценка: ";
		SetColor(White);
		cout << setprecision(2) << fixed;
		cout << testing_result.AccurateMark();
	}
}

void TestingResultsSystem::ShowSectionStats(const string& section,
	const TestingResult& testing_result, const size_t handed_over) const
{
	SetColor(Vanil);
	cout << "\nРаздел: ";
	SetColor(White);
	cout << testing_result.GetSection();
	ShowChapterStats(testing_result, handed_over);
}

void TestingResultsSystem::ShowSubsectionStats(const string& subsection, 
	const TestingResult& testing_result, const size_t handed_over) const
{
	SetColor(Vanil);
	cout << "\nРаздел: ";
	SetColor(White);
	cout << testing_result.GetSection();
	SetColor(Vanil);
	cout << "\nПодраздел: ";
	SetColor(White);
	cout << testing_result.GetSubsection();
	ShowChapterStats(testing_result, handed_over);
}

TestingResultsSystem::TestingResultsSystem(
	const map<string, TestingResultList>& users_results)
	:
	users_results(users_results)
{}

TestingResultsSystem::TestingResultsSystem()
	:
	TestingResultsSystem(map<string, TestingResultList>())
{}

void TestingResultsSystem::AddUser(const string& user_login)
{
	users_results.emplace(user_login, TestingResultList());
}

void TestingResultsSystem::AddResult(const string& user_login,
	const TestingResult& testing_result)
{
	auto it = users_results.find(user_login);
	if (it != users_results.end())
	{
		it->second.Add(testing_result);
	}
}

void TestingResultsSystem::RenameLogin(const string& old_user_login, 
	const string& new_user_login)
{
	auto it = users_results.find(old_user_login);
	if (it != users_results.end())
	{
		TestingResultList results(it->second);
		users_results.erase(it);
		users_results.emplace(new_user_login, results);
	}
}

void TestingResultsSystem::ClearUserResults(const string& user_login)
{
	auto it = users_results.find(user_login);
	if (it != users_results.end())
	{
		it->second.Clear();
	}
}

void TestingResultsSystem::DeleteUser(const string& user_login)
{
	users_results.erase(user_login);
}

void TestingResultsSystem::DeleteSection(const string& section)
{
	for (auto& user_result : users_results)
	{
		user_result.second.DeleteSection(section);
	}
}

void TestingResultsSystem::DeleteSubsection(const string& section, const string& subsection)
{
	for (auto& user_result : users_results)
	{
		user_result.second.DeleteSubsection(section, subsection);
	}
}

void TestingResultsSystem::ShowUserResults(const string& user_login) const
{
	const auto it = users_results.find(user_login);
	if (it != users_results.end())
	{
		cout << it->second;
	}
}

void TestingResultsSystem::ShowSectionsResults(const vector<string>& sections)const
{
	size_t handed_over = 0;
	TestingResult testing_result;

	for (const auto& section : sections)
	{
		testing_result.SetSection(section);
		for (const auto& user_result : users_results)
		{
			user_result.second.SectionsResults(section, testing_result, handed_over);
		}

		ShowSectionStats(section, testing_result, handed_over);
		cout << endl;
		handed_over = 0;
	}
}

void TestingResultsSystem::ShowSubsectionResults(const string& section, 
	const vector<string>& subsections)
{
	size_t handed_over = 0;
	TestingResult testing_result;
	vector<string> subsections_names = subsections;
	if (!subsections_names.size())
	{
		return;
	}

	subsections_names.pop_back();

	for (const auto& subsection : subsections_names)
	{
		testing_result.SetSection(section);
		testing_result.SetSubsection(subsection);

		for (const auto& user_result : users_results)
		{
			user_result.second.SubsectionsResults(section, subsection, testing_result, handed_over);
		}

		ShowSubsectionStats(subsection, testing_result, handed_over);
		cout << endl;
		handed_over = 0;
	}
}

void TestingResultsSystem::SaveBin(ofstream& fout) const
{
	size_t size = users_results.size();
	fout.write((char*)&size, sizeof(size));

	for (const auto& user_result : users_results)
	{
		size = user_result.first.size();
		fout.write((char*)&size, sizeof(size));
		fout.write(user_result.first.c_str(), size);
		user_result.second.SaveBin(fout);
	}
}

void TestingResultsSystem::ReadBin(ifstream& fin)
{
	size_t size = 0, size_str = 0;
	TestingResultList testing_results;
	string user_login;
	fin.read((char*)&size, sizeof(size));

	for (size_t i = 0; i < size; ++i)
	{
		fin.read((char*)&size_str, sizeof(size_str));
		user_login.resize(0);
		user_login.resize(size_str);
		fin.read(&user_login[0], size_str);
		testing_results.ReadBin(fin);
		users_results.emplace(user_login, testing_results);
	}
}
