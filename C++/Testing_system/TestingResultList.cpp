#include "TestingResultList.h"

TestingResultList::TestingResultList(const list<TestingResult>& testing_results)
	:
	testing_results(testing_results)
{}

TestingResultList::TestingResultList(const TestingResultList& item)
{
	testing_results = item.testing_results;
}

void TestingResultList::Add(const TestingResult& testing_result)
{
	testing_results.push_back(testing_result);
}

void TestingResultList::DeleteLast()
{
	testing_results.pop_back();
}

void TestingResultList::SaveBin(ofstream& fout) const
{
	size_t size = testing_results.size();
	fout.write((char*)&size, sizeof(size));

	for (const auto& testing_result : testing_results)
	{
		testing_result.SaveBin(fout);
	}
}

void TestingResultList::ReadBin(ifstream& fin)
{
	size_t size = 0, i = 0;
	TestingResult tmp;

	testing_results.clear();
	fin.read((char*)&size, sizeof(size));

	for (; i < size; ++i)
	{
		tmp.ReadBin(fin);
		testing_results.push_back(tmp);
	}
}

void TestingResultList::DeleteSection(const string& section)
{
	auto it = testing_results.begin();
	for (; it != testing_results.end();)
	{
		if (it->GetSection() == section)
		{
			it = testing_results.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void TestingResultList::DeleteSubsection(const string& section, const string& subsection)
{
	auto it = testing_results.begin();
	for (; it != testing_results.end();)
	{
		if (it->GetSubsection() == subsection && it->GetSection() == section)
		{
			it = testing_results.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void TestingResultList::SectionsResults(const string& section, TestingResult& result, size_t& handed_over) const
{

	for (const auto& testing_result : testing_results)
	{
		if (testing_result.GetSection() == section)
		{
			result += testing_result;
			++handed_over;
		}
	}
}

void TestingResultList::SubsectionsResults(const string& section, 
	const string& subsection, TestingResult& result, size_t& handed_over) const
{
	for (const auto& testing_result : testing_results)
	{
		if (testing_result.GetSection() == section && 
			testing_result.GetSubsection() == subsection)
		{
			result += testing_result;
			++handed_over;
		}
	}
}

ostream& operator<<(ostream& out, const TestingResultList& item)
{
	if (item.testing_results.size() == 0)
	{
		out << "\nТестирование еще не проводилось";
		return out;
	}

	for (const auto& testing_result : item.testing_results)
	{
		out << testing_result << endl;
	}
	return out;
}
