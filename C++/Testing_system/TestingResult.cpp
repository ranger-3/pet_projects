#include "TestingResult.h"

TestingResult::TestingResult(const string& section, const string& subsection,
	const int& answers_amount, const int& right_answers_amount)
	:
	section(section), subsection(subsection), answers_amount(answers_amount), 
	right_answers_amount(right_answers_amount)
{}

TestingResult::TestingResult()
	:
	TestingResult("", "", 0, 0)
{}

const int TestingResult::Mark() const
{
	return right_answers_amount ?
		Grading_system / (answers_amount / (double)right_answers_amount) : 0;
}

const double TestingResult::AccurateMark() const
{
	return right_answers_amount ?
		Grading_system / (answers_amount / (double)right_answers_amount) : 0;
}

const int TestingResult::Precent() const
{
	return answers_amount ? (right_answers_amount * 100) / answers_amount : 0;
}

const double TestingResult::AccuratePrecent() const
{
	return answers_amount ? (right_answers_amount * 100) / (double)answers_amount : 0;
}

void TestingResult::ShowStats() const
{
	SetColor(Vanil);
	cout << "\nПравильных ответов: ";
	SetColor(White);
	cout << right_answers_amount << " из " << answers_amount;
	SetColor(Vanil);
	cout << "\nПроцент правильных ответов: ";
	SetColor(White);
	cout << Precent() << '%';
	SetColor(Vanil);
	cout << "\nОценка: ";
	SetColor(White);
	cout << Mark();
}

void TestingResult::Clear()
{
	section = "";
	subsection = "";
	answers_amount = 0;
	right_answers_amount = 0;
}

void TestingResult::Set(const string section, const string& subsection, 
	const int& answers_amount, const int& right_answers_amount)
{
	this->section = section;
	this->subsection = subsection;
	this->answers_amount = answers_amount;
	this->right_answers_amount = right_answers_amount;
}

void TestingResult::SaveBin(ofstream& fout) const
{
	size_t size = section.size();
	fout.write((char*)&size, sizeof(size));
	fout.write(section.c_str(), size);
	size = subsection.size();
	fout.write((char*)&size, sizeof(size));
	fout.write(subsection.c_str(), size);
	fout.write((char*)&answers_amount, sizeof(answers_amount));
	fout.write((char*)&right_answers_amount, sizeof(right_answers_amount));
}

void TestingResult::ReadBin(ifstream& fin)
{
	size_t size = 0;
	fin.read((char*)&size, sizeof(size));
	section.resize(0);
	section.resize(size);
	fin.read(&section[0], size);
	fin.read((char*)&size, sizeof(size));
	subsection.resize(0);
	subsection.resize(size);
	fin.read(&subsection[0], size);
	fin.read((char*)&answers_amount, sizeof(answers_amount));
	fin.read((char*)&right_answers_amount, sizeof(right_answers_amount));
}

TestingResult& TestingResult::operator+=(const TestingResult& item)
{
	answers_amount += item.answers_amount;
	right_answers_amount += item.right_answers_amount;
	return *this;
}

ostream& operator<<(ostream& out, const TestingResult& item)
{
	SetColor(Vanil);
	out << "\nРаздел: ";
	SetColor(White);
	out << item.section;
	SetColor(Vanil);
	out << "\nПодраздел: ";
	SetColor(White);
	out << item.subsection;
	item.ShowStats();
	return out;
}
