#include "Solution.h"


std::vector<double> Solution::GaussMeth(std::vector<std::vector<double>>& matr, std::vector<double>& b){
    double d, s;
    size_t n = matr.size();
    std::vector<double> res(n);
    for (size_t k = 0; k < n; ++k)
    {
        double max_el = DBL_MIN;
        size_t index = 0;
        for (size_t i = k; i < n; ++i)
        {
            if (max_el < std::fabs(matr[i][k]))
            {
                max_el = std::fabs(matr[i][k]);
                index = i;
            }
        }
        if(index != k)
        {
            for(size_t i = 0; i < n; ++i)
            {
                double temp = matr[index][i];
                matr[index][i] = matr[k][i];
                matr[k][i] = temp;
            }
            double t = b[index];
            b[index] = b[k];
            b[k] = t;
        }
        for (size_t j = k + 1; j < n; ++j)
        {
            
            d = matr[j][k] / matr[k][k];
            for (size_t i = k; i < n; ++i)
            {
                matr[j][i] = matr[j][i] - d * matr[k][i];
            }
            b[j] = b[j] - d * b[k];
        }
    }
    for (size_t k = n - 1; k >= 0; --k)
    {
        d = 0;
        for (size_t j = k; j < n; ++j)
        {
            s = matr[k][j] * (k == n - 1 ? 0 : res[j]);
            d += s;
        }

        res[k] = (b[k] - d) / matr[k][k];
        if(k == 0){
            break;
        }
    }


    return res;
}

void Solution::LogSplines(const std::vector<double>& coeffs){
    size_t row_number = 1;
    std::cout << "The splines are: \n";
    std::vector<double> spline;
    auto it = coeffs.begin();
    while(it != coeffs.end()){
        std::copy(it, it + 3, std::back_inserter(spline));
        std::string log = "";
        bool first = true;
        for(size_t i = 0; i < spline.size(); ++i){
            std::string number = "";
            std::stringstream ss;
            ss.setf(std::ios::fixed);
            ss.precision(2);
            if(spline[i] == 0){
                continue;
            }
            if(spline[i] > 0 && !first){
                ss << "+ " <<  spline[i];
            }
            else{
               ss <<  spline[i];
               first = false;
            }
            std::getline(ss, number);
            switch (i)
            {
            case 0:
                log += number + "x^2 ";
                break;
            case 1:
                log += number + "x ";
                break;
            case 2:
                log += number;
                break;
            default:
                throw std::exception("Check the spline");
            }
        }
        std::cout << "\t" << row_number++ << ") " << log << std::endl;
        it = it + 3;
        spline.clear();
    }
}
void Solution::Task2(){
    std::vector<std::vector<double>> matrix(12, std::vector<double>(12));
    std::vector<double> x = {1, 2, 3, 4, 5}, f_x;
    auto f = [](const double& x){
        return 2.0*std::pow(x, 7) + 4.0*std::pow(x, 4) + 5.0*std::pow(x, 2) - 7.0;
    };
    for(const auto& i: x){
        f_x.push_back(f(i));
    }
    matrix = {
        {1,1,1,0,0,0,0,0,0,0,0,0},
        {4,2,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,4,2,1,0,0,0,0,0,0},
        {0,0,0,9,3,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,9,3,1,0,0,0},
        {0,0,0,0,0,0,16,4,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,16,4,1},
        {0,0,0,0,0,0,0,0,0,25,5,1},
        {4,1,0,-2,-1,0,0,0,0,0,0,0},
        {0,0,0,6,1,0,-6,-1,0,0,0,0},
        {0,0,0,0,0,0,8,1,0,-8,-1,0},
        {1,0,0,0,0,0,0,0,0,0,0,0}
    };
    std::vector<double> b = {4,397,397,5384,5384,36'937,36'937,168'868,0,0,0,0};
    auto result = Solution::GaussMeth(matrix, b);
    result[0] = 0.0;
    LogSplines(result);
}
double Solution::Task1(double value){
    auto f = [](double x){
        return 8.0* std::pow(x, 12) + 5.0*std::pow(x, 10) + 10.0* std::pow(x, 9);
    };
    
    double res = 0;
    std::vector<double> x = {0, 0.2, 0.4, 0.5, 0.6, 0.8, 1}, f_x, coeffs;
    for(const auto& i: x){
        f_x.push_back(f(i));
    }
    size_t i = 0, j = 1;
    size_t controller = 0;
    size_t n = x.size();
    while(f_x.size() > 1){
        std::vector<double> values;
        while(j < x.size()){
            values.push_back((f_x[j - controller] - f_x[i])/(x[j] - x[i]));
            ++j;
            ++i;
        }
        coeffs.push_back(f_x.front());
        f_x = values;
        ++controller;
        i = 0;
        j = 1 + controller;
    }
    double f_value = f(value);
    std::vector<double> multiplies;
    double coffs_value = coeffs.front();
    for(size_t k = 0; k < x.size() - 2; ++k){
        if(multiplies.size() == 0){
            multiplies.push_back(value - x[k]);
            continue;
        }

        multiplies.push_back(multiplies[multiplies.size() - 1] * (value - x[k]));
    }
    for(size_t k = 0; k < multiplies.size(); ++k){
        coffs_value += (coeffs[k + 1] * multiplies[k]);
    }
    std::cout << coffs_value << " " << f_value << std::endl; 
    return std::fabs(f_value - coffs_value);
}