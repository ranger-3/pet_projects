#include "Question.h"

const char* place_for_question{ "Место для вопроса" };
const char* required_question{ "Введите вопрос" };
const char* required_first_answer{ "Введите первый ответ он должен быть верным" };
const char* required_second_answer{ "Введите второй обязательный ответ" };
const char* additional_answer{ "Введите дополнительный ответ" };
const char* additional_answers_header{ "Добавить дополнительный ответ?" };
vector<string> additional_answers_points { "Добавить ответ", "Закончить составление вопроса" };

const string Question::GetString()const
{
	char buf[Buf_size]{};
	cin.getline(buf, sizeof(buf));
	return buf;
}

void Question::GetAndSet(const string& header, string& str)
{
	SetColor(Vanil);
	cout << endl << header << ": ";
	SetColor(White);
	str = GetString();
}

void Question::SetRightQuestion()
{
	size_t last_symbol = question.size() - 1;
	if (question[last_symbol] != '?')
	{
		question += " ?";
	}
}

const vector<string> Question::RandomSortAnswers() const
{
	vector<string> answers_points;
	size_t size = answers.size();
	int index1 = 0, index2 = 0;

	for (const auto& answer : answers)
	{
		answers_points.push_back(answer.first);
	}

	for (size_t i = 0; i < size; ++i)
	{
		index1 = rand() % size;
		index2 = rand() % size;
		swap(answers_points[index1], answers_points[index2]);
	}

	return answers_points;
}

Question::Question(const string& question, const vector<pair<string, bool>>& answers)
	:
	question(question), answers(answers)
{}

Question::Question(const string& question)
	:
	Question(question, vector<pair<string, bool>>())
{}

Question::Question()
	:
	Question(place_for_question)
{}

void Question::InitQuestion()
{
	Menu additional_questions_menu
	(additional_answers_points, additional_answers_header);
	string answer;
	bool repeat = false;

	question.resize(0);
	answers.clear();

	system("cls");
	GetAndSet(required_question, question);
	SetRightQuestion();
	system("cls");
	cout << *this << endl;
	GetAndSet(required_first_answer, answer);
	answers.push_back(make_pair(answer, true));
	system("cls");
	cout << *this << endl;
	GetAndSet(required_second_answer, answer);
	answers.push_back(make_pair(answer, false));

	do
	{
		if (repeat)
		{
			system("cls");
			cout << *this << endl;
			GetAndSet(additional_answer, answer);
			answers.push_back(make_pair(answer, false));
		}
		additional_questions_menu.RepeatMenu(repeat);
		
	} while (repeat);

}

void Question::Ask(int& key, bool& correct) const
{
	vector<string> asnwers_points = RandomSortAnswers();
	Menu question_menu(asnwers_points, question);
	string answer;
	unsigned short current_point = 1;
	int index = -1;

	question_menu.ShowAndGet(key, current_point);

	if (key == Esc)
	{
		return;
	}

	index += current_point;
	answer = asnwers_points[index];

	for (const auto& v : answers)
	{
		if (v.first == answer)
		{
			correct = v.second;
			return;
		}
	}
}

void Question::clear()
{
	question.resize(0);
	answers.clear();
}

void Question::SaveBin(ofstream& fout)const
{
	unsigned int size = question.size(), mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;

	size = ~size;
	size ^= mask;
	fout.write((char*)&size, sizeof(size));

	for (const auto& ch : question)
	{
		symbol = ~ch;
		symbol ^= mask_for_symbol;
		fout.put(symbol);
	}

	size = answers.size();
	size = ~size;
	size ^= mask;
	fout.write((char*)&size, sizeof(size));

	for (const auto& answer : answers)
	{
		size = answer.first.size();
		size = ~size;
		size ^= mask;
		fout.write((char*)&size, sizeof(size));

		for (const auto& ch : answer.first)
		{
			symbol = ~ch;
			symbol ^= mask_for_symbol;
			fout.put(symbol);
		}
		fout.write((char*)&answer.second, sizeof(answer.second));
	}
}

void Question::ReadBin(ifstream& fin)
{
	size_t i = 0, j = 0;
	unsigned int size = 0, size_str = 0, mask = Mask;
	char symbol = 0, mask_for_symbol = Mask_for_char;
	pair<string, bool> tmp;

	fin.read((char*)&size, sizeof(size));
	size ^= mask;
	size = ~size;

	question.resize(0);

	for (; i < size; ++i)
	{
		fin.get(symbol);
		symbol ^= mask_for_symbol;
		symbol = ~symbol;
		question += symbol;
	}

	fin.read((char*)&size, sizeof(size));
	size ^= mask;
	size = ~size;

	for (i = 0; i < size; ++i)
	{		
		fin.read((char*)&size_str, sizeof(size_str));
		size_str ^= mask;
		size_str = ~size_str;
		tmp.first.resize(0);

		for (j = 0; j < size_str; ++j)
		{
			fin.get(symbol);
			symbol ^= mask_for_symbol;
			symbol = ~symbol;
			tmp.first += symbol;
		}
		fin.read((char*)&tmp.second, sizeof(tmp.second));
		answers.push_back(tmp);
	}
}

ostream& operator<<(ostream& out, const Question& item)
{
	SetColor(Vanil);
	cout << "\n\t" << item.question;
	SetColor(White);

	for (const auto& answer : item.answers)
	{
		cout << "\n\n\t" << answer.first;
	}
	return out;
}
