// pLaplace equation (C++)
// ======================

#include <dolfin.h>
#include "pLaplace.h"

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

  // Create mesh and function space
  auto mesh = std::make_shared<UnitSquareMesh>(64, 64);
  auto V = std::make_shared<pLaplace::FunctionSpace>(mesh);

  // Define boundary condition
  auto u0 = std::make_shared<Constant>(0.0);
  auto boundary = std::make_shared<DirichletBoundary>();
  DirichletBC bc(V, u0, boundary);
    
    
    //Define solution function u
    auto u = std::make_shared<Function>(V);
    
    //Define Variatonal problem
    pLaplace::ResidualForm F(V);
    auto f = std::make_shared<Constant>(1.0);
    auto p = std::make_shared<Constant>(3.0);
    F.p = p;
    F.u = u;
    F.f = f;
    

    //Create Jacobian J = F' to be used in the nonlinear solver
    pLaplace::JacobianForm J(V,V);
    J.u = u;
    J.p = p;

    
// Solve Parameters
//    Parameters params("nonlinear_variational_solver");
//    Parameters newton_params("newton_solver");
//    newton_params.add("relative_tolerance", 1e-6);
//    params.add(newton_params);
    
  // Compute solution
  solve(F == 0, *u, bc, J);

  // Save solution in VTK format
  File file("pLaplace.pvd");
  file << *u;

  return 0;
}
