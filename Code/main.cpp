// pLaplace equation (C++)
// ======================

#include <dolfin.h>
#include "pLaplace.h"
#include <ufc.h>
#include <iostream>
#include "problem_classes.h"
#include <assert.h>

#include <stdexcept>
#include <limits>

using namespace dolfin;

int main()
{
    
    double no_elements;
    std::cout << "Please enter number of elements (e.g. 32):\n>";
    std::cin >> no_elements;
    if (no_elements <= 0) {
        throw std::invalid_argument("Number of elements should be positive");
    }
    
    double u0_input;
    std::cout << "Please enter constant boundary conditions (e.g. 3.0):\n>";
    std::cin >> u0_input;
    
    double f_input;
    std::cout << "Please enter constant source function (e.g. 3.0) :\n>";
    std::cin >> f_input;
    
    double p_input;
    std::cout << "Please enter constant p value greater than 2 (e.g. 4.0):\n>";
    std::cin >> p_input;
    if (p_input <= 2) {
        throw std::invalid_argument("p should be greater than 2");
        //p should be greater than 2. For the case p = 2 the equation reduces to the usual Laplace equation
    }
    
    create_problem prob;
    prob.set_values(no_elements, u0_input, f_input, p_input);
    prob.problem_solver();
    
    
    
    return 0;
}
