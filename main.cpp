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

  // Define variational forms
//      pLaplace::BilinearForm a(V, V);
//  pLaplace::LinearForm L(V);
//      auto f = std::make_shared<Source>();
//    auto f = std::make_shared<Constant>(1.0);
//    auto p = std::make_shared<Constant>(3.0);
//    auto epsilon = std::make_shared<Constant>(0.0001);
//    a.p = p;
//    a.epsilon = epsilon;
//  L.f = f;
    
    pLaplace::ResidualForm F(V);
    auto f = std::make_shared<Constant>(1.0);
    auto p = std::make_shared<Constant>(3.0);
    F.p = p;
    F.f = f;

    
  // Compute solution
  Function u(V);
  solve(F == 0, u, bc);

  // Save solution in VTK format
  File file("pLaplace.pvd");
  file << u;

  return 0;
}
