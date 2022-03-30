#include "DoubleSignal.h"
#include <iostream>
#include <cmath>
#include <exception>

using namespace std;


void DoubleSignal::Copy(int number_of_times_to_copy) {			
	if (number_of_times_to_copy > 0) {
		Signal* temp = signals;
		signals = new Signal[num_of_signals * (number_of_times_to_copy + 1)];
		int n = num_of_signals;

		for (int i = 0; i < num_of_signals; i++)
		{
			signals[i].level = temp[i].level;
			signals[i].time = temp[i].time;
		}

		while (number_of_times_to_copy--) {
			int m = num_of_signals;
			for (int i = m, k = 0; i < m + n; i++, k++)
			{
				signals[i].time = signals[k].time;
				current_time += signals[k].time;

				signals[i].level = signals[k].level;
				num_of_signals++;
			}
		}
	}

}
void DoubleSignal::Reverse() {			
	for (int i = 0; i < this->num_of_signals; i++)
	{
		if (this->signals[i].level == '0')
			this->signals[i].level = '1';
		else
			this->signals[i].level = '0';
	}
}
void DoubleSignal::Insert(const DoubleSignal& other, int ins_time)		
{
	Signal* temp = signals;
	signals = new Signal[num_of_signals + other.num_of_signals];

	int i = 0;
	int count_time = 0;
	while (ins_time > count_time && i < num_of_signals)		//добавили начальные сигналы
	{
		signals[i].level = temp[i].level;
		signals[i].time = temp[i].time;
		count_time += signals[i].time;
		i++;
	}

	int j, k;
	for (j = i, k = 0; k < other.num_of_signals; j++, k++)		//добавили новый сигнал в середину
	{
		signals[j].level = other.signals[k].level;
		signals[j].time = other.signals[k].time;
		current_time += other.signals[k].time;
		num_of_signals++;
	}

	while (j < num_of_signals)			//добавили оставшиеся сигналы
	{
		signals[j].level = temp[i].level;
		signals[j].time = temp[i].time;
		i++;		//итерируемся по temp
		j++;		//итерируемся по signals
	}
}
void DoubleSignal::Delete(int start_time, int duration)		
{
	if (start_time >= 0 && duration > 0) {
		Signal* temp = signals;

		int i = 0;
		int count_time = 0;
		int new_current_time = 0;
		while (start_time > count_time && i < num_of_signals)			//ищем откуда вырезать
		{
			count_time += temp[i].time;
			i++;
		}			//i - откуда будем удалять

		//теперь посчитаем, сколько элементов будем удалять, чтобы перевыделить память 
		int counter = 0, j = i, k = i;
		while (duration > 0 && j < num_of_signals)
		{
			duration -= temp[j].time;
			new_current_time += temp[j].time;
			counter++;
			j++;
		}

		if (i == num_of_signals) return;				//если удалять надо с конца, то выходим

		Signal* ptr = signals;
		signals = new Signal[num_of_signals - counter];

		for (int i = 0; i < k; i++)					//перезаписываем сигналы
		{
			signals[i].level = ptr[i].level;
			signals[i].time = ptr[i].time;
		}

		int t = counter + k;								//с этого сигнала будем вставлять
		for (int l = k; l < num_of_signals - counter - k + 2; l++, t++)			//дозаписываем оставшиеся сигналы
		{
			signals[l].level = ptr[t].level;
			signals[l].time = ptr[t].time;
		}
		current_time -= new_current_time;
		num_of_signals -= counter;
	}
	else
		throw invalid_argument("uncorrect argument");
}
void DoubleSignal::AddSignal(char sig, int tm)			
{
	if (!CheckSignal(sig))
		throw invalid_argument("Signal is uncorrect");
	else {
		Signal* temp = signals;
		signals = new Signal[num_of_signals + 1];

		for (int i = 0; i < num_of_signals; i++)
		{
			signals[i].level = temp[i].level;
			signals[i].time = temp[i].time;
		}

		signals[num_of_signals].level = sig;
		signals[num_of_signals].time = tm;
		current_time += tm;
		num_of_signals++;
		delete[] temp;
	}
}

istream& operator >> (istream& is, DoubleSignal& db)		
{
	char sim;
	int tm;
	is >> sim >> tm;

	if (CheckSignal((int)sim) && tm > 0) {
		Signal* temp = db.signals;
		db.signals = new Signal[db.num_of_signals + 1];

		for (int i = 0; i < db.num_of_signals; i++)
		{
			db.signals[i].level = temp[i].level;
			db.signals[i].time = temp[i].time;
		}

		db.signals[db.num_of_signals].level = sim;
		db.signals[db.num_of_signals].time = tm;
		db.current_time += tm;
		db.num_of_signals++;
		delete[] temp;
	}
	else 
		throw invalid_argument("Signal is uncorrect");
	return is;
}

