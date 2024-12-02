#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Dictionary
{
	enum { Mask = 805974229, Mask_for_char = 97 };

	vector<string> dictionary;

public:

	Dictionary(const vector<string>& dictionary);
	Dictionary();

	~Dictionary() {}

	void AddWord(const string& word);
	void DeleteWord(const string& word);
	const string GetRandomWord()const;

	friend ostream& operator<<(ostream& out, const Dictionary& item);

	void SaveEncrypt(ofstream& fout)const;
	void ReadDecrypt(ifstream& fin);
};

