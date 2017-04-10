// pLaplace equation (C++)
// ======================

#include <dolfin.h>
#include "pLaplace.h"
#include <ufc.h>
#include <iostream>

using namespace dolfin;

// Source term (right-hand side)
class Source : public Expression
{
  void eval(Array<double>& values, const Array<double>& x) const
  {
    double dx = x[0] - 0.5;
    double dy = x[1] - 0.5;
    values[0] = 10*exp(-(dx*dx + dy*dy) / 0.02);
  }
};

// Sub domain for Dirichlet boundary condition
class DirichletBoundary : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
    return x[0] < DOLFIN_EPS or x[0] > 1.0 - DOLFIN_EPS;
  }
};


int main()
{
    double input;
    std::cout << "Please enter number of elements (e.g. 32):\n>";
    std::cin >> input;
    // Create mesh and function space
    auto mesh = std::make_shared<UnitSquareMesh>(input, input);
    auto V = std::make_shared<pLaplace::FunctionSpace>(mesh);

    // Define boundary condition
    std::cout << "Please enter constant boundary conditions (e.g. 3.0):\n>";
    std::cin >> input;
    auto u0 = std::make_shared<Constant>(input);
    auto boundary = std::make_shared<DirichletBoundary>();
    DirichletBC bc(V, u0, boundary);
    
    //Define solution function u
    auto u = std::make_shared<Function>(V);
    
    //Define Variatonal problem
    pLaplace::ResidualForm F(V);
    std::cout << "Please enter constant source function (e.g. 3.0) :\n>";
    std::cin >> input;
    auto f = std::make_shared<Constant>(input);
//    auto f = std::make_shared<Source>();
    std::cout << "Please enter constant p value (e.g. 4.0):\n>";
    std::cin >> input;
    auto p = std::make_shared<Constant>(input);
    auto epsilon = std::make_shared<Constant>(1.0e-5);
    F.p = p;
    F.u = u;
    F.f = f;
    F.epsilon = epsilon;
    

    //Create Jacobian J = F' to be used in the nonlinear solver
    pLaplace::JacobianForm J(V,V);
    J.u = u;
    J.p = p;
    J.epsilon = epsilon;

    
    // Solve Parameters
    Parameters params("nonlinear_variational_solver"); //to solve a nonlinear problem
    Parameters newton_params("newton_solver"); //use the newton method to solve the problem
    newton_params.add("maximum_iterations", 1000); //set number of maximum iterations
    //    newton_params.add("relative_tolerance", 1e-6); //set relative tolerance instead of maximum iterations
    params.add(newton_params);
    
    // Compute solution
    solve(F == 0, *u, bc, J, params);

    // Save solution in VTK format
    File file("pLaplace.pvd");
    file << *u;

    return 0;
}
