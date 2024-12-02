#include "Section.h"

const char* section_header{ "Выберите раздел" };
const char* return_back{ "Вернуться назад" };

const vector<string> Section::GetSectionsNames() const
{
	vector<string> sections_names;

	for (const auto& section : sections)
	{
		sections_names.push_back(section.first);
	}

	sections_names.push_back(return_back);

	return sections_names;
}

const vector<string> Section::GetSubsectionsName(const string& section) const
{
	vector<string> subsections_names;

	auto it = sections.find(section);
	if (it != sections.end())
	{
		return it->second.GetSubsectionsName();
	}

	return subsections_names;
}

bool Section::IsContains(const string& section)const
{
	return sections.find(section) != sections.end();
}

bool Section::IsContainsSubsection(const string& section, const string& subsection)const
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		return it->second.IsContains(subsection);
	}
	return false;
}

void Section::AddSection(const string& section)
{
	sections.emplace(section, Subsection());
}

void Section::AddSubsection(const string& section, const string& subsection)
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		it->second.AddSubsection(subsection);
	}
}

void Section::Delete(const string& section)
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		sections.erase(section);
	}
}

void Section::DeleteSubsection(const string& section, const string& subsection)
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		it->second.DeleteSubsection(subsection);
	}
}

void Section::DeleteLastQuestion(const string& section, const string& subsection)
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		it->second.DeleteLastQuestion(subsection);
	}
}

void Section::Init(const string& section, const string& subsection)
{
	auto it = sections.find(section);
	if (it == sections.end())
	{
		return;
	}
}

void Section::Testing(const string& section, const string& subsection,
	int& key, int& right_answers_counter, int& current_question)const
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		it->second.Testing(subsection, key, 
			right_answers_counter, current_question);
	}
}

const string Section::ChooseSectionMenu(int& key) const
{
	vector<string> sections_names = GetSectionsNames();
	Menu menu(sections_names, section_header);
	unsigned short current_point = 1, choosen_point = -1;

	menu.ShowAndGet(key, current_point);
	choosen_point += current_point;
	if (current_point == sections_names.size())
	{
		key = Esc;
	}
	return sections_names[choosen_point];
}

const string Section::ChooseSubsectionMenu(const string& section, int& key) const
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		return it->second.ChooseSubsectionMenu(key);
	}
	return "";
}

const size_t Section::QuestionsAmount(const string& section, const string& subsection) const
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		return it->second.QuestionsAmount(subsection);
	}
	return 0;
}

void Section::AddQuestions(const string& section, const string& subsection)
{
	auto it = sections.find(section);
	if (it != sections.end())
	{
		it->second.AddQuestions(subsection);
	}
}

void Section::SaveBin(ofstream& fout) const
{
	size_t size = sections.size();
	fout.write((char*)&size, sizeof(size));

	for (const auto& section : sections)
	{
		size = section.first.size();
		fout.write((char*)&size, sizeof(size));
		fout.write(section.first.c_str(), size);
		section.second.SaveBin(fout);
	}
}

void Section::ReadBin(ifstream& fin)
{
	size_t size = 0, size_str = 0, i = 0;
	string section;
	Subsection subsection;
	fin.read((char*)&size, sizeof(size));

	for (; i < size; ++i)
	{
		fin.read((char*)&size_str, sizeof(size_str));
		section.resize(0);
		section.resize(size_str);
		fin.read(&section[0], size_str);
		subsection.Clear();
		subsection.ReadBin(fin);
		sections.emplace(section, subsection);
	}
}
