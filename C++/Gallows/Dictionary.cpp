#include "Dictionary.h"

Dictionary::Dictionary(const vector<string>& dictionary)
	:
	dictionary(dictionary)
{}

Dictionary::Dictionary() : dictionary(vector<string>())
{}

void Dictionary::AddWord(const string& word)
{
	dictionary.push_back(word);
}

void Dictionary::DeleteWord(const string& word)
{
	auto it = remove(dictionary.begin(), dictionary.end(), word);
	dictionary.erase(it, dictionary.end());
}

const string Dictionary::GetRandomWord()const
{
	if (dictionary.size())
	{
		unsigned int random_number = rand() % dictionary.size();
		return dictionary[random_number];
	}

	return "error";
}

ostream& operator<<(ostream& out, const Dictionary& item)
{
	for (const auto& v : item.dictionary)
	{
		out << v << "  ";
	}
	return out;
}

void Dictionary::SaveEncrypt(ofstream& fout)const
{
	unsigned int size = dictionary.size(), 
		mask = Mask, size_encrypt = 0;

	char mask_for_char = Mask_for_char, symbol = 0;
	
	size_encrypt = ~size;
	size_encrypt ^= mask;
	fout.write((char*)&size_encrypt, sizeof(size_encrypt));

	for (const auto v : dictionary)
	{
		size = v.size();
		size_encrypt = ~size;
		size_encrypt ^= mask;
		fout.write((char*)&size_encrypt, sizeof(size_encrypt));

		for (size_t i = 0; i < size; ++i)
		{
			symbol = v[i];
			symbol = ~symbol;
			symbol ^= mask_for_char;
			fout.put(symbol);
		}
	}
}

void Dictionary::ReadDecrypt(ifstream& fin)
{
	
	unsigned int size = 0, dictionary_size = 0, mask = Mask;
	char mask_for_char = Mask_for_char, symbol = 0;
	string tmp;

	fin.read((char*)&dictionary_size, sizeof(dictionary_size));
	dictionary_size ^= mask;
	dictionary_size = ~dictionary_size;

	for (size_t i = 0; i < dictionary_size; ++i)
	{
		tmp.resize(0);
		fin.read((char*)&size, sizeof(size));
		size ^= mask;
		size = ~size;

		for (size_t j = 0; j < size; ++j)
		{
			fin.get(symbol);
			symbol ^= mask_for_char;
			symbol = ~symbol;
			tmp += symbol;
		}
		dictionary.push_back(tmp);
	}
}