#include <iostream>
#include "Solution.h"

enum class Tasks{
    Task1,
    Task2
};

int main(){
    while(true){
        int number = 0;
        std::cout << "Enter the number of the task or \"-1\" to end programme > ";
        std::cin >> number;
        //number = 2;
        if(number == -1){
            break;
        }
        --number;
        Tasks ts = static_cast<Tasks>(number);
        switch (ts)
        {
        case Tasks::Task1:{
            auto res = Solution::Task1(0.5);
            std::string s;
            std::stringstream sstream;
            sstream.setf(std::ios::fixed);
            sstream.precision(4);
            sstream << res;
            s = sstream.str();
            std::cout << "The calculation difference is " << s << std::endl;
            break;
        }
        case Tasks::Task2:{
            Solution::Task2();   
            break;
        }
        }
    }
    return 0;
}