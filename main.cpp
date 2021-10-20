/*Вариант 18. Астроида
Разработать класс, определяющий кривую – астроиду.
Астроида – плоская кривая, описываемая точкой окружности радиуса r, катящейся по внутренней стороне окружности радиуса R = 4r.
1) Определить состояние класса.
2) Разработать необходимые конструкторы и методы получения и изменения параметров, определяющих кривую.
3) Вернуть длину дуги от точки 0 до заданного угла t.
4) Вернуть длину всей кривой.
5) Вернуть радиус кривизны в зависимости от заданного угла t.
6) Вернуть площадь, ограниченную кривой.
7) Вернуть значения координат x и y в зависимости от заданного параметра t.
8) Вернуть значение координаты y в декартовой системе координат в зависимости от заданного значения x.
Разработать диалоговую программу для тестирования класса.*/

//#include "gtest.h"
#include "Astroid.h"
#include <iostream>
#include <cmath>
#include <stdexcept>


namespace SecondLab {
	
	int Dialog(Astroid &astroid);
	void print_menu();
	void GetFullInfo(Astroid &astroid);
	void SetRadius(Astroid &astroid);
	void GetArcLength(Astroid &astroid);
	void GetCurvantureRadius(Astroid &astroid);
	void GetDecartesCoordinates(Astroid &astroid);
	void GetY(Astroid &astroid);
	template <class T>
	int getNum(T &a) {
		std::cin >> a;
		if (!std::cin.good()) {
			return -1;
		}
		return 1;
	}

	typedef void(*opt_t)(Astroid&);

	static const opt_t options[OPTIONS_NUMBER] = {
		&GetFullInfo,
		&SetRadius,
		&GetArcLength,
		&GetCurvantureRadius,
		&GetDecartesCoordinates,
		&GetY
	};

	int Dialog(Astroid& astroid) {
		int choice = 0;
		std::cout << "------------------------------------------------------------" << std::endl;
		while (1) {
			print_menu();
			std::cout << "------------------------------------------------------------" << std::endl;
			std::cout << "Your choice: ";
			getNum(choice);
			std::cout << "------------------------------------------------------------" << std::endl;
			if (!choice) {
				return choice;
			}
			else if (choice < 0 || choice > OPTIONS_NUMBER) {
				throw std::invalid_argument("Invalid input");
			}
			else {
				options[choice - 1](astroid);
			}
			std::cout << "------------------------------------------------------------" << std::endl;
		}
	}

	void print_menu() {
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Info" << std::endl;
		std::cout << "2. Set radius (The entered value will be multiplied by 4)" << std::endl;
		std::cout << "3. Get length of the arc depended on your angle" << std::endl;
		std::cout << "4. Get the radius of curvanture" << std::endl;
		std::cout << "5. Get the decartes coordinates" << std::endl;
		std::cout << "6. Get the y-coordinate" << std::endl;
	}

	void GetFullInfo(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cout << "Whole length of line: " << astroid.WholeLength() << std::endl;
		std::cout << "Square inside the astroid: " << astroid.Square() << std::endl;
	}

	void SetRadius(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		double r;
		std::cout << "Set the new radius: ";
		getNum(r);
		astroid.set(r);
	}

	void GetArcLength(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		double t;
		std::cout << "Print the angle: ";
		getNum(t);
		std::cout << "The length of arc is " << astroid.ArcLength(t) << std::endl;
	}

	void GetCurvantureRadius(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		double t;
		std::cout << "Print the angle: ";
		getNum(t);
		std::cout << "The radius of curvanture is " << astroid.CurvatureRadius(t) << std::endl;
	}

	void GetDecartesCoordinates(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		double t;
		std::cout << "Print the angle: ";
		getNum(t);
		struct Coordinates point = astroid.Decartes(t);
		std::cout << "The coordinates are (" << point.x << ", " << point.y << ")" << std::endl;
	}

	void GetY(Astroid &astroid) {
		std::cout << "------------------------------------------------------------" << std::endl;
		double x;
		std::cout << "Print the X-coordinate: ";
		getNum(x);
		try {
			astroid.y(x);
		}
		catch (const std::invalid_argument& er) {
			std::cout << er.what() << std::endl;
		}
		std::cout << "The Y-coordinate is " << astroid.y(x) << std::endl;
		std::cout << "The Y-coordinate is " << -astroid.y(x) << std::endl;
	}
}

using namespace SecondLab;

int main() {
	int choice = 7;
	while (choice)
	{
		try {
			Astroid astroid;
			choice = Dialog(astroid);
		}
		catch (const std::invalid_argument &er) {
			std::cout << er.what() << std::endl;
		}
	}
	return 0;
}