ostream& operator << (ostream &out, const DoubleSignal& dbsignal) {		//+
	for (int i = 0; i < dbsignal.num_of_signals; i++)
	{
		out << dbsignal.signals[i].level << ' ' << dbsignal.signals[i].time << endl;
	}
	out << "Current time - " << dbsignal.current_time << endl;
	out << "Number of sigmals - " << dbsignal.num_of_signals << endl << endl;

	return out;
}

Signal& DoubleSignal::operator [] (const int index) {		
	if (index < num_of_signals && index >= 0)
		return (signals[index]);
	else
		throw invalid_argument("Uncorrect index");
}

DoubleSignal DoubleSignal::operator + (const DoubleSignal& other)		
{
	DoubleSignal temp;
	temp = *this;
	temp += other;
	return temp;
}

DoubleSignal& DoubleSignal::operator += (const DoubleSignal& other) {		
	Signal* temp = signals;
	signals = new Signal[num_of_signals + other.num_of_signals];

	for (int i = 0; i < num_of_signals; i++)
	{
		signals[i].level = temp[i].level;
		signals[i].time = temp[i].time;
	}

	int n = num_of_signals;
	int m = other.num_of_signals;
	for (int i = n, k = 0; i < n + m; i++, k++) {
		signals[i].level = other.signals[k].level;
		signals[i].time = other.signals[k].time;
		current_time += other.signals[k].time;
		num_of_signals++;
	}

	delete[] temp;

	return *this;
}

DoubleSignal::~DoubleSignal()
{
	delete[] signals;
}

DoubleSignal::DoubleSignal() {			
	signals = new Signal[0];
	num_of_signals = 0;
	current_time = 0;
}

DoubleSignal::DoubleSignal(unsigned char signal) {		//+
	if (CheckSignal((int)signal)) {
		signals = new Signal[1];
		num_of_signals = 1;
		signals[0].level = signal;
		signals[0].time = 1;	//сигнал один и определен на всем времени
		current_time = 1;
	}
	else
		throw invalid_argument("Uncorrect signal!");
}

DoubleSignal::DoubleSignal(string buf) {

	if (CheckSubsequence(buf))
	{
		signals = new Signal[buf.size()];
		num_of_signals = 0;
		current_time = 0;
		for (char i : buf) {
			signals[num_of_signals].level = i;
			signals[num_of_signals].time = 1;			//по умолчанию длительность одного сигнала = 1
			current_time++;
			num_of_signals++;
		}
	}
	else
		throw invalid_argument("Uncorrect string! Try again");
}

DoubleSignal::DoubleSignal(const DoubleSignal& other)		
{
	signals = new Signal[other.num_of_signals];
	current_time = other.current_time;
	num_of_signals = other.num_of_signals;

	for (int i = 0; i < num_of_signals; i++)
	{
		signals[i].level = other.signals[i].level;
		signals[i].time = other.signals[i].time;
	}
}

DoubleSignal::DoubleSignal(DoubleSignal&& x) : signals(x.signals)
{
	current_time = x.current_time;
	num_of_signals = x.num_of_signals;
	x.signals = nullptr;
}

DoubleSignal& DoubleSignal::operator = (const DoubleSignal& other)
{
	if (&other == this)						// Проверка на самоприсваивание
		return *this;

	delete[] signals;						// Удаляем всё, что к этому моменту может хранить указатель 

	signals = new Signal[other.num_of_signals];			// Копируем передаваемый объект
	current_time = other.current_time;
	num_of_signals = other.num_of_signals;

	for (int i = 0; i < num_of_signals; i++)
	{
		signals[i].level = other.signals[i].level;
		signals[i].time = other.signals[i].time;
	}
	return *this;
}

DoubleSignal& DoubleSignal::operator = (DoubleSignal&& x)
{
	if (&x == this)				// Проверка на самоприсваивание
		return *this;

	delete[] signals;			// Удаляем всё, что к этому моменту может хранить указатель

	signals = x.signals;
	current_time = x.current_time;
	num_of_signals = x.num_of_signals;

	x.signals = nullptr;

	return *this;
}

bool CheckSignal(int sig) {
	return (sig == 48) || (sig == 49);
}
bool CheckSubsequence(string str) {
	bool res = 1;
	for (char t : str) {
		if (t == '1' || t == '0')
			continue;
		else {
			res = 0;
			break;
		}
	}
	return res;
}