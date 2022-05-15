#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <string>
#include <iomanip>
#include <sstream>

class Solution{
private:
    static void LogResult(double result);
    static void LogSplines(const std::vector<double>& coeffs); 
    static std::vector<double> GaussMeth(std::vector<std::vector<double>>& matr, std::vector<double>& b);
public:
    static double Task1(double value);
    static void Task2();
};