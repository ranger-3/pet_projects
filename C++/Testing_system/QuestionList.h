#pragma once

#include <list>
#include "Question.h"

class QuestionList
{
	vector<Question> questions;

public:

	const size_t Amount()const { return questions.size(); }
	void Clear() { questions.clear(); }
	void Init();
	void DeleteLast();
	void Testing(int& key, int& right_answers_counter, int& current_question)const;
	void ShowQuestions()const;
	void SaveBin(ofstream& fout)const;
	void ReadBin(ifstream& fin);
};

