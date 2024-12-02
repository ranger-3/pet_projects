#pragma once

#include <list>
#include "TestingResult.h"

class TestingResultList
{

	list<TestingResult> testing_results;

public:
	TestingResultList(const list<TestingResult>& testing_results);
	TestingResultList() : TestingResultList(list<TestingResult>()){}
	TestingResultList(const TestingResultList& item);

	~TestingResultList() {}

	void Clear() { testing_results.clear(); }
	void Add(const TestingResult& testing_result);
	void DeleteLast();
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
	void DeleteSection(const string& section);
	void DeleteSubsection(const string& section, const string& subsection);
	void SectionsResults(const string& section, TestingResult& result, size_t& handed_over)const;
	void SubsectionsResults(const string& section, const string& subsection, 
		TestingResult& result, size_t& handed_over)const;

	friend ostream& operator<<(ostream& out, const TestingResultList& item);
};

