#pragma once
#define OPTIONS_NUMBER 6
#define M_PI 3.14

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
}