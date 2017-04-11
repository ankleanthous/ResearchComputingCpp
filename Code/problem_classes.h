#include <dolfin.h>
#include "pLaplace.h"
#include <ufc.h>
#include <iostream>
#include <assert.h>

using namespace dolfin;

class DirichletBoundary : public SubDomain
{
    bool inside(const Array<double>& x, bool on_boundary) const
    {
        return on_boundary;
    }
};


class create_problem {
public:
    double no_elements, u0_input, f_input, p_input;

	public:
		void set_values(double, double, double, double);

	int problem_solver(){
    // Create mesh and function space
        
    if (no_elements <= 0) {
        throw std::invalid_argument("Number of elements should be positive");
    }
    if (p_input <= 2) {
        throw std::invalid_argument("p should be greater than 2");
    //p should be greater than 2. For the case p = 2 the equation reduces to the usual Laplace equation
    }

    // Create mesh and function space
    auto mesh = std::make_shared<UnitSquareMesh>(no_elements, no_elements);
    auto V = std::make_shared<pLaplace::FunctionSpace>(mesh);

    // Define boundary condition
    
    auto u0 = std::make_shared<Constant>(u0_input);
    auto boundary = std::make_shared<DirichletBoundary>();
    DirichletBC bc(V, u0, boundary);
    
    //Define solution function u
    auto u = std::make_shared<Function>(V);
    
    //Define Variatonal problem
    pLaplace::ResidualForm F(V);
    
    auto f = std::make_shared<Constant>(f_input);
        
    auto p = std::make_shared<Constant>(p_input);
    
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
        
};
};

void create_problem::set_values (double x, double y, double z, double w) {
  no_elements = x;
  u0_input = y;
  f_input = z;
  p_input = w;
};
