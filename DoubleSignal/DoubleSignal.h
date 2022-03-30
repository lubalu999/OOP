#pragma once
#include <string>

bool CheckSignal(int sig);
bool CheckSubsequence(std::string str);

struct Signal
{
	char level;			//0 или 1
	int time;			//длительность текущего сигнала
};

class DoubleSignal
{
private:
	Signal *signals;
	int current_time;
	int num_of_signals;
public:
	DoubleSignal();
	DoubleSignal(unsigned char signal);
	DoubleSignal(std::string buf);
	DoubleSignal(const DoubleSignal& other);
	DoubleSignal(DoubleSignal&& x);
	~DoubleSignal();
	void Copy(int number_of_times_to_copy);
	void Reverse();
	void Insert(const DoubleSignal& other, int ins_time);
	void Delete(int start_time, int duration);
	void AddSignal(char sig, int tm);

	int GetCurrentTime() const
	{
		return current_time;
	}
	int GetNumberOfElements() const
	{
		return num_of_signals;
	}
	std::string GetString() const
	{
		std::string str = "";
		for (int i = 0; i < num_of_signals; i++)
		{
			str += signals[i].level;
		}
		return str;
	}

	DoubleSignal& operator += (const DoubleSignal& other);
	DoubleSignal operator + (const DoubleSignal& other);
	Signal& operator [] (const int index);
	DoubleSignal& operator = (const DoubleSignal& x);
	DoubleSignal& operator = (DoubleSignal&& x);
	friend std::ostream& operator << (std::ostream &out, const DoubleSignal& dbsignal);
	friend std::istream& operator >> (std::istream& is, DoubleSignal& db);
};