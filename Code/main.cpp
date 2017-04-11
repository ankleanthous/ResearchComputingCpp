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
    std::cout << "Please enter constant p value greater than 2 (e.g. 4.0):\n>";
    std::cin >> p_input;
    if (p_input <= 2) {
        throw std::invalid_argument("p should be greater than 2");
        //p should be greater than 2. For the case p = 2 the equation reduces to the usual Laplace equation
    }
    

    create_problem prob;
    prob.set_values(no_elements, u0_input, f_input, p_input);
    prob.problem_solver();
    
//    // Solve Parameters
//    Parameters params("nonlinear_variational_solver"); //to solve a nonlinear problem
//    Parameters newton_params("newton_solver"); //use the newton method to solve the problem
//    newton_params.add("maximum_iterations", 1000); //set number of maximum iterations
//    //    newton_params.add("relative_tolerance", 1e-6); //set relative tolerance instead of maximum iterations
//    params.add(newton_params);
//    
//    // Compute solution
//    solve(F == 0, *u, bc, J, params);
//    
//    // Save solution in VTK format
//    File file("pLaplace.pvd");
//    file << *u;
    
    return 0;
}
