#include "QuestionList.h"

const char* questions_header{ "Добавить вопрос?" };
vector<string> questions_points{"Добавить вопрос", "Закончить составление вопросов"};

void QuestionList::Init()
{
	Menu questions_menu(questions_points, questions_header);
	Question question;
	bool repeat = true;

	while (repeat)
	{
		question.InitQuestion();
		questions.push_back(question);
		questions_menu.RepeatMenu(repeat);
	}
}

void QuestionList::DeleteLast()
{
	questions.pop_back();
}

void QuestionList::Testing(int& key, int& right_answers_counter, int& current_question)const
{
	right_answers_counter = 0;
	bool correct = false;
	int i = current_question;
	size_t size = questions.size();

	for (; i < size; ++i)
	{
		questions[i].Ask(key, correct);
		if (key == Esc)
		{
			return;
		}

		if (correct)
		{
			++right_answers_counter;
		}
		++current_question;
	}
}

void QuestionList::ShowQuestions() const
{
	for (const auto& question : questions)
	{
		cout << '\t' << question.GetQuestion() << "\n\n";
	}
}

void QuestionList::SaveBin(ofstream& fout)const
{
	size_t size = questions.size();
	fout.write((char*)&size, sizeof(size));
	for (const auto& question : questions)
	{
		question.SaveBin(fout);
	}
}

void QuestionList::ReadBin(ifstream& fin)
{
	size_t size = 0, i = 0;
	Question question;
	fin.read((char*)&size, sizeof(size));
	for (; i < size; ++i)
	{
		question.clear();
		question.ReadBin(fin);
		questions.push_back(question);
	}
}