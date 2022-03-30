//Вариант 6.
//1.Разработать класс "двоичный сигнал" в соответствии со следующим заданием :
//Состояние класса -
//Двоичный сигнал определяется последовательностью состояний сигнала(значение уровня и длительность типа char 
//в условных единицах).Для описания состояния сигнала целесообразно использовать структуру.Память под массив 
//структур выделяется статически, во время компиляции, и задается массивом фиксированного размера.Задаётся 
//максимальная длительность сигнала.
//
//Протокол класса -
//Определяет возможности создания и инициализации экземпляров класса и правила их использования(методы класса).
//Предусмотреть следующие возможности :
//·  ++        пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию;
//·  ++        создание экземпляров класса с инициализацией постоянным уровнем сигнала(уровень 0 или 1 на 
//				максимальную длительность);			////длительность 1
//·  ++        создание экземпляров класса с инициализацией сигналом как строки символов;
//·   +       ввод экземпляров класса из входного потока и вывод;
//·  ++        инвертировать сигнал;
//·  ++        дополнение сигнала другим сигналом;
//·  +        вставка в определённый момент времени(тип int) другого сигнала;
//·  ++        копирование сигнала определённое число раз;		
//·  +        удаление фрагмента сигнала в определенное время(тип int) определённой длительности.

//тесты на динамику (корректное и некорректное значения)

#include "DoubleSignal.h"
#include <iostream>
#include <cmath>
#include <exception>
#include <string>
using namespace std;

void PrintDialog(string array[]);

void Dialog(DoubleSignal& db);

int main()
{
	DoubleSignal db;
	Dialog(db);

	return 0;
}

void Dialog(DoubleSignal& db)
{
	string array[11] = {
		"\n0. Create DoubleSignal",
		"1. Create DoubleSignal with constant signal level",
		"2. Create DoubleSignal by string",
		"3. Add new signal",
		"4. Copy DoubleSignal a certain number of times",
		"5. Invert DoubleSignal",
		"6. Complement a DoubleSignal with another DoubleSignal",
		"7. Insertion at a certain point in time of another DoubleSignal",
		"8. Remove fragment of DoubleSignal at a certain time of a certain duration",
		"9. Print DoubleSignal",
		"10. Exit\n"
	};
	while (true)
	{
		try {
		int num;
		PrintDialog(array);
		cin >> num;
		if (num == 0)
		{
			DoubleSignal temp;
			db = temp;
		}
		if (num == 1)
		{
			char sig;
			cout << "Enter signal (0 or 1): ";
			cin >> sig;
			DoubleSignal temp(sig);
			db = temp;
		}
		if (num == 2)
		{
			string str;
			cout << "Enter string (0 and 1): ";
			cin >> str;
			DoubleSignal temp(str);
			db = temp;
		}
		if (num == 3)
		{
			cout << "Enter new signal (0 or 1) and time of signal: ";
			cin >> db;
		}
		if (num == 4)
		{
			int count;
			cout << "Enter number of copy: ";
			cin >> count;
			db.Copy(count);
		}
		if (num == 5)
		{
			db.Reverse();
		}
		if (num == 6)
		{
			string str;
			cout << "Enter subsequence of 0 and 1 (new DoubleSignal): ";
			cin >> str;
			DoubleSignal temp(str);
			db += temp;
		}
		if (num == 7)
		{
			int ins_time;
			string str;
			cout << "Enter point in time: ";
			cin >> ins_time;
			cout << "Enter subsequence of 0 and 1 (new DoubleSignal): ";
			cin >> str;
			DoubleSignal temp(str);
			db.Insert(temp, ins_time);
		}
		if (num == 8)
		{
			int time;
			int duraction;
			cout << "Enter point of time: ";
			cin >> time;
			cout << "Enter duraction: ";
			cin >> duraction;
			db.Delete(time, duraction);
		}
		if (num == 9)
		{
			cout << db;
		}
		if (num == 10)
		{
			break;
		}
		}
		catch (const exception &exception)
		{
			cerr << "Error: " << exception.what() << endl;
		}
	}
}
void PrintDialog(string array[]) {
	for (size_t i = 0; i < 11; i++)
	{
		cout << array[i] << endl;
	}
}
