#include "Astroid.h"
#include <cmath>
#include <stdexcept>

namespace SecondLab {
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

	double Astroid::y(double x) const {				//выводить 2
		double x0 = x > 0 ? x : -x;
		if (R >= x0)
			return pow((pow(R, 2.0 / 3) - pow(x0, 2. / 3)), 1.5);
		else
			throw std::invalid_argument("Invalid input");
	}
}