#ifndef lab_2_18_hpp
#define lab_2_18_hpp

namespace SecondLab{
struct Coordinates{
    double x;
    double y;
};

    class Astroid{
    private:
        double R;
    public:
        Astroid ();//пустой конструктор
        Astroid(double r);//инициализирующий конструктор
        Astroid& set(double r);
        double ArcLength (double t);
        double CurvatureRadius (double t);
        double WholeLength();
        double Square();
        struct Coordinates Decartes(double t);
        double y(double x);
    };
}
#endif
