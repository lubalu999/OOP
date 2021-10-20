#include "pch.h"
#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

#define M_PI 3.14
#define OPTIONS_NUMBER 6

namespace SecondLab {
	struct Coordinates {
		double x;
		double y;
	};

	class Astroid {
	private:
		double R;
	public:
		Astroid();//пустой конструктор
		Astroid(double r);//инициализирующий конструктор
		Astroid& set(double r);
		double ArcLength(double t) const;
		double CurvatureRadius(double t) const;
		double WholeLength() const;
		double Square() const;
		struct Coordinates Decartes(double t) const;
		double y(double x) const;
	};

	Astroid::Astroid() {
		R = 4.0;
	}
	Astroid::Astroid(double r) {
		if (r <= 0)
			throw std::invalid_argument("Invalid input");
		R = 4 * r;
	}
	Astroid& Astroid::set(double r) {
		if (r <= 0)
			throw std::invalid_argument("Invalid input");
		R = 4 * r;
		return *this;
	}
	double Astroid::ArcLength(double t) const {
		double res;
		double a = t >= 0 ? t : -t;
		if (a <= 2 * M_PI)
		{
			int k = int(2 * a / M_PI);
			res = k * 1.5*R + 1.5*R*sin(t)*sin(t);				//k*1.5*R - 1/4 всей кривой
		}
		else
			res = 6 * R;
		return res;
	}

	double Astroid::WholeLength() const {
		return 6 * R;
	}

	double Astroid::CurvatureRadius(double t) const {
		return abs(1.5*R*sin(2 * t));
	}

	double Astroid::Square() const {
		return 3. / 8 * M_PI*R*R;
	}

	struct Coordinates Astroid::Decartes(double t) const {
		struct Coordinates point;
		point.x = R * cos(t)*cos(t)*cos(t);
		point.y = R * sin(t)*sin(t)*sin(t);
		return point;
	}

	double Astroid::y(double x) const {				
		double x0 = x > 0 ? x : -x;
		if (R >= x0)
			return pow((pow(R, 2.0 / 3) - pow(x0, 2. / 3)), 1.5);
		else
			throw std::invalid_argument("Invalid input");
	}

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

TEST(Astroid_Constructor, Default_Constructor) {
	Astroid astroid;
	ASSERT_NO_THROW(astroid);
	ASSERT_EQ(18.84, astroid.Square());
	ASSERT_EQ(24, astroid.WholeLength());
}

TEST(Astroid_Constructor, Initial_Constructor) {
	Astroid astroid_0(2);
	ASSERT_NO_THROW(astroid_0);
	ASSERT_EQ(75.36, astroid_0.Square());
	ASSERT_EQ(48, astroid_0.WholeLength());
	ASSERT_ANY_THROW(Astroid astroid_1(-1.09));
	ASSERT_ANY_THROW(Astroid astroid_2(0));
}

TEST(Astroid_Methods, Setters) {
	Astroid astroid;
	ASSERT_NO_THROW(astroid.set(4.23));
	ASSERT_NEAR(101.52, astroid.WholeLength(), 0.001);				
	ASSERT_NEAR(337.102, astroid.Square(), 0.001);					
	ASSERT_ANY_THROW(astroid.set(-10));
}

TEST(Astroid_Methods, Arc_Length) {
	Astroid astroid(0.34);
	int k = int(2 * 2 / M_PI);
	double res = k * 1.5*0.34*4 + 1.5*0.34*4*sin(2)*sin(2);
	ASSERT_EQ(res, astroid.ArcLength(2));
}

TEST(Astroid_Methods, Curvature_Radius) {
	Astroid astroid(5.3);
	double r = abs(1.5*5.3*4*sin(2 * 1));
	ASSERT_EQ(r, astroid.CurvatureRadius(1));
}

TEST(Astroid_Methods, Decartes_Coordinates) {
	Coordinates point;
	Astroid astroid(2.28);
	point.x = 9.12*cos(1)*cos(1)*cos(1);
	point.y = 9.12*sin(1)*sin(1)*sin(1);
	ASSERT_EQ(point.x, astroid.Decartes(1).x);
	ASSERT_EQ(point.y, astroid.Decartes(1).y);
}

TEST(Astroid_Methods, Y_Coordinate) {
	Astroid astroid(6.84);
	ASSERT_NEAR(16.834, astroid.y(3.98), 0.001);					
	ASSERT_NO_THROW(astroid.y(-9));
	ASSERT_ANY_THROW(astroid.y(-100));
	ASSERT_NO_THROW(astroid.y(0.99));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}