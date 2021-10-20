#define _USE_MATH_DEFINES

#include "lab_2_18.hpp"
#include <cmath>
#include <stdexcept>
namespace SecondLab{
    Astroid::Astroid(){
        R = 4.;
    }
    Astroid::Astroid(double r){
        if (r <= 0)
            throw std::invalid_argument ("Invalid input");
        R = 4*r;
    }
    Astroid& Astroid::set(double r){
        if (r <= 0)
            throw std::invalid_argument ("Invalid input");
        R = 4*r;
        return *this;
    }
    double Astroid::ArcLength (double t){
        double res;
        double a = t>=0?t:-t;
        if (a <= 2*M_PI)
        {
        int k = int(2*t/M_PI);
        res = k*1.5*R+1.5*R*sin(t)*sin(t);
        }
        else
            res = 6*R;
        return res;
    }

    double Astroid::WholeLength(){
        return 6*R;
    }
    
    double Astroid::CurvatureRadius (double t){
        return 1.5*R*sin(2*t);
    }

    double Astroid::Square(){
        return 3./8*M_PI*R*R;
    }

    struct Coordinates Astroid::Decartes (double t){
        struct Coordinates point;
        point.x = R*cos(t)*cos(t)*cos(t);
        point.y = R*sin(t)*sin(t)*sin(t);
        return point;
    }

    double Astroid::y(double x){
        double x0 = x>0?x:-x;
        if (R >= x0)
            return pow((pow(R, 2./3)-pow(x0, 2./3)), 1.5);
        else
            throw std::invalid_argument ("Invalid input");
    }
}