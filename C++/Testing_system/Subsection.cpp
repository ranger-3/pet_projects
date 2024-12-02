#include "Subsection.h"

const char* subsections_header{ "Выберите подраздел" };
const char* subsections_repeat_menu_header{ "Такой подраздел уже существует" };
const char* eneter_subsection{ "Введите подраздел" };
const char* go_back{ "Вернуться назад" };

const vector<string> Subsection::GetSubsectionsName() const
{
	vector<string> subsections_name;

	for (const auto& subsection : subsections)
	{
		subsections_name.push_back(subsection.first);
	}

	subsections_name.push_back(go_back);

	return subsections_name;
}

const string Subsection::GetString() const
{
	char buf[100]{};
	cin.getline(buf, sizeof(buf));
	return buf;
}

bool Subsection::IsContains(const string& subsection)const
{
	return subsections.find(subsection) != subsections.end();
}

void Subsection::AddSubsection(const string& subsection)
{
	subsections.emplace(subsection, QuestionList());
}

void Subsection::DeleteSubsection(const string& subsection)
{
	if (subsections.find(subsection) != subsections.end())
	{
		subsections.erase(subsection);
	}
}

void Subsection::DeleteLastQuestion(const string& subsection)
{
	auto it = subsections.find(subsection);
	if (it != subsections.end())
	{
		it->second.DeleteLast();
	}
}

void Subsection::Testing(const string& subsection, int& key,
	int& right_answers_counter, int& current_question)const
{
	auto it = subsections.find(subsection);
	if (it != subsections.end())
	{
		it->second.Testing(key, right_answers_counter, current_question);
	}
}

void Subsection::AddQuestions(const string& subsection)
{
	auto it = subsections.find(subsection);
	if (it != subsections.end())
	{
		it->second.Init();
	}
}

const string Subsection::ChooseSubsectionMenu(int& key) const
{
	vector<string> subsections_name = GetSubsectionsName();
	Menu menu(subsections_name, subsections_header);
	unsigned short current_point = 1, choosen_point = -1;

	menu.ShowAndGet(key, current_point);
	choosen_point += current_point;
	if (choosen_point == Amount())
	{
		key == Esc;
	}
	return subsections_name[choosen_point];
}

void Subsection::ClearQuestions(const string& subsection)
{
	auto it = subsections.find(subsection);
	if (it != subsections.end())
	{
		it->second.Clear();
	}
}

void Subsection::GetAndSetSubsection()
{
	Menu menu(subsections_repeat_menu_header);
	string subsection;
	bool repeat = true;
	while (repeat)
	{
		cout << endl << eneter_subsection << ": ";
		subsection = GetString();
		if (IsContains(subsection))
		{
			menu.RepeatMenu(repeat);
		}
		else
		{
			AddSubsection(subsection);
			repeat = false;
		}
	}
}

const size_t Subsection::QuestionsAmount(const string& subsection) const
{
	auto it = subsections.find(subsection);
	if (it != subsections.end())
	{
		return it->second.Amount();
	}
	return 0;
}

void Subsection::SaveBin(ofstream& fout)const
{
	size_t size = subsections.size();
	fout.write((char*)&size, sizeof(size));

	for (const auto& subsection : subsections)
	{
		size = subsection.first.size();
		fout.write((char*)&size, sizeof(size));
		fout.write(subsection.first.c_str(), size);
		subsection.second.SaveBin(fout);
	}
}

void Subsection::ReadBin(ifstream& fin)
{
	size_t size = 0, size_str = 0, i = 0;
	string subsection;
	QuestionList question_list;
	fin.read((char*)&size, sizeof(size));

	for (; i < size; ++i)
	{
		fin.read((char*)&size_str, sizeof(size_str));
		subsection.resize(0);
		subsection.resize(size_str);
		fin.read(&subsection[0], size_str);
		question_list.Clear();
		question_list.ReadBin(fin);
		subsections.emplace(subsection, question_list);
	}
}