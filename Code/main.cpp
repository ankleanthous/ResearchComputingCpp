// pLaplace equation (C++)
// ======================

#include <dolfin.h>
#include "pLaplace.h"
#include <ufc.h>
#include <iostream>
#include "problem_classes.h"

#include "catch.hpp"

using namespace dolfin;

//// Source term (right-hand side)
//class Source : public Expression
//{
//  void eval(Array<double>& values, const Array<double>& x) const
//  {
//    double dx = x[0] - 0.5;
//    double dy = x[1] - 0.5;
//    values[0] = 10*exp(-(dx*dx + dy*dy) / 0.02);
//  }
//};



int main()
{
    double no_elements;
    std::cout << "Please enter number of elements (e.g. 32):\n>";
    std::cin >> no_elements;
    
    double u0_input;
    std::cout << "Please enter constant boundary conditions (e.g. 3.0):\n>";
    std::cin >> u0_input;
    
    double f_input;
    std::cout << "Please enter constant source function (e.g. 3.0) :\n>";
    std::cin >> f_input;
    
    double p_input;
    std::cout << "Please enter constant p value (e.g. 4.0):\n>";
    std::cin >> p_input;
    
    create_problem prob;
    prob.set_values(no_elements, u0_input, f_input, p_input);
    prob.problem_solver();
    
    return 0;
}
