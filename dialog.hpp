#ifndef dialog_hpp
#define dialog_hpp

#include <iostream>
#include "lab_2_18.hpp"
namespace SecondLab {
    
    int Dialog (Astroid &astroid);
    void print_menu();
    void GetFullInfo (Astroid &astroid);
    void SetRadius (Astroid &astroid);
    void GetArcLength (Astroid &astroid);
    void GetCurvantureRadius (Astroid &astroid);
    void GetDecartesCoordinates (Astroid &astroid);
    void GetY (Astroid &astroid);
    template <class T>
        int getNum(T &a){
            std::cin>>a;
            if (!std::cin.good()){
                return -1;
            }
            return 1;
        }
}
#endif /* dialog_hpp */
