#include "dialog.hpp"

#define OPTIONS_NUMBER 6

namespace SecondLab{
    typedef void(*opt_t)(Astroid&);
    
    static const opt_t options[OPTIONS_NUMBER] = {
        &GetFullInfo,
        &SetRadius,
        &GetArcLength,
        &GetCurvantureRadius,
        &GetDecartesCoordinates,
        &GetY
    };

    int Dialog (Astroid& astroid){
        int choice = 0;
        std::cout << "------------------------------------------------------------" << std::endl;
        while(1){
            print_menu();
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout<<"Your choice: ";
            getNum(choice);
            std::cout << "------------------------------------------------------------" << std::endl;
            if (!choice){
                return choice;
            }
            else if (choice < 0 || choice > OPTIONS_NUMBER){
                throw std::invalid_argument ("Invalid input");
            }
            else{
                options[choice-1](astroid);
            }
            std::cout << "------------------------------------------------------------" << std::endl;
        }
    }

    void print_menu(){
        std::cout<<"----------------------------------------------------------------"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;
        std::cout<<"1. Info"<<std::endl;
        std::cout<<"2. Set radius (Please mention, you'll set the value times four)"<<std::endl;
        std::cout<<"3. Get length of the arc depended on your angle"<<std::endl;
        std::cout<<"4. Get the radius of curvanture"<<std::endl;
        std::cout<<"5. Get the decartes coordinates"<<std::endl;
        std::cout<<"6. Get the y-coordinate"<<std::endl;
    }

    void GetFullInfo(Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Whole length of line: "<<astroid.WholeLength() <<std::endl;
        std::cout << "Square inside the astroid: "<<astroid.Square() << std::endl;
    }

    void SetRadius(Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        double r;
        std::cout << "Set the new radius: ";
        getNum(r);
        astroid.set(r);
    }

    void GetArcLength (Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        double t;
        std::cout << "Print the angle: ";
        getNum(t);
        std::cout << "The length of arc is " << astroid.ArcLength(t) << std::endl;
    }

    void GetCurvantureRadius (Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        double t;
        std::cout << "Print the angle: ";
        getNum(t);
        std::cout << "The radius of curvanture is " << astroid.CurvatureRadius(t) << std::endl;
    }

    void GetDecartesCoordinates (Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        double t;
        std::cout << "Print the angle: ";
        getNum(t);
        struct Coordinates point = astroid.Decartes(t);
        std::cout << "The coordinates are (" << point.x <<", "<< point.y << ")" <<std::endl;
    }

    void GetY (Astroid &astroid){
        std::cout << "------------------------------------------------------------" << std::endl;
        double x;
        std::cout << "Print the X-coordinate: ";
        getNum(x);
        try{
            astroid.y(x);
        }
        catch (const std::invalid_argument& er){
            std::cout << er.what() << std::endl;
        }
        std::cout << "The Y-coordinate is " << astroid.y(x) << std::endl;
    }
